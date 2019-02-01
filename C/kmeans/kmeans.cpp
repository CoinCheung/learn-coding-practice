// #include<>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<iostream>
#include<iterator>
#include<vector>
#include<array>
#include<tuple>
#include<map>
#include<set>
#include<algorithm>
#include<sstream>
#include<ctime>
#include<stdlib.h>
#include<cmath>
#include<thread>
#include<mutex>

#include<rapidjson/document.h>
#include<rapidjson/stringbuffer.h>
#include<rapidjson/writer.h>


double scale{800};
double img_upper_lmt{1500};
int k = 5;
// std::string jname = "/home/coin/Haishen/all_train.json";
std::string jname = "/home/coin/Haishen/coco_gxm_test_0516_train.json";


// 1. kmeans 对初始值比较敏感, 所以需要取不同的初始值多做几次取最好的, 一般做10次
// 2. 如果数据集是非凸的, 一般不会自动收敛, 所以需要指定一个最大收敛迭代数Max_iter, 一般是300
// 3. 初始化的方法, 可以随机取, 但是因为对初始值敏感, 所以结果也带一定随机性. 所以一般选距离最大的点: 1) 随机选第一个点; 2) 选与第一个点距离最大的点为第二个点; 3) 选跟前两个点的最小距离最大的点为第三个点, 依次
// 4. 衡量分类数k的标准, 一般可以看簇半径的变化, 簇半径就是所有样本与中心点距离的最大值. 由于有多个类, 一般使用多个类的平均值. 如果k小于应该有的类数, 减小k的时候, 簇半径会急剧增大, 如果k大于应该有的类数, 增大k的时候, 簇半径会减小缓慢
// 5. 除了最大迭代数 max_iter还有centroid不变之外, 还有一个迭代截止条件, 就是每个样本距离和它最近的簇中心点的距离之和的变化量, sklearn 默认是1e-4, 如果两个距离之和变化量小于这个inertia的话, 就认为收敛.

// 6. 太大的计算量的话, 可以考虑用多线程去做. 多核加速


// TODO:
// 1. 多线程bug
// 2. gxm 数据会输出nan

class Sample {
    public:
        double width;
        double height;
        double dis;
        int cls;
        double aspect_ratio;

        Sample(double w, double h):width(w), height(h){}
        static double distance(Sample&, Sample&);
};



double Sample::distance(Sample& a, Sample& b) {
    double IOU, cross, join;
    double min_w, min_h;

    min_w = a.width > b.width ? b.width : a.width;
    min_h = a.height > b.height ? b.height : a.height;

    cross = min_w * min_h;
    join = a.width * a.height + b.width * b.height - cross;
    IOU = cross / join;

    return 1 - IOU;
}


class KMeans {
    public:
        std::vector<Sample> samples;
        std::vector<Sample> means;
        std::vector<Sample> means_tmp;
        int class_num;
        int sample_num;
        double dis_sum;
        double dis_sum_old;
        bool done;
        int MAX_ITER;
        double MARGIN;
        double MeanSilhouette;
        int jobs;

        KMeans(std::vector<Sample>& smpl, int cn, int MAXITER, double MARGIN, int jobnum);
        void GenInitMean();
        void GenRandMean();
        void SampleClassify();
        void GetSampleMean();
        KMeans SetJobs(int job_num);
        double ComputeSilhouette(int ind);
        double ComputeSilhouetteMean();
        static void ComputeSilhouetteThread(KMeans *ptr, 
                int start, int len);
        void PrintRes();
};

KMeans::KMeans(std::vector<Sample>& smpl, int cn, int MAXITER = 300, 
        double MARGIN = 1e-4, int jobnum = 1) {
    if (cn < 1) {
        std::cout << "cluster centrid number must be greater than 1 \n"; 
        exit(0);
    }

    class_num = cn;
    samples = smpl;
    sample_num = static_cast<int>(samples.size());
    done = false;
    MAX_ITER = MAXITER;
    MARGIN = MARGIN;
    jobs = jobnum;
    dis_sum = 0;
    dis_sum_old = 0;

    means.reserve(cn);
    means_tmp.reserve(cn);
    for (int i{0}; i < class_num; i ++) means_tmp.push_back(Sample(0,0));
}


void KMeans::GenInitMean() {
    using std::set;
    using std::vector;
    using std::count;

    set<int> exist_inds;
    vector<double> vdis(sample_num, 10000000000);
    int ind;
    double max{-1};
    int max_ind{0};
    double dis;

    srand(time(NULL));
    ind = rand() % sample_num;
    exist_inds.insert(ind);

    // for (int i{0}; i < sample_num; i++) {
    //     if (count(exist_inds.begin(), exist_inds.end(), i)) continue;
    //     dis = Sample::distance(samples[i], samples[ind]);
    //     if (dis < vdis[i]) vdis[i] = dis;
    //     if (max < vdis[i]) {
    //         max = vdis[i];
    //         max_ind = i;
    //     }
    // }
    // exist_inds.insert(max_ind);
    // ind = max_ind;

    for (int n{1}; n < class_num; n ++) {
        max = -1;
        for (int i{0}; i < sample_num; i++) {
            if (count(exist_inds.begin(), exist_inds.end(), i)) continue;
            dis = Sample::distance(samples[ind], samples[i]);
            if (dis < vdis[i]) vdis[i] = dis;
            if (max < vdis[i]) {
                max = vdis[i];
                max_ind = i;
            }
        }
        exist_inds.insert(max_ind);
        ind = max_ind;
    }

    means.clear();
    for (auto& el : exist_inds) {
        means.push_back(samples[el]);
    }
}

void KMeans::GenRandMean() {
    means.clear();
    srand((unsigned)time(NULL));
    for (int i{0}; i < class_num; i++) {
        means.push_back(samples[rand() % sample_num]);
    }
}

void KMeans::SampleClassify() {
    double dis, min;
    int cls;

    dis_sum_old = dis_sum;
    dis_sum = 0;
    done = true;
    for (auto& el : samples) {
        min = 100000000;
        for (int i{0}; i < class_num; i ++) {
            dis = Sample::distance(el, means[i]);
            if (dis < min) {
                min = dis;
                cls = i;
            }
        }
        if (cls != el.cls) done = false;
        el.cls = cls;
        el.dis = min;
        dis_sum += el.dis;
    }
}

void KMeans::GetSampleMean() {
    using std::vector;

    static vector<int> nums(class_num);
    nums.assign(class_num, 0);
    // done = true;

    for (auto& el : means_tmp) {
        el.width = 0.0;
        el.height = 0.0;
    }
    for (auto& el : samples) {
    // std::cout << "el.cls: " << el.cls << std::endl;
        means_tmp[el.cls].width += el.width;
        means_tmp[el.cls].height += el.height;
        nums[el.cls] ++;
    }

    for (int i{0}; i < class_num; i++) {
        means_tmp[i].width /= nums[i];
        means_tmp[i].height /= nums[i];
        means_tmp[i].aspect_ratio = means_tmp[i].width / means_tmp[i].height;
        if (means_tmp[i].width != means[i].width || means_tmp[i].height != means[i].height) {
            // done = false;
        }
    }

    means_tmp.swap(means);
}

KMeans KMeans::SetJobs(int job_num) {
    jobs = job_num;
    return *this;
}

double KMeans::ComputeSilhouette(int ind) {
    int same_cls{samples[ind].cls};
    double same_dis_mean{0};
    double min_other_dis_mean = 1000000;
    double res;
    std::vector<double> dis_mean(class_num, 0);
    std::vector<double> nums(class_num, 0);

    for (int i{0}; i < sample_num; i++) {
        if (i != ind) {
            dis_mean[samples[i].cls] += Sample::distance(samples[ind], samples[i]);
            nums[samples[i].cls] ++;
        }
    }

    for (int i{0}; i < class_num; i++) {
        dis_mean[i] /= nums[i];
        if (dis_mean[i] < min_other_dis_mean && i != same_cls) {
            min_other_dis_mean = dis_mean[i];
        }
    }
    same_dis_mean = dis_mean[same_cls];

    if (same_dis_mean > min_other_dis_mean) {
        res = min_other_dis_mean / same_dis_mean - 1;
    } else {
        res = 1 - same_dis_mean / min_other_dis_mean;
    }

    return res;
}


double KMeans::ComputeSilhouetteMean() {
    // only for debug
    // std::vector<Sample> vec;
    // vec.assign(samples.begin(), samples.begin()+10000);
    // samples = vec;
    // sample_num = static_cast<int>(samples.size());
    // 

    if (sample_num < 22400) {  // if memory comsumming less than 2G
        using std::vector;
        MeanSilhouette = 0;
        // creating distance matrix
        vector<vector<double>> dis_mtrx(sample_num);
        for (int i{0}; i < sample_num; i++) {
            dis_mtrx[i].reserve(i);
            for (int j{0}; j < i; j++) {
                dis_mtrx[i][j] = Sample::distance(samples[i], samples[j]);
            }
        }
        // same logic as ComputeSilhouette(), but for refering the distance table
        vector<double> dis_mean(class_num, 0);
        vector<double> nums(class_num, 0);
        int same_cls;
        double same_dis_mean{0};
        double min_other_dis_mean = 1000000;
        int loc_r, loc_c;
        for (int ind{0}; ind < sample_num; ind++) {
            same_cls = samples[ind].cls;
            dis_mean.assign(class_num, 0);
            nums.assign(class_num, 0);
            min_other_dis_mean = 1000000;
            for (int i{0}; i < sample_num; i++) {
                if (i != ind) {
                    if (ind > i) {
                        loc_r = ind;
                        loc_c = i;
                    } else {
                        loc_r = i;
                        loc_c = ind;
                    }
                    dis_mean[samples[i].cls] += dis_mtrx[loc_r][loc_c];
                    nums[samples[i].cls] ++;
                }
            }
            for (int i{0}; i < class_num; i++) {
                dis_mean[i] /= nums[i];
                if (dis_mean[i] < min_other_dis_mean && i != same_cls) {
                    min_other_dis_mean = dis_mean[i];
                }
            }
            same_dis_mean = dis_mean[same_cls];
            if (same_dis_mean > min_other_dis_mean) {
                MeanSilhouette += min_other_dis_mean / same_dis_mean - 1;
            } else {
                MeanSilhouette += 1 - same_dis_mean / min_other_dis_mean;
            }
        }
        MeanSilhouette /= sample_num;
        std::cout << "computing Silhouette by refering to table: \n";

    } else {  // if memory comsumming more than 2G
        // TODO: multi threading
        using std::thread;
        using std::vector;

        int interval = sample_num / jobs;
        vector<thread> vth;
        vth.reserve(jobs);
        MeanSilhouette = 0;
        std::cout << "computing Silhouette one by one with " << jobs << " threads \n";
        for (int i{0}; i < jobs - 1; i++) {
            // std::cout << "creating thread: " << i << std::endl;
            vth.push_back(thread(ComputeSilhouetteThread, this, i * interval,
                        interval));
        }
        // std::cout << "creating last thread: " << std::endl;
        vth.push_back(thread(ComputeSilhouetteThread, this, (jobs - 1) * interval,
                    sample_num - (jobs - 1 ) * interval));
        // std::cout << "after creating last thread " << std::endl;
        for (auto& el : vth) {
            el.join();
        // for (int i{0}; i < jobs; i ++) {
            // vth[i].join();
        }
        // int in;
        // std::cin >> in;
        // std::cout << "all joined " << std::endl;
        MeanSilhouette /= sample_num;
    }

    return MeanSilhouette;
}


void KMeans::ComputeSilhouetteThread(KMeans* ptr, int start, int len) {
    using std::mutex;
    using std::lock_guard;

    // std::cout << "threading start ... \n";
    std::mutex m;
    double sum{0};
    for (int i{start}; i < len; i ++) {
        sum += ptr->ComputeSilhouette(i+1);
    }
    {
        lock_guard<mutex> lock(m);
        ptr->MeanSilhouette += sum;
    }
    // std::cout << "threading done ... \n";
}


void KMeans::PrintRes() {
    using namespace std;
    double dis_margin = dis_sum_old - dis_sum;
    cout << "====================\n";
    // std::cout << "iter " << iter << ":\n";
    cout << "dis_sum_old: " << dis_sum_old << ",\t dis_sum: " 
        << dis_sum << ",\t dis_decrease: " 
        << dis_margin << "\n"; 

    for (int i{0}; i < class_num; i ++) {
        cout << "mean " << i << ": " << means[i].width << ", " 
            << means[i].height << ", aspect ratios: " 
            << means[i].aspect_ratio << endl;
    }
    cout << endl;
}


std::string ReadJson(std::string jfile_name) {
    using namespace std;

    string res;
    string str;
    ifstream fin;

    fin.open(jfile_name, ifstream::in);
    if (!fin.is_open())  {
        cout << "error opening file!!" << endl;
        exit(0);  // TODO: use logging
    }
    while (getline(fin, str)) res.append(str + "\n");
    fin.close();

    return res;
}


std::vector<Sample> GetBoxShapes(std::string jf_name) {
    using std::string;
    using std::cout;
    using std::endl;
    using std::vector;
    using std::tuple;
    using std::make_tuple;
    using std::map;
    using std::stringstream;
    using std::get;

    using rapidjson::Document;
    using rapidjson::ParseErrorCode;
    using rapidjson::Value;

/* 
 * methods of Value:
 *     v.IsObject();
 *     v.HasMember();
 *     v.IsArray();
 *     v.IsInt();
 *     v.IsString();
 *     v.GetInt();
 *     v.GetString();
 *     v[9];
 *     v["key"];
 *  */

    string json_str;
    Document doc;

    json_str = ReadJson(jf_name);
    doc.Parse<0>(json_str.c_str());
    if (doc.HasParseError()) {
        ParseErrorCode code = doc.GetParseError();
        cout << code << "\n";
    }

    map<int, tuple<double, double, double>> shapes;

    // parse images field and
    Value& images = doc["images"];
    Value img;
    int img_id;
    double width, height, ratio;
    double max, min;
    stringstream ss;
    if (images.IsArray()) {
        int img_len = static_cast<int>(images.Size());
        for (int i{0}; i < img_len; i++) {
            img = images[i];
            if (img.IsObject()) {
                if (img.HasMember("id")) {
                    ss.str("");
                    ss.clear();
                    ss << img["id"].GetString();
                    if (!(ss >> img_id)) {
                        cout << "Error reading image id!!!\n";
                    }
                }
                if (img.HasMember("width")) {
                    width = static_cast<double>(img["width"].GetInt());
                }
                if (img.HasMember("height")) {
                    height = static_cast<double>(img["height"].GetInt());
                }
            }
            // compute ratio
            if (width > height) {
                max = width;
                min = height;
            } else {
                max = height;
                min = width;
            }
            if (max > img_upper_lmt) {
                ratio = img_upper_lmt / max;
            } else  {
                ratio = scale / min;
            }
            shapes[img_id] = make_tuple(width, height, ratio);
        }
    } else  {
        cout << "No image field in the json file, there can be errors !!\n";
    }

    // parse annotations
    Value& ann = doc["annotations"];  // 必须是引用, 而且贴着ann
    vector<Sample> bbox;

    Value seg;
    Value box;
    if (ann.IsArray()) {
        int seg_len {static_cast<int>(ann.Size())};
        bbox.reserve(seg_len);

        for (int i{0}; i < seg_len; i++) {
            seg = ann[i];
            if (seg.IsObject()) {
                box = seg["bbox"];
                if (seg.HasMember("image_id")) {
                    ss.str("");
                    ss.clear();
                    ss << seg["image_id"].GetString();
                    ss >> img_id;
                    
                    ratio = get<2>(shapes[img_id]);
                    width = box[2].GetDouble() * ratio;
                    height = box[3].GetDouble() * ratio;
                    // bbox.push_back(make_tuple(width, height));
                    bbox.push_back(Sample(width, height));
                } else  {
                    cout << "bbox object has no img_id field !!\n";
                }
            } else  {
                cout << "ann[" << i << "] is not an object!!\n";
                exit(0);
            }
        }
    }

    return bbox;
}

int main() {

    // for (auto &el:shape) {
    //     cout << el.first << ", " << el.second << endl;
    // }

    /* // 遍历
     * Document::MemberIterator beg(doc.MemberBegin());
     * Document::MemberIterator end(doc.MemberEnd());
     * for (; beg != end; beg++) {
     *     cout << beg->name.GetString() << endl;
     *     // cout << beg->value.GetString() << endl;
     * } */

    using std::vector;
    using std::tuple;
    using std::string;
    using std::get;

    using std::cout;
    using std::endl;

    string jfile_name(jname);
    vector<Sample> bbox;

    bbox = GetBoxShapes(jfile_name);

    KMeans km(bbox, k);
    km.SetJobs(2);

    // km.Fit();
    // km.GenRandMean();
    km.GenInitMean();
    cout << "====================\n";
    cout << "Initial Centroids are: \n";
    for (int i{0}; i < k; i ++) {
        cout << "mean " << i << ": " << km.means[i].width << ", " 
            << km.means[i].height << endl;
    }

    int iter{0};
    double dis_margin;
    while (!km.done) {
        km.SampleClassify();
        km.GetSampleMean();

        dis_margin = km.dis_sum_old - km.dis_sum;

        iter ++;
        if (iter % 30 == 0) {

            // cout << "====================\n";
            km.PrintRes();

            // std::cout << "iter " << iter << ":\n";
            // cout << "dis_sum_old: " << km.dis_sum_old << ",\t dis_sum: "
            //     << km.dis_sum << ",\t dis_decrease: "
            //     << dis_margin << "\n";
            //
            // for (int i{0}; i < k; i ++) {
            //     cout << "mean " << i << ": " << km.means[i].width << ", "
            //         << km.means[i].height << ", aspect ratios: "
            //         << km.means[i].aspect_ratio << endl;
            // }
            // cout << endl;
        }

        if (iter == km.MAX_ITER || abs(dis_margin) <= km.MARGIN) break;
    }

    double sm{km.ComputeSilhouetteMean()};

    std::cout << "Mean Silhouette is: " << sm << std::endl;

    std::cout << "Final Result is: " << sm << std::endl;
    km.PrintRes();
    if (km.done)
        std::cout << "done because class is fixed" << std::endl;


    // int in;
    // std::cin >> in;

    // for (auto& el : bbox)  {
    for (int i{0}; i < (int)bbox.size(); i++) {
        // std::cout << el.cls << std::endl;
        // std::cout << bbox[i].cls << std::endl;
    }
    // for (auto el:mean) {
    //     std::cout << el.width << ", " << el.height << "\n";
    // }


    return 0;
}
