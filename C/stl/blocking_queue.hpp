
#ifndef _BLOCKING_QUEUE_
#define _BLOCKING_QUEUE_

#include <queue>
#include <mutex>
#include <condition_variable>


template<typename T>
class BlockingQueue {
public:
    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;
    std::queue<T> queue;
    size_t capacity{5};

    BlockingQueue()=default;
    BlockingQueue(int cap):capacity(cap) {}
    BlockingQueue(const BlockingQueue&)=delete;
    BlockingQueue& operator=(const BlockingQueue&)=delete;

    void push(const T& data) {
        std::unique_lock<std::mutex> lock(mtx);
        while (queue.size() >= capacity) {
            not_full.wait(lock, [&]{return queue.size() < capacity;});
        }
        queue.push(data);
        not_empty.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        while (queue.empty()) {
            not_empty.wait(lock, [&]{return !queue.empty();});
        }
        T res = queue.front();
        queue.pop();
        not_full.notify_all();
        return res;
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(mtx);
        return queue.empty();
    }

    size_t size() {
        std::unique_lock<std::mutex> lock(mtx);
        return queue.size();
    }

    void set_capacity(const size_t capacity) {
        this->capacity = (capacity > 0 ? capacity : 10);
    }
};


#endif
