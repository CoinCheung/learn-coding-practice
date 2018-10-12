#include<future>
#include<chrono>
#include<iostream>


void try_async();
int thread_func(int a, int b);


int main() {
    try_async();
    return 0;
}

int thread_func(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(5)); 
    return a + b;
}

void try_async() {
    using namespace std;

    std::future_status status;
    // std::future<int> fut = std::async(std::launch::async, thread_func, 1, 2);  // 两个选项, future 构造
    std::shared_future<int> fut = std::async(std::launch::deferred, thread_func, 2, 3);  // 两个选项, future 构造
    cout << fut.get() << endl;
    while (true) {
        status = fut.wait_for(std::chrono::seconds(1));  // 三种 wait 方法,不同状态意思 
        if (status == std::future_status::deferred) cout << "not ready" << endl;
        else if (status == std::future_status::timeout) cout << "timeout" << endl;
        else {
            cout << "result is: " << fut.get() << endl; // fut.get结果
            break;
        }
    }
}

