// #include<stdio.h>
// #include<iostream>

namespace my
{
    #include<stdio.h>
    // using namespace std;
    // int cout = 5;
    // // using std::endl;
    // int m = 4;
    void foo()
    {
        fputs("fffff\n",stdout);
    }
}

// using namespace std;

void print()
{
    // fputs("print by cpp in print()\n", stdout);
    // std::cout<<"print by cout in print()"<<my::m<<std::endl;
}

    // using my::foo;

int main()
{
    int printf = 5;
    
    // fprintf(stdout,"number is %d", printf);
    // fputs("print by cpp\n", stdout);
    // cout<<"print by cout"<<endl;
    // print();
    my::foo();
    // fprintf(stdout, "number is %d\n",my::cout);
    // std::cout<< "enen"<<endl;
}
