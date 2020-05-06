#include<iostream>

using std::cout;
using std::endl;


class A
{
    private:
        int a;
    public:
        int aa;
        void print();
        A();
        A(A&);
};

void A::print()
{
    using namespace std;

    cout << "class A method" << endl;
}

A::A() {

}

A::A(A& var_a) {
    a = var_a.a;
}


class B: public A
{
    public:
        void print();
        B(B&);
        B();
};

B::B(B& b) {
    // a = b.a;
}

B::B() {
}

void B::print()
{
    using namespace std;

    cout << "class B method" << endl;
}


class C: public B
{
    private:
        int ccc;
    public:
        int aaa;
        // void print(){std::cout << "class C method" << std::endl;}
        void fun(C&);
        void set_private(int val);
};


void C::set_private(int val) {
    ccc = val;
}


void C::fun(C& c) {
    std::cout << c.ccc << std::endl;
}


class D: public A {
    
};


class Base1 {
    public:
        virtual void fun1() {cout << "fun1\n";}
        // virtual ~Base1() {}
};

class Base2 {
    public:
        virtual void fun2() {cout << "fun2\n";}
        virtual ~Base2() {}
};

class Derive: public Base1, public Base2 {
    public:
        virtual void fun1() {cout << "fun_derive_2\n";}
        virtual void fun3() {cout << "fun_derive_3\n";}
};


int main()
{
    C c;

    c.A::print();
    B b;

    C cc;

    c.set_private(888);
    cc.fun(c);
    cc.print();

    D d;
    // d.A::print();

    Base1 *b1 = static_cast<Base1*>(new Derive);
    b1->fun1();

    delete static_cast<Derive*>(b1);


    return 0;
}


