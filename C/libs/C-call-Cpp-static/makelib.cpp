#include<iostream>


extern "C"
{
void fun()
{
    using namespace std;

    cout << "in the static lib" << endl;
}

}
