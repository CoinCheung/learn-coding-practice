#include<iostream>
#include<cstring>
#include<array>
#include<vector>
#include<algorithm>
#include<opencv2/opencv.hpp>


int main(void)
{
    using namespace std;

    long N[256];
    memset(N, 0, 256*sizeof(long));

    long max = N[0];
    for(auto val:N)
        if(val>max)
            max=val;
    cout << max << endl;

    // array<int, 7> mm{0};
    // for(auto& val:mm)
    //     val = 88;
    // for(auto val:mm)
    //     cout << "mm is: " << val << endl;
    //
    // try vector
    // int n;
    // n = 10;
    // vector<int> labels(n, 2);
    // labels[4] = 4;
    // for(auto val:labels)
    //     cout << "labels is: " << val << endl;

    vector<int> v(5);
    v.push_back(4);
    int m;
    // v.pop_back();
    // m = end(v);
    int mm[4];
    end(mm);
    begin(mm);

    using namespace cv;
    Mat img =  imread("./img.jpg", -1);
    Mat img_out;
    imshow("org", img);
    waitKey(0);

    vector<Mat> channels;
    vector<Mat> chnls(3);
    split(img, channels);
    cout << "channels: " << channels.size() << endl;
    chnls[0] = channels[0];
    chnls[1] = channels[2];
    chnls[2] = channels[1];
    merge(chnls, img_out);
    imshow("changed", img);
    waitKey(0);



    return 0;
}
