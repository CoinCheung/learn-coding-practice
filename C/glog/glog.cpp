#include<glog/logging.h>
#include<iostream>

int main() {
    using namespace std;

    CHECK(false) << "error error" << endl;

    return 0;
}
