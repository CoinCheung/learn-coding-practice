#include<iostream>
#include<vector>

using namespace std;

class QF {
 private:
    int n;

 public:
    vector<int64_t> QFContract(int64_t a);
};

vector<int64_t> QF::QFContract(int64_t a) {
    vector<int64_t> factors;
    factors.reserve(50);

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

int main() {
    QF qf;
    int64_t number_base = 6541367001;
    // int64_t number = 3;
    for (int i{0}; i < 1000; i+=2) {
        int64_t number = number_base + i;
        // cout << "\nprocessing: " << number << endl;
        auto res = qf.QFContract(number);
        if (res.size() == 2) {
            cout << number << ": ";
            for (auto &el : res) cout << el << ", ";
            cout << endl;
        }
    }

    return 0;
}


