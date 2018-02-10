#include<iostream>
#include<array>



void array_example();

int main(void)
{

    array_example();

    return 0;
}


void array_example()
{
    using namespace std;

    array<array<int, 3>, 3> a{{{1,2,2},{4,5,6},{7,8,9}}};

    for(auto arr:a)
    {
        for(auto val:arr)
            cout << "number is: " << val << endl;

    }
}



