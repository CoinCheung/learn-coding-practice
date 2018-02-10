#include"b.h"
#include<iostream>


using std::cout;
using std::endl;


class B1
{
    public:
        virtual void func(){cout << "func of B1" << endl;}
        virtual ~B1(){}
};



class B2
{
    public:
        virtual void func(){cout << "func of B2" << endl;}
        virtual ~B2(){}
};



class D: public B1, public B2
{
    public:
        int m;
        virtual void func(){cout << "func of D" << endl;}
};

#include<cstring>

class obj
{
    public:
        int *np;
        int len;

        obj(obj& o){np = new int[o.len];std::memcpy(np, o.np, sizeof(int)*o.len);std::cout<<"left construction"<<std::endl;}
        obj(obj&& o):np(nullptr){std::cout << "right value construction is called !!" << std::endl;}
        obj(int n):np(new int[n]), len(n){}
        ~obj(){delete[] np;}
};

obj fun()
{
    obj a(5);
    // return std::move(a);
    return a;
}

int main(void)
{
    // B bb;
    // bb.printA();

    // D d;
    // d.func();

    fun();

    return 0;
}
