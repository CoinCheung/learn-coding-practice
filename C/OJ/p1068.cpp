#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void solve();


int main() {
    std::ios_base::sync_with_stdio(false);
    solve();
    return 0;
}


void solve() {
    int t;
    int n;
    int p1{0}, p2{0};
    vector<int> ps(1024);
    vector<int> res(1024);
    cin >> t;
    for (int i{0}; i < t; ++i) {
        cin >> n;
        int pos = 0;
        for (int j{0}; j < n; ++j) {
            cin >> p1;
            for (int k{0}; k < (p1-p2); ++k) {
                ps[pos++] = 0;
            }
            ps[pos++] = 1;
            p2 = p1;
        }
        // 
        for (int j{0}; j < pos; ++j) {
            if (ps[j] == 1) {
                int jj = j;
                int val = 1;
                int max_val = 1;
                while (val != 0) {
                    --jj;
                    if (ps[jj] == 0) {
                        --val;
                    } else {
                        ++val;
                        ++max_val;
                    }
                }
                cout << max_val << ' ';
            }
        }
        cout << endl;
    }
}
