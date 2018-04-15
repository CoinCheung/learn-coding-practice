#include<iostream>
#include"list.h"


int main(void)
{
    using namespace std;

    list li;

    cout << "traverse invert:" << endl;
    cout << "before invert:" << endl;
    for(int i{0}; i<1; i++)
        li.add(i);
    li.print();

    cout << "after invert:" << endl;
    li.invert_traverse();
    // li.invert_copy_new();
    li.print();


    return 0;
}
