#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<glog/logging.h>

#include<Eigen/Dense>
#include<Eigen/Core>


void init_glog();
std::vector<std::vector<double>> get_data(int pre_len=46);
std::vector<std::string> stringsplit(std::string &str, std::string token); 

class PCA {
    public:
        Eigen::MatrixXd data;
        Eigen::MatrixXd res;
        int w, h;

        PCA() {}
        PCA(std::vector<std::vector<double>>&);
        void pca();
};


int main() {
    init_glog();
    auto data = get_data();
    PCA pca(data);
    pca.pca();
    return 0;
}


void init_glog() {
    google::InitGoogleLogging("PCA logger");
    google::SetStderrLogging(google::INFO);
}


std::vector<std::vector<double>> get_data(int pre_len) {
    using namespace std;

    string fn("../04cars.dat.txt");
    ifstream file(fn, ifstream::in | ifstream::ate);
    CHECK(file.is_open()) << "file " << fn << "open failed !!";

    int len = file.tellg();
    file.seekg(0);

    string buf;
    buf.resize(len);
    file.read(&buf[0], len);
    file.close();

    stringstream ss;
    auto split = stringsplit(buf, "\n");
    vector<vector<double>> samples;
    vector<double> one_inst;
    double tmp;
    one_inst.resize(16);
    for (auto &line : split) {
        if (line.find('*') != string::npos) continue;
        line.replace(0, pre_len, "");
        ss.str(line);
        ss.clear();

        for (int i{0}; i < 16; ++i) {
            ss >> tmp;
            one_inst[i] = tmp;
        }
        samples.push_back(one_inst);
    }

    return samples;
}


std::vector<std::string> stringsplit(std::string &str, std::string token) {
    using namespace std;

    auto beg = str.begin();
    string::size_type pos1 = 0;
    string::size_type pos2 = str.find(token, pos1);
    vector<string> split;
    while (pos2 != string::npos) {
        split.emplace_back(beg+pos1, beg+pos2);
        pos1 = pos2 + token.size();
        pos2 = str.find(token, pos1);
    }
    if (pos1 != str.length()) {
        split.emplace_back(beg+pos1, beg+str.length());
    }

    return split;
}


PCA::PCA(std::vector<std::vector<double>>& d) {
    // check all rows have same length
    h = static_cast<int>(d.size());
    if (h == 0) {
        w = 0;
    } else {
        w = static_cast<int>(d[0].size());
        for (int i{0}; i < h; ++i) {
            auto wtemp = static_cast<int>(d[i].size());
            CHECK(w == wtemp) << "input data matrix should have same dimensions\n";
        }
    }


    // std::vector<double> data_act(h*w);
    // int pos = 0;
    data = Eigen::MatrixXd(h, w);
    for (int i{0}; i < h; ++i) {
        for (int j{0}; j < w; ++j)
            data(i, j) = d[i][j];
    }
    // data = Eigen::Map<Eigen::MatrixXd>(&data_act[0], w, h);  // eigen is colomn main
}

void PCA::pca() {
    using namespace std;
    
    Eigen::MatrixXd C = data.transpose() * data;
    cout << C << endl;
    cout << C.rows() << ", " << C.cols() << endl;

    cout << C.rowwise().mean() << endl;
}
