#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using std::cout;
using std::endl;

class subMat:public Mat
{
    public:
        void isContinuous()
        {
            cout<<"imshow() inherent from mat"<<endl;
        }
};


int main(void)
{
    Mat srcImage = imread("./img.jpg");
    imshow("图",srcImage);
    waitKey(0);

    return 0;
}
