#include<iostream>
#include<cstring>
#include<array>
#include<vector>
#include<algorithm>


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




    return 0;
}
