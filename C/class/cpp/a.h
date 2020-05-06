
#include<iostream>

using std::cout;
using std::endl;


class A
{
    public:
        int dataA;
        void funA();
};


void A::funA()
{
    cout << "funA()" << endl;
}
