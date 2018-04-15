#include<opencv2/opencv.hpp>
#include<vector>
#include"ConnectedDomain.h"
#include<memory>
#include<vector>
#include<array>




/* compute the connected area of a picture
 * input:
 *     srcImage: an input gray scale picture
 *     show: a bool whether draw the process  */
cv::Mat ConnectedDomain(cv::Mat srcImage, bool draw)
{
    using namespace std;
    using namespace cv;

    unsigned char *data = srcImage.data;
    long len = srcImage.rows * srcImage.cols;

    // convert gray scale picture to binary color map with a threshold of 125
    for(long i{0}; i<len; i++)
        if(data[i]>125)
            data[i] = 255;
        else
            data[i] = 0;
   
    // definition of associated variables
    // int *labels{new int[len]};
    vector<int> labels(len, 0);
    int CurrentLabel;
    int CurrentColor;
    vector<pair<long,long>> cache;
    pair<long, long> pos;
    long ind;
    long istart, iend, jstart, jend;

    Mat show(srcImage.rows, srcImage.cols, CV_8UC1, Scalar(255));
    unsigned char *data_show  = show.data;
    unsigned char interval = 40; // gray scale interval of two connected patches
    if(draw)
    {
        imshow("original", srcImage);
        waitKey(1);
    }

    // a lambda to compute the neighbors of a given pixel
    auto AddToCache = [&](pair<long, long>&& pos){
                        istart = pos.first - 1;
                        iend = pos.first + 1;
                        jstart = pos.second - 1;
                        jend = pos.second + 1;

                        // compute boundary of search
                        if(pos.first==0) 
                            istart = 0;
                        else if(pos.first==srcImage.rows-1)
                            iend = srcImage.rows-1;

                        if(pos.second==0)
                            jstart = 0;
                        else if(pos.second==srcImage.cols-1)
                            jend = srcImage.cols-1;

                        // check the neighbors and add them to vector
                        for(long i{istart}; i<iend+1; i++)
                            for(long j{jstart}; j<jend+1; j++)
                            {
                                ind = srcImage.cols * i + j;
                                if(data[ind]==CurrentColor && labels[ind]==0)
                                {

                                    labels[ind] = CurrentLabel;
                                    cache.push_back(pair<long,long>(i,j));

                                    data_show[ind] = CurrentLabel * interval;
                                    if(draw)
                                    {
                                        imshow("drawing search", show);
                                        waitKey(1);
                                    }
                                }
                            }
    };

    // process of searching the connected domains
    CurrentLabel = 1;
    // memset(labels, 0, sizeof(int)*len);

    for(long i{0}; i<srcImage.rows; i++)
        for(long j{0}; j<srcImage.cols; j++)
        {
            ind = srcImage.cols * i + j;
            if(labels[ind]==0)
            {
                CurrentColor = data[ind];
                labels[ind] = CurrentLabel; // find the first seed pixel

                data_show[ind] = CurrentLabel * interval;
                if(draw)
                {
                    imshow("drawing search", show);
                    waitKey(1);
                }
                
                AddToCache(pair<long,long>(i,j)); // label its neighbors and add them to a container

                // search all its neighbors of neighbors recursively
                while(!cache.empty())
                {
                    pos = cache.back();
                    cache.pop_back();

                    AddToCache(std::move(pos));
                }
                CurrentLabel ++;
                // TODO: if areas are to computed ,add operations here
            }
        }

    cout << "number of connected domains: " << CurrentLabel-1 << endl;

    // for(long i{0}; i<len; i++)
    //     data[i] = labels[i] * interval;

    // swap(data_show, srcImage.data);
    // delete[] labels;

    return show;
}
