#include<iostream>


using std::cout;
using std::endl;


void calS()
{
    int a = 0;
    int res = 0;

    cout << "in static lib, before calculation" << endl;

    while(a++ < 10000)
        res += a;

    cout << "in static lib, after calculation" << endl;
}
