#include<glog/logging.h>
#include<iostream>
#include<cassert>
#include<memory>
#include<vector>

int main() {
    using namespace std;

    google::InitGoogleLogging("main");
    google::SetLogDestination(google::GLOG_INFO, "./myinfo");
    google::SetStderrLogging(google::INFO);

    LOG(INFO) << "INFO\n";
    LOG(WARNING) << "WARNING\n";
    LOG(ERROR) << "ERROR\n";

    shared_ptr<int> pt(new int(10));
    auto ptr = make_shared<vector<int>>(10);
    ptr = nullptr;
    cout << (ptr.get() == nullptr) << endl;
    // cout << pt.get() == nullptr << endl;
    CHECK_LE(1, 0) 
        << "triger equal\n";

    // CHECK(false) << "error error" << endl;

    return 0;
}
