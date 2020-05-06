
#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <chrono>
#include "blocking_queue.hpp"


int count = 0;
std::mutex mtx;

void push_queue(BlockingQueue<float>& q) {
    while (true) {
        q.push(count);
        // auto t = std::chrono::milliseconds(1000);
        // std::this_thread::sleep_for(t);
        {
            std::lock_guard<std::mutex> lock(mtx);
            ++count;
        }
    }
}

void print_queue(BlockingQueue<float>& q, int idx) {
    while (true) {
        auto t = std::chrono::milliseconds(1000);
        std::this_thread::sleep_for(t);
        float res = q.pop();
        std::cout << "thread " << idx << ": " << res << std::endl;
    }
}


void try_blocking_queue() {
    BlockingQueue<float> q;
    bool stop{false};
    auto fun = [&] {
        std::cout << "before entering loop\n";
        while (!stop) {
            q.push(1);
        }
        std::cout << "after entering loop\n";
    };
    std::thread t_bg(fun);
    t_bg.detach();
    // Some other tasks
    stop = true;
    // How could I shut it down before quit here, or could I simply let os do that?
}


int main() {
    BlockingQueue<float> q(32);
    std::future<void> f0 = std::async(std::launch::async, push_queue, std::ref(q));
    std::future<void> f1 = std::async(std::launch::async, print_queue, std::ref(q), 0);
    std::future<void> f2 = std::async(std::launch::async, print_queue, std::ref(q), 1);

    f0.get();
    f1.get();
    f2.get();
    try_blocking_queue();

    return 0;
}
