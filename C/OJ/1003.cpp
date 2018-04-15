#include<iostream>


int main()
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    double c;
    double n;
    double res;

    while (true)
    {
        cin >> c;
        if (c == 0.00)
            break;

        n = 2;
        res = 0.5;
        while (res < c)
        {
            n ++;
            res += 1 / n;
        }

        cout << static_cast<int>(n - 1) << " card(s)\n";
    }


    return 0;
}
