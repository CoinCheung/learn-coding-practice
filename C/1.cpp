#include<iostream>
#include<cstring>

using std::cout;
using std::endl;
using std::memcpy;

class A
{
    public:
        double *data;
        int N;
        A();
        ~A();
        A& operator=(A& a); // 重载声明
};

A::A(){N = 10; data = new double[10]; data[1]=33333;}
A::~A(){delete[] data;}

A& A::operator=(A& a) // 重载定义
{
    cout << "operator ="<<endl;
    this->N = a.N;
    this->data = new double[10]; 
    // this->data[1] = 2222;
    memcpy(this->data,a.data, a.N);

    return *this;
}

A& test()
{
    A *a = new A;  
    return *a;
}
int main(void)
{
    A b;
    b = test();  // 使用

    double *d = new double[10];
    double *dc = new double[10];
    d[1] = 11111;
    memcpy(dc, d, 10*sizeof(double));
    cout << "copied element is: "<<dc[1] <<endl;

    cout << b.data[1] <<endl;
}
