#include<opencv2/opencv.hpp>
#include<iostream>
#include<cassert>
#include"grayscale.h"
#include"ConnectedDomain.h"


void tryfilter();
void SplitMerge();
void ConnDomain();
void GrayScale();
void tryverbose();
void EdgeDetect();


int main(void)
{
    using namespace cv;
    using namespace std;


    // ConnDomain();

    // GrayScale();

    ////// other trying
    // double min, max;
    // Point minloc, maxloc;
    // minMaxLoc(temp, &min, &max, &minloc, &maxloc);
    //
    // int minind[3], maxind[3];
    // minMaxIdx(srcImage, &min, &max, minind, maxind);
    // cout << srcImage.rows << endl;
    // cout << srcImage.dims << endl;
    // cout << "here" << endl;
    // cout << srcImage.channels() << endl;
    // cout << srcImage.depth() << endl;
    // srcImage.convertTo(temp, CV_8UC3);
    // cout << temp.channels() << endl;
    // cout << temp.depth() << endl;


    EdgeDetect();
    // tryfilter();
    // SplitMerge();
    // tryverbose();


    cout << "done" << endl;
    int m;
    cin >> m;

    return 0;
}


void ConnDomain()
{
    using namespace std;
    using namespace cv;

    Mat srcImage = imread("./img.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    assert(!srcImage.empty());
    // imshow("original",srcImage);
    // waitKey(1);

    // compute the connected domain
    Mat temp;
    resize(srcImage, temp, Size(0, 0), 0.4, 0.4, INTER_CUBIC);
    // resize(srcImage, temp, Size(440, 300), 0, 0, INTER_CUBIC);
    Mat Conn = ConnectedDomain(temp, false);
    imshow("connected domains", Conn);
    waitKey(0);
}



void GrayScale()
{
    using namespace std;
    using namespace cv;

    Mat srcImage = imread("./img.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    assert(!srcImage.empty());
    Mat temp;

    assert(!srcImage.empty());
    temp = GrayScaleHistogram(srcImage);
    imshow("histogram", temp);
    waitKey(0);
}




void tryfilter()
{
    using namespace std;
    using namespace cv;

    Mat srcImage = imread("./img.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    // Mat srcImage = imread("./img.jpg");
    assert(!srcImage.empty());
    imshow("before filter",srcImage);
    waitKey(0);

    Mat dst;
    Mat kernel;

    // 一般形式的滤波
    // kernel = (Mat_<char>(3,3) << 1,0,-1,2,0,-2,1,0,-1);
    // kernel = (Mat_<char>(3,3) << 0,0,0,-70,0,70,0,0,0);
    // filter2D(srcImage,dst,-1,kernel);
    // imshow("after filter",dst);
    // waitKey(0);



    // 均值滤波
    // kernel = (Mat_<double>(3,3) << 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9);
    // filter2D(srcImage, dst, -1, kernel);
    // imshow("均值滤波", dst);
    // waitKey(0);



    // 中值滤波
    // medianBlur(srcImage, dst, 3);
    // imshow("中值滤波", dst);
    // waitKey(0);



    // 高斯滤波
    GaussianBlur(srcImage, dst, Size(3,3), 0);
    imshow("高斯滤波opencv", dst);
    waitKey(0);
    kernel = (Mat_<double>(3,3) << 1.0/16,2.0/16,1.0/16,2.0/16,4.0/16,2.0/16,1.0/16,2.0/16,1.0/16);
    filter2D(srcImage, dst, -1, kernel);
    imshow("高斯滤波kernel", dst);
    waitKey(0);


    ////////////
    // uchar* data;
    // long len;
    // long ind;
    //
    //
    // ind = 70;
    // len  = srcImage.rows * srcImage.cols;
    // data = srcImage.data;
    // cout << "original: " << (int)data[ind] << ", " << (int)data[ind+1] << ", " << (int)data[ind+2] << endl;
    // cout << "filtered: " << (int)dst.data[ind] << ", " << (int)dst.data[ind+1] << ", " << (int)dst.data[ind+2] << endl;
    //
    //
    // data = dst.data;
    //
    // for(long i{0}; i<len; i++)
    //     if(data[i] < 0 || data[i] > 255)
    //     {
    //         cout << "negative after filtering: " << i << "," << data[i] << endl;
    //         // cout << "ind is: " << i << endl;
    //         // break;
    //     }
    //

}


void SplitMerge()
{
    using namespace std;
    using namespace cv;

    Mat src;
    Mat out;

    src = imread("./img.jpg");

    //// vector version
    //
    // vector<Mat> con;
    // int size;
    //
    // // split
    // split(src, con);
    //
    // size = con.size();
    // for(int i{0}; i<size; i++)
    // {
    //     imshow("split"+i, con.at(i));
    //     waitKey(0);
    // }
    //
    // // merge
    // merge(con, out);
    // imshow("merge", out);
    // waitKey(0);
    //

    //// array version
    Mat m[3];
    split(src, m);
    for(int i{0}; i<3; i++)
    {
        imshow("split"+i, m[i]);
        waitKey(0);
    }
    merge(m, 3, out);
    imshow("merge", out);
    waitKey(0);
}



void tryverbose()
{

}


void EdgeDetect()
{
    using namespace std;
    using namespace cv;

    Mat src;
    Mat kernel;
    Mat gaussian;
    Mat out;
    Mat sobelx;
    Mat sobely;
    // long len;

    src = imread("./img.jpg");
    assert(!src.empty());
    // len = src.rows * src.cols;

    // sobel 检测
    // Sobel(src, sobelx, -1, 1, 0, 3);
    // Sobel(src, sobely, -1, 0, 1, 3);
    // out = sobelx + sobely;
    //
    // imshow("sobelx", sobelx);
    // waitKey(0);
    // imshow("sobely", sobely);
    // waitKey(0);
    // imshow("edges", out);
    // waitKey(0);


    // laplace without gaussian filter
    kernel = (Mat_<char>(3,3) << 1,1,1, 1,-8,1, 1,1,1);
    filter2D(src, out, -1, kernel);
    imshow("plain laplace edges", out);
    waitKey(0);

    // laplace combined with gaussian filter
    GaussianBlur(src, gaussian, Size(3,3), 1);
    kernel = (Mat_<double>(3,3) << 1,1,1, 1,-8,1, 1,1,1);
    filter2D(gaussian, out, -1, kernel);
    imshow("laplace edges with gaussian", out);
    waitKey(0);

    // LoG kernel算子
    // kernel = (Mat_<char>(5,5) << 0,0,-1,0,0,0,-1,-2,-2,0,-1,-2,16,-2,-1,0,-1,-2,-1,0,0,0,-1,0,0);
    // filter2D(src, out, -1, kernel);
    // imshow("LoG 5x5 direct implementation", out);
    // waitKey(0);

    // Canny 算法
    // double t1;
    // double ratio;
    //
    // t1 = 60;
    // ratio = 4;
    // Canny(src, out, t1, t1*ratio, 3); // 3这个参数表示计算sobel梯度时，使用的窗的大小，3表示3x3的窗口
    // imshow("Canny opencv interface", out);
    // waitKey(0);



}
