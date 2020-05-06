#include<iostream>


int main(void)
{
    using namespace std;

    #if F
    cout << "macro F is defined: " << F << endl;

    #else
    cout << "no macro F is defined or its value is 0" << endl;
    #endif

    return 0;
}

