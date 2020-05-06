#include"b.h"
#include"a.h"
#include<iostream>

using std::cout;
using std::endl;

void B::funB()
{
    cout << "funB()" << endl;
}

void B::printA()
{
    A a;
    a.funA();
}
