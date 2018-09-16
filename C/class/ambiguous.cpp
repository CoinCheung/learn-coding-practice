#include<iostream>


using std::cout;
using std::endl;


class A {
    public:
        void print() {cout << "print function of A\n";}
};


class B {
    public:
        void print() {cout << "print function of B\n";}
};


class C: public A, public B {

};


class D: public A, public C {

};


class left: public A {
    public:
        // void print() {cout << "left function\n";}
};


class right: public A {
    public:
        // void print() {cout << "right function\n";}
};


class son: public left, public right {
    public:
        // void print() {cout << "son function\n";}

};


int main() {

    C c;
    c.A::print();

    D d;
    // d.A::print();
    
    son s;
    s.left::print();
    s.right::print();
    // s.A::print();
    // s.print();
    // s.left::A::print();

    s.left::print();

    return 0;
}
