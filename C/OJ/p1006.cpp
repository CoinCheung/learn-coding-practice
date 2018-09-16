#include<iostream>


int compute_r(int a, int b, int c);


int main()
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    int r1, r2, r3;
    int r;
    int p, e, i, d;
    int peak;

    r1 = compute_r(28, 33, 23);
    r2 = compute_r(23, 33, 28);
    r3 = compute_r(23, 28, 33);
    r = 23 * 28 * 33;

    int num{0};
    while (true)
    {
        num ++;
        cin >> p >> e >> i >> d;
        if ((p == -1) && (e == -1) && (i == -1) && (d == -1))
            break;
        peak = (p * r1 + e * r2 + r3 * i - d) % r;
        peak = (peak + r - 1) % r + 1;

        cout << "Case " << num << ": the next triple peak occurs in " << peak << " days.\n";
    }

    return 0;
}


int compute_r(int a, int b, int c)
{
    int res;
    int r1{a * b};

    int i{0};
    while (true)
    {
        i ++;
        res = r1 * i;
        if (res % c == 1)
            break;
    }

    return res;
}
