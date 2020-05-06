#include<iostream>
#include<algorithm>
#include <iterator>
#include <numeric>
#include<vector>


class Obj {
    public:
        Obj(int aa, int bb): a(aa), b(bb) {}
        int a;
        int b;
        void print() {std::cout << a << ", " << b << std::endl;};
};


void try_vector();
void try_common();


int main() {
    // try_vector();
    try_common();
    return 0;
}



void try_vector() {
    using namespace std;

    vector<Obj> v;
    v.emplace_back(2,3);

    for (auto &el : v) el.print();
}


void try_common() {
    using namespace std;

    vector<int> v1(10);
    std::iota(v1.begin(), v1.end(), 1);
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, ", "));
    cout << endl;

    // vector<int> v2(std::move(v1));
    // std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, ", "));
    // cout << endl;

    vector<int> v2 = std::move(v1);
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, ", "));
    cout << endl;
}
