#include"head.hpp"
#include"meta.hpp"
#include<iostream>
#include<ctime>


long fab_rec(int N);
long fab_no_rec(int N);

int main(void)
{

    using namespace std;

    clock_t start, end;

    array<double> arr(4);
    arr.print();

    array<bool, 4> arr1(5);
    arr1.print();

    start = clock();
    cout << "fun is: " << fun<50>() << endl;
    end = clock();
    cout << "fun() time is: " << end - start << endl;
    
    start = clock();
    cout << "fab_rec() is: " << fab_rec(50) << endl;
    end = clock();
    cout << "fab_rec() time is: " << end - start << endl;

    start = clock();
    cout << "fab_no_rec() is: " << fab_no_rec(50) << endl;
    end = clock();
    cout << "fab_no_rec() time is: " << end - start << endl;

    // start = clock();
    // cout << "struct fib is: " << fib<10>::Result << endl;
    // end = clock();
    // cout << "struct fib time is: " << end - start << endl;
    //
    int nn = 10;
    int aa[nn];
    aa[1] = 99;
    cout << "aa is: " << aa[1] << endl;

    return 0;
}



long fab_rec(int N)
{
    if(N > 1)
        return fab_rec(N-1) + fab_rec(N-2);
    else if(N == 1)
        return 1;
    else if(N == 0)
        return 0;
}


long fab_no_rec(int N)
{
    if(N == 0)
        return 0;
    else if(N == 1)
        return 1;
    else if(N > 1)
    {
        long n1, n2, n3;

        n1 = 0;
        n2 = 1;
        for(int i=0; i<N-1; i++)
        {
            n3 = n1 + n2;
            n1 = n2;
            n2 = n3;
        }

        return n3;
    }
}
