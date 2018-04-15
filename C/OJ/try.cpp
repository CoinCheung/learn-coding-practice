#include<stdio.h>
#include<iostream>
#include<iomanip>


int main()
{
    using namespace std;

    double pi = 10.0/20;

    printf("%07.2f\n", 3.4);

    cout.precision(4);
    cout << 3.1415926 << "\n";

    cout << fixed << setprecision(4) << pi << "\n";

    return 0;
}
