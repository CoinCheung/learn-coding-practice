#include<iostream>
#include<vector>
#include<cstdint>

using namespace std;

class QF {
 private:
    int32_t n;

 public:
    vector<int64_t> QFContract(int64_t a);
};

vector<int64_t> QF::QFContract(int64_t a) {
    vector<int64_t> factors;
    factors.reserve(50);
    int32_t e = 0;

    n = 0;
    while (a > 1) {
        for (int64_t i = 2; i <= a; ++i) {
            if (a%i == 0) {
                a = a/i;
                factors.push_back(i);
                break;
            }
        }
    }
    return factors;
}

int32_t main() {
    QF qf;
    int64_t number_base = 6541367001;
    // int64_t number = 3;
    for (int i{0}; i < 1000; i+=2) {
        int64_t number = number_base + i;
        auto res = qf.QFContract(number);
        if (res.size() == 2) {
            for (auto &el : res) cout << el << ", ";
        }
    }

    return 0;
}

