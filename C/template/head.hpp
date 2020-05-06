#ifndef _HEAD_HPP_
#define _HEAD_HPP_
#include<iostream>

template<class T, int N=2>
class array
{
    public:
        T a[N];
        array(T val){for(T& ele:a)ele=val;}

        void print();
};

template<class T, int N>
void array<T, N>::print()
{
    using namespace std;

    for(T ele:a)
        cout << ele << endl;
}


// 特化
template<int N>
class array<bool, N>
{
    public:
        bool a[N];
        array(bool val){for(auto& el:a){el=true;}}
        void print();
};

template<int N>
void array<bool, N>::print()
{
    using namespace std;

    for(auto el:a)
        if(el)
            cout << "bool true " << endl;
        else
            cout << "bool false " << endl;
}


#endif
