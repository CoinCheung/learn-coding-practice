#include<iostream>


class Obj {
    public:
        Obj(int aa, int bb): a(aa), b(bb) {}
        Obj(const Obj& o) {a = o.a; b = o.b;std::cout << "copying" << std::endl;}
        Obj(Obj&& o) {a = o.a; b = o.b;std::cout << "moving" << std::endl;}
        int a;
        int b;
};


const int & Min(const int& a, const int& b);

Obj& Min(Obj &o1, Obj &o2);


int main() {
    using namespace std;

    int a = 1;
    int b = 2;

    auto&& val = Min(a, b);
    cout << val << endl;

    auto o1 = Obj(1,1);
    auto o2 = Obj(2,2);

    Obj res = Min(o1, o2);

    cout << res.a << endl;
    res.a = 100;
    cout << res.a << endl;
    cout << o1.a << endl;
    cout << o2.a << endl;

    return 0;
}


const int & Min(const int& a, const int& b) {
    return a < b ? a : b;
}

Obj& Min(Obj &o1, Obj &o2) {
    if (o1.a > o2.a) {
        return o1;
    } else {
        Obj oo2(o2);
        return oo2;
        // return o2;
    }
}
