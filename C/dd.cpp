#include<iostream>
#include<valarray>
#include<vector>

extern "C"
{
#include"header.h"
#include"malloc.h"
}




using namespace std;

// extern "C"
// {
    
    void printB();
// }


class A
{
    public: 
        int a;
        int b;
        virtual void fun(){cout << a << endl;}
        // virtual void fun(int a){cout << a <<endl;}
        void func(int a, int b){cout << " func() of base" << endl;}
};

class B: public A
{
    public:
        int a;
        // void fun(){cout << a <<endl;}
        void func(int a){cout << " func() of derived" << endl;}
};


void func(int a[])
{
    cout << a[0] << endl;
    cout << a[1] << endl;
}


int main(){

    int *p = new int[20];
    int (*a)[2][5];
    
    a = (int(*)[2][5])p;

    for(int i = 0; i < 20; i++)
        p[i] = i;

    cout << a[1][1][3] <<endl;

    // A a;
    // B b;
    // A *p;

    // a.a = 1;
    // a.b = 2;
    // b.a = 3;
    // b.A::a = 4;
    // p = &b;

    // p->fun();
    // p->fun(1);
    // b.fun(1);
    // b.A::fun();
    // a.fun();
    // cout <<  << endl;
    // b.fun();

    // int arr[10] = {1,2,3,4,5,6,7,8,9,0};
    // int size = 10;
    // valarray<int> arr(size);
    // valarray<int> arr;
    // arr = {1,2,3,4,5,6,7,8,9,0};

    // arr[3] = 333;

    // valarray<int> subarr = arr[std::slice(-2,4,-1)];
    // for(unsigned int i = 0; i < arr.size(); i++)
    //     cout << arr[i] << "  ";
    // cout << endl;
    //
    //
    // for(unsigned int i = 0; i < subarr.size(); i++)
    //     cout << subarr[i] << "  ";
    // cout << endl;
    //
    // std::slice sl(2,3,4);
    //
    //
    // cout << sl.start() << endl;
    //
    //
    // vector<double> vc;
    // cout << "vector: " << endl;
    // cout << vc.size() << endl;
    // vc.push_back(3.0);
    // cout << vc.size() << endl;
    // cout << vc[0] << endl;

    // func({2,3});

    // a.fun();
    // p->fun();
    //
    // b.func(1);
    // // b.func(1,2);
    // p->func(1,2);
    	
    // //	for(int i=0;i<13;i++){
    //
    // //		cout<<"this is "<<i<<endl;
    // //	}
    //
    // //print();
	// int a=3;
	// if(a==0)
	//     cout<<"a==0!"<<endl;
	// else if(a==1)
	//     cout<<"a==1"<<endl;
	// else if(a==2)
	//     cout<<"a==2"<<endl;
	// else
	//     cout<<"a==3"<<endl;
    //
    // printf("hello from printf in C in main\n");
    // // printA();
    //
    // const char *d = "dfdfs";
    // // const char *d;
    //
    // dd = d;
	//
    // printB();
    //
    // int (*aaa)[5];
    //
    // aaa = new int[4][5];
    // aaa[1][3] = 333;
    //
    // cout << aaa[1][3] << endl;
    // delete[] aaa;
    //
    // // aaa = (int(*)[5])malloc(sizeof(int)*20);
    // // free(aaa);
    //
    //
    // A *oa;
    // oa = new A;
    // oa->a = 3;
    // oa->b = 5;
    // cout << "oa->a before delete is" << oa->a <<endl;
    // delete oa;
    // cout << "oa->a after delete is" << oa->a <<endl;


	return 0;
}



void printB()
{

    // for( i = 0; i < 10; i++)
        printf("hello from printB in C\n");
        printA();
}
