#include<functional>
#include<iostream>


void try_function();
void fun_inner();

class funcObj {public: void operator()() {std::cout << "func obj" << std::endl;}};

class ObjMember {
    public:
        static void fun1() {std::cout << "static member" << std::endl;}
        void fun2() {std::cout << "not static member" << std::endl;}
};


int main() {
    try_function();

    return 0;
}

void fun_inner() {
    using namespace std;
    cout << "func" << endl;
};

void try_function() {
    using namespace std;
    auto f1 = []{cout << "lambda" << endl;};
    funcObj fo;
    
    std::function<void(void)> f;
    f = f1;
    f();
    f = fun_inner;
    f();
    f = fo;
    f();
    f = funcObj();
    f();

    f = ObjMember::fun1;
    f();
    // ObjMember om;
    // f = om.fun2;
    // f();

    std::function<int(int, int)> ff;
    ff = [](int a, int b)->int {return a + b;};
    cout << ff(1, 2) << endl;
}
