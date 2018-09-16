#include<iostream>
#include<stdio.h>

using std::cout;
using std::endl;


int main() {
    float a;
    int b;
    unsigned int c;

    a = 19.9;
    b = a * 10;
    cout << b << endl;
    b = a * 100;
    cout << b << endl;
    c = a * 10;
    cout << c << endl;
    c = a * 100;
    cout << c << endl;

    a = 179723554568;
    // a = 179723554568.00000;
    b = (int)a;
    c = (int)a;
    // a *= 11189775539951897755399555897755399553911.9999999;
    cout << b << endl;
    cout << c << endl;
    printf("%x\n", b);

    unsigned char aa = 1;
    unsigned int bb = aa;
    printf("%08x\n", bb);
    char aa1 = -1;
    unsigned int bb1 = aa1;
    printf("%x\n", bb1);
    aa1 = -1;
    printf("%x\n", aa1);
    printf("%x\n", (unsigned char)aa1);

    unsigned int cc;
    cc = (1 << 31) + 1;
    cout << "here\n";
    printf("%d\n", (int)cc);
    printf("%x\n", cc);

    int dd;
    dd = 0x8fffffff;
    printf("%d\n", (char)dd);



    return 0;
}

