#include<iostream>


class B
{
    public:
        char a;
        int b;
        ~B(){std::cout << "deconstructing B" << std::endl;}
};

class A
{
    public:
        int a;
        char b;
        A(B& bbb){a = 999; b = 'd';}
        A(int aa, char bb): a(aa), b(bb){}
        ~A(){}
};


class C: public B
{
    public:
        double c;
        C(char a, int b, double c):c(c),B{a,b}{}
};


void try_cast();

int main()
{

    using namespace std;

    // cout << sizeof(struct A) << endl;
    // cout << sizeof(struct B) << endl;
    
    try_cast();

    // cout << try_cast->iii << endl;

    return 0;
}



void try_cast()
{
    using namespace std;

    static int iii = 44;
    iii += 1;

    A* a = new A{1,'a'};
    B b{'b',97};

    // cout << a->a << ", " << a->b << endl;
    cout << b.a << ", " << b.b << endl;

    A *c = reinterpret_cast<A*>(&b);
    cout << c->a << ", " << c->b << endl;

    A d{static_cast<A>(b)};
    cout << d.a << ", " << d.b << endl;


    C cc{'c',3, 4.3};

    B bbb = static_cast<B>(cc);
    cout << bbb.a << ", " << bbb.b << endl;

    B* bb = new B{'b', 2};
    C* ccc = static_cast<C*>(bb);

    cout << ccc->a << ", " << ccc->b << ", " << ccc->c << endl;

    A* ra = new A{98, 'a'};
    B* rb = reinterpret_cast<B*>(ra);
    cout << rb->a << ", " << rb->b << endl;

    int i = 1;
    // double ii = reinterpret_cast<double>(i);
    

    char input;
    cin >> input;
    // int aa = 10;
    // char bb = 'a';
    //
    // int cc;
    // cc = static_cast<int>(bb);
    // cout << cc << endl;

}
