#include<iostream>


using std::cout;
using std::endl;


void calD()
{
    int a = 0;
    int res = 0;

    cout << "in dynamic lib, before calculation" << endl;

    while(a++ < 10000)
        res += a;

    cout << "in dynamic lib, after calculation" << endl;
}
