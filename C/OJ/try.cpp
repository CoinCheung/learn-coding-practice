#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include<array>

class CLS {
    public:
        int a;
        CLS(int val): a(val){}
};

int main()
{
    using namespace std;

    double pi = 10.0/20;

    printf("%07.2f\n", 3.4);

    cout.precision(4);
    cout << 3.1415926 << "\n";

    cout << fixed << setprecision(4) << pi << "\n";

    array<int, 10> arr;
    arr[9] = 9;

    int a[10];

    vector<int> vi(5);
    vector<int> v2(5);
    int i{0};
    for (auto& el: vi)
        el = i++;
    v2.assign(vi.begin(), vi.end());
    for (auto& el:v2)
        cout << el << ", ";
    cout << endl;

    vi[100] = 8;
    cout << vi[100] << endl;
    vi.resize(1000);

    pair<int, int> p1{1,2}, p2{3,4};
    p2 = p1;
    cout << p1.first << ", " << p1.second << endl;
    cout << p2.first << ", " << p2.second << endl;
    p1.first = 888;
    cout << p1.first << ", " << p1.second << endl;
    cout << p2.first << ", " << p2.second << endl;

    vector<CLS> v11(5, CLS(3));
    vector<CLS> v22(10, CLS(4));

    cout << "before" << endl;
    cout << &v11 << endl;
    cout << &v22 << endl;
    cout << &v11[0] << endl;
    cout << &v22[0] << endl;
    vi = vector<int>(std::move(v2));
    cout << "after" << endl;
    cout << &v11 << endl;
    cout << &v22 << endl;
    cout << &v11[0] << endl;
    cout << &v22[0] << endl;

    cout << v11[0].a << endl;
    cout << v22[0].a << endl;

    return 0;
}




#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<iterator>
#include<stdio.h>  // for EOF
int main() {
    using namespace std;
    std::ios_base::sync_with_stdio(false);

    int n;

    while (cin >> n) {

        // ;
        // if (n == EOF) exit(0);
        cout << n;

        while (n != 0) {
            cin >> n;
            cout << n;
        }

        while (cin >> n) {
            if (n == 0) break;
            cout << n;
        }
    }
    return 0;
}

