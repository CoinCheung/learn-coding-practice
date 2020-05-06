#include<iostream>
#include<string>
#include<chrono>
#include<thread>


void try_chrono();


int main() {
    try_chrono();
    return 0;
}

void try_chrono() {
    using namespace std;

    chrono::high_resolution_clock::time_point tp_now = chrono::high_resolution_clock::now();
    std::time_t utp_now = chrono::high_resolution_clock::to_time_t(tp_now);
    cout << utp_now << endl;
    string str;
    std::this_thread::sleep_for(chrono::milliseconds(5000));
    str.assign(ctime(&utp_now));
    cout << str;
}

