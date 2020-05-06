#include<iostream>
// #include<stdio.h>
#include<iomanip>


int main()
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    double month{0};
    double avg{0};

    for (int i{0}; i < 12; i++)
    {
        cin >> month;
        avg += month;
    }

    avg /= 12;
    cout << fixed << setprecision(2) << "$" << avg << "\n";
    // printf("$%.2f\n",avg);

    return 0;
}
