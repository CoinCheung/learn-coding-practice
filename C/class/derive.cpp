#include<iostream>


class A
{
    public:
        void print();
};

void A::print()
{
    using namespace std;

    cout << "class A method" << endl;
}


class B: A
{
    public:
        void print();
};

void B::print()
{
    using namespace std;

    cout << "class B method" << endl;
}


class C: B
{
    public:
        int aaa;
        // void print(){std::cout << "class C method" << std::endl;}
};

int main()
{
    C c;

    c.print();

    return 0;
}


