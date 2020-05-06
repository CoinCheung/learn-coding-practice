#include<iostream>

using std::cout;
using std::endl;



class A {
    public:
        A() {cout << "A()" << endl;}
        A(const A&) {cout << "A(A&)" << endl;}
};



void do_it();

int main() {
    do_it();

    return 0;
}


void do_it() {
    A a;
    A a1 = a;
    a1 = a;

}
