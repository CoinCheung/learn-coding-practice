#include<vector>
#include<iostream>

using std::cout;
using std::endl;
using std::vector;

class Solution {
 public:
    // slow
    // int numTrees(int n) {
    //     if (n == 0) return 1;
    //     if (n == 1) return 1;
    //     int res = 0;
    //     for (int i{0}; i < n; ++i) {
    //         res += numTrees(i) * numTrees(n - 1 - i);
    //     }
    //     return res;
    // }
    int numTrees(int n) {
        vector<int> count(n+1, 0);
        count[0] = 1;
        count[1] = 1;
        for (int i{2}; i <= n; ++i) {
            for (int j{0}; j < i; ++j) {
                count[i] += count[j] * count[i-1-j];
            }
        }
        return count[n];
    }
};

int main() {
    Solution sol;
    cout << sol.numTrees(18) << endl;
    return 0;
}
