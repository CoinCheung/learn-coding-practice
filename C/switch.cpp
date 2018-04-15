#include<iostream>
#include<array>


void fun();

int main()
{
    fun();
    return 0;
}


void fun()
{
    using namespace std;

    array<int, 5> ar;

    int i{0};
    for (auto& el:ar)
        el = (5-i++-1);

    for (auto& el:ar)
        cout << el << ", ";
    cout << endl;

    int temp;
    // for (auto& el:ar)
    for (int i{0}; i<5; i++)
    {
        if (i != ar[i])
        {
            temp = ar[ar[i]];
            ar[ar[i]] = ar[i];
            ar[i] = temp;
        }

    }
    for (auto& el:ar)
        cout << el << ", ";
    cout << endl;

}

