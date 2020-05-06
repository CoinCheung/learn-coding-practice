#include<iostream>


void printchar(const char *str)
{
    using namespace std;

    char* cp;
    cp = const_cast<char*>(str);
    cout << "origin string is: " << str << endl;
    cp[0] = 'd';
    cout << "after changed string is: " << cp << endl;

}


void fun()
{
    using namespace std;

    const int n = 10;
    const int* constp;
    int*  np;

    constp = &n;
    cout << "*constp is: " << *constp << endl;
    np = const_cast<int*>(constp);
    cout << "*np is: " << *np << endl;

    (*np) ++;
    cout << "*np is: " << *np << endl;
    cout << "*constp is: " << *constp << endl;

    const char* s = "nimabi";
    // printchar(s);

    constp = new int[5];

    int  nn = 10;
    constp = &nn;
    nn++;
    // (*constp)++;

    const int& a1 = nn;
    int& ap = const_cast<int&>(a1);
    cout << "ap:" << ap << endl;
    // ap = const_cast<int*> (&a1);
    ap ++;
    cout << "ap:" << ap << endl;

}


int main(void)
{
    fun();

    return 0;
}
