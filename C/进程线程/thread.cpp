#include<thread>
#include<iostream>
#include<string>
#include <future>
#include <functional>
#include <chrono>

using namespace std;
void thread_fun(std::string&&, std::string&);
void try_async();
void try_bg_thread();



int main()
{
    using namespace std;

    string ss("thread string");
    string ss2("thread string");

    thread t1(thread_fun, std::move(ss), std::ref(ss2));
    
    t1.join();

    try_async();

    try_bg_thread();

    return 0;
}

void thread_fun(std::string&& str1, std::string& str2)
{
    using namespace std;

    cout << std::this_thread::get_id() << str1 << ", " << str2 << endl;
}

class C {
    public: 
        int a{0};
        void func() {cout << a << endl;}
};

void try_async() {
    C c;
    c.a = 3;
    // std::future<void> f = std::async(std::launch::async, c.func);
    std::future<void> f = std::async(
        std::launch::async, std::bind(&C::func, &c));
    // std::future<void> f = std::async(
    //     std::launch::async, &C::func, &c);
}


class CC {
public:
    bool stop{false};
    CC () {
        auto fun = [&] {
            cout << "before enter loop\n";
            while (!stop) {}
            cout << "after enter loop\n";
        };
        std::thread th_bg(fun);
        th_bg.detach();
    }
    ~CC() {
        cout << "set stop to true\n";
        stop = true;
    }
};

void try_bg_thread() {
    CC* c = new CC();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout << "others" << endl;
    delete c;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
