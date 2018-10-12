#include<iostream>
#include<algorithm>
#include<vector>


class Obj {
    public:
        Obj(int aa, int bb): a(aa), b(bb) {}
        int a;
        int b;
        void print() {std::cout << a << ", " << b << std::endl;};
};


void try_vector();


int main() {
    try_vector();
    return 0;
}



void try_vector() {
    using namespace std;

    vector<Obj> v;
    v.emplace_back(2,3);

    for (auto &el : v) el.print();
}

