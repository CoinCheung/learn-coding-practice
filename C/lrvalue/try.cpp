#include<iostream>

using namespace std;


class A
{
    public:
        A(int n1, int n2):a(n1),b(n2){};
        A(A& a){std::cout << "left ref constructor"<< std::endl;}
        A(A&& a){std::cout << "right ref constructor"<< std::endl;}
        int a;
        int b;
};


class B
{
    public:
        B(int n1, int n2): c(n1), d(n2){}
        int c;
        int d;
};

// int fun(A std::move(a), B std::move(b))
int fun(A&& a, B b)
{
    return a.a + b.c;
}


A funcA(A a)
{
    A aa(a);
    return aa;
}

class D {
    public: 
        int a{0};
        int b{0};

        // D(int a, int b): a(a), b(b) {}
        // D(D& d) {a = d.a;b = d.b;}
        // D(D&& d) {a = d.a;b = d.b;}
};

int main()
{
    A aa(1,2);
    B bb(3,4);

    // int re = fun(aa,std::move(bb));
    // A& ar = std::move(aa);
    // A&& ar = std::move(aa);
    A&& ar = funcA(aa);
    // fun(ar, bb);
    // A mmm =
        // funcA(funcA(aa));
        // funcA(std::move(aa));
        // funcA(ar);
    // A mmm(aa);
    // int re = fun(A(ar),B(2,3));
    // fun(aa,bb);

    // cout << re << endl;

    // D d1(2, 3);
    D d1{2, 3};
    D d2(d1);
    cout << d1.a << endl;
    cout << d2.a << endl;
    return 0;
}


