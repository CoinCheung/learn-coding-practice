#include<vector>
#include<memory>
#include<iostream>


class Base
{
    public:
        virtual void forward(){std::cout<<"Base forward()"<<std::endl;};
        virtual void backward(){std::cout<<"Base backward()"<<std::endl;};
};


class Derived1:public Base
{
    public:
        int data1;
        Derived1():data1(1){}
        void forward(){std::cout<<"Derived1 forward(): data1 is: "<<data1<<std::endl;};
        void backward(){std::cout<<"Derived1 backward()"<<std::endl;};
};


class Derived2:public Base
{
    public:
        int data2;
        Derived2():data2(2){}
        void forward(){std::cout<<"Derived2 forward(): data2 is: "<<data2<<std::endl;};
        void backward(){std::cout<<"Derived2 backward()"<<std::endl;};
};


std::vector<std::shared_ptr<Base>> fun()
{
    using namespace std;

    vector<shared_ptr<Base>> vec;

    vec.reserve(10);

    for(auto i{0}; i<10; i++)
        if(i%2==0)
            vec.push_back(shared_ptr<Base>(new Derived1()));
        else
            vec.push_back(shared_ptr<Base>(new Derived2()));

    shared_ptr<Base> b;
    b.reset(new Derived1());
    // b->forward();

    return vec;
}


int main(void)
{
    using namespace std;

    vector<shared_ptr<Base>> vec;

    vec = fun();
    for(auto& ele:vec)
    {
        ele->forward();
    }


    return 0;
}




