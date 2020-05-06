#include<iostream>
#include<cmath>

#define PI 3.141592653
#define PI_half 1.5707963265

int main()
{
    using namespace std;

    std::ios_base::sync_with_stdio(false);

    int len;
    double x, y;
    double area;
    int time;

    cin >> len;
    for (int i{1}; i <= len; i++)
    {
        cin >> x >> y;
        area = PI_half * (x * x + y * y);
        time = ceil(area / 50);
        // cout << time << ", " << ceil(time);
        cout << "Property " << i << ": This property will begin eroding in year " << time << ".\n";
    }
    cout << "END OF OUTPUT.\n";

    return 0;
}
