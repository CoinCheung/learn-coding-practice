#include<iostream>
#include<memory>


void try_list_init();


int main()
{

    try_list_init();
    
    return 0;
}



void try_list_init()
{
    using namespace std;

    shared_ptr<int> p(new int[10]{0});

    for(int i{0}; i<10; i++)
        cout << *(p.get()+i) << endl;

    int *hp = new int{8};
    cout << *hp << endl;


    /* ========= */
    cout << "2018.02.28" << endl;

    // struct strc{strc(int aa, char bb):a(aa),b(bb){}int a; char b;};
    struct strc{int a; char b;}; 
    strc stra={10, 'a'};
    strc strb{1,'b'};

    cout << "stra is:" << stra.a << "," << stra.b << endl;
    cout << "strb is:" << strb.a << "," << strb.b << endl;

    shared_ptr<int> p1(new int[10]{1,2,3});
    for(int i{0}; i<10; i++)
        cout << p1.get()[i] << endl;;


}
