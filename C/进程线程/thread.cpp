#include<thread>
#include<iostream>
#include<string>

void thread_fun(std::string&&, std::string&);

int main()
{
    using namespace std;

    string ss("thread string");
    string ss2("thread string");

    thread t1(thread_fun, std::move(ss), std::ref(ss2));
    
    t1.join();

    return 0;
}

void thread_fun(std::string&& str1, std::string& str2)
{
    using namespace std;

    cout << std::this_thread::get_id() << str1 << ", " << str2 << endl;
}
