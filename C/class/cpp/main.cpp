#include"b.h"
#include<iostream>
#include <vector>
#include <functional>


using std::cout;
using std::endl;
using std::vector;

void try_bind();
void try_construct();

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

class Base {
    public: 
        virtual int operator()()=0;
};

class Derived1: public Base {
    public:
        int operator()() override {
            return 1;
        }
};

class Derived2: public Base {
    public:
        int operator()() override {
            return 2;
        }
};


class Strt {
    public:
        int a{0};
        int b{0};

        Strt(int a, int b): a(a), b(b) {}

        // Strt(Strt& s)=default;
        // Strt(Strt&& s)=default;
        // Strt(Strt& s) {a = s.a; b = s.b;}
        // Strt(Strt&& s) {a = s.a; b = s.b;}
};

int main(void)
{
    // B bb;
    // bb.printA();

    // D d;
    // d.func();

    // fun();

    // vector<Base> list;
    // list.push_back(Derived1());
    // list.push_back(Derived2());

    // Strt s;
    // Strt s0(s);
    Strt s1(2, 3);
    Strt s2(s1);
    // Strt s3(Strt(2, 3));
    try_bind();
    try_construct();

    return 0;
}

class C {
    public:
        int a{0};
        int b{0};
        void func() {cout << a << endl;}
};

void try_bind() {

    C c;
    c.a = 10;
    auto f = std::bind(&C::func, &c);
    f();
}

class DD {
    public:
        int a{0};
        int b{0};

        DD(int a, int b): a(a), b(b) {}

        // DD(Strt& s)=default;
        // DD(Strt&& s)=default;
        // DD(Strt& s) {a = s.a; b = s.b;}
        // DD(Strt&& s) {a = s.a; b = s.b;}
};

void try_construct() {
    DD d1(1, 2);
    DD d2(d1);
    cout << d2.b << endl;

}
