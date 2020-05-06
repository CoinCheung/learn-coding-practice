#include<iostream>

using namespace std;


class Base {public: int base; virtual void base_fun() {}};
class Derived: public Base {int der; void base_fun() {cout << "fuck you\n";}};

int main() {
    Base *bp;
    // bp = new Derived;  // 这样有错, 无法通过类检查型
    bp = dynamic_cast<Base*> (new Derived);
    bp->Base::base_fun();
    return 0;
}
