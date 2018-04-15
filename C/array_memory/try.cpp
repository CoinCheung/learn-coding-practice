#include<iostream>
#include<memory>
#include<array>


void try_memory();


int main()
{
    try_memory();

    return 0;
}



void try_memory()
{
    using namespace std;

    int (*ppp)[8] = new int[8][8]();
    delete[] ppp;

    shared_ptr<int[][8]> sp(new int[8][8]);

    for(auto i{0}; i<8; i++)
        for(auto j{0}; j<8; j++)
            sp[i][j] = i*j;

    for(auto i{0}; i< 8; i++)
        cout << sp.get()[i][i] << endl;

    int arr2[8][8];
    for(auto& arr:arr2)
        for(auto& el:arr)
            el = 8*8;
    for(auto& arr:arr2)
        for(auto& el:arr)
            cout << el << endl;

    cout << arr2[0] << endl;

    int *ip = arr2[0];
    cout << *(ip+10) << endl;

    const int M = 4;
    const int N = 4;

    std::array<std::array<int,M>, N> arr3;
    std::array<std::array<int,M>, N> arr4();
    std::array<std::array<int,M>, N> arr5{1,2,3,2,3,4};

    for(auto& arrs:arr5)
    {
        for(auto& arr:arrs)
            cout << arr << ',';
        cout << endl;
    }


}

