#include<opencv2/opencv.hpp>
#include<cstring>
#include<array>


/* given a gray scale image and compute its histogram */
cv::Mat GrayScaleHistogram(cv::Mat& Img)
{
    using namespace cv;
    using namespace std;
    
    //variables needed
    // long GrayNum[256];
    array<long, 256> GrayNum{};

    unsigned char* data;
    long len;
    long MaxVal;
    Mat hist(256,256, CV_8UC1, Scalar(255));
    long height;

    // variables initialization
    data = Img.data;
    len = Img.rows * Img.cols;
    height = 256 * 0.9;
    // memset(GrayNum, 0, sizeof(long)*256);
    for(auto& val:GrayNum)
        val = 0;

    // count pixels
    for(long i{0}; i<len; i++)
        GrayNum[data[i]] ++;

    // find the most pixel
    MaxVal = GrayNum[0];
    for(long val:GrayNum)
        if(MaxVal<val)
            MaxVal = val;
        
    // compute and draw histogram
    // hist = height * (val / maxval)
    for(int i{0}; i<256; i++)
    {
        GrayNum[i] = static_cast<long>(((double)GrayNum[i]/MaxVal)*height);
        line(hist, Point(i,255), Point(i, 255-GrayNum[i]), Scalar(0));
    }
    
    return hist;
}
