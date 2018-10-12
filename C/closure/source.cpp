#include<iostream>
#include<vector>
#include<functional>


void try_closure();
auto func();


int main() {
    try_closure();
    return 0;
}


void try_closure() {
    using namespace std;

    int state = 9;
    auto f = [=]() {std::cout << state+1 << std::endl;};
    vector<std::function<void(void)>> fv;

    auto f1 = [] {cout << "f1" << endl;};
    fv.push_back(f);
    fv.push_back(f1);
    
    for (auto &f : fv) f();

    

    // auto fun = func(3);
    // fun();
}

// auto func(int state) {
//     std::function<void(void)> f = [=]() {std::cout << state+1 << std::endl;};
//     return f;
// }
