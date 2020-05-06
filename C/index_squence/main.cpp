#include<iostream>
#include<string>
#include<tuple>
#include"utils.hpp"


void try_index_sequence();


int main() {
    try_index_sequence();
    return 0;
}

void try_index_sequence() {
    using namespace std;

    auto para = make_tuple(1, 2, "apple");
    auto la = [](int a, int b, string s)->int {
        cout << "There is " << a + b << " " << s << " in total\n";
        return a + b;
    };

    int res;
    res = apply(la, para);
    cout << res << endl;
}

