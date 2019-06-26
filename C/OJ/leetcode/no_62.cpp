#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;


class Solution {
 public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> res(m, vector<int>(n, 0));
        res[0][0] = 1;
        for (int i{0}; i < m; ++i) {
            for (int j{0}; j < n; ++j) {
                if (i-1 >= 0) {
                    res[i][j] += res[i-1][j];
                }
                if (j-1 >= 0) {
                    res[i][j] += res[i][j-1];
                }
            }
        }
        return res[m-1][n-1];
    }

    // int uniquePaths(int m, int n) {
    //     int x = 0, y = 0;
    //     int count = 0;
    //     traverse(x, y, m, n, count);
    //     return count;
    // }
    //
    // void traverse(int x, int y, int m, int n, int& count) {
    //     if ((x == m-1) && (y == n-1)) {
    //         count += 1;
    //         return;
    //     }
    //     if (x >= m || y >= n) {
    //         return;
    //     }
    //     traverse(x + 1, y, m, n, count);
    //     traverse(x, y + 1, m, n, count);
    // }
};


int main() {
    Solution sol;
    int m{3}, n{2};
    int res = sol.uniquePaths(m, n);
    cout << res << endl;
    return 0;
}
