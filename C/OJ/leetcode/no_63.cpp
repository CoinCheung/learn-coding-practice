#include<vector>
#include<iostream>

using std::vector;
using std::cout;
using std::endl;

class Solution {
 public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int64_t>> res(m, vector<int64_t>(n, 0));

        if (obstacleGrid[0][0] == 1) {
            return 0;
        }

        res[0][0] = 1;
        for (int i{0}; i < m; ++i) {
            for (int j{0}; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    continue;
                }
                if (i-1 >= 0) {
                    res[i][j] += res[i-1][j];
                }
                if (j-1 >= 0) {
                    res[i][j] += res[i][j-1];
                }
                // if ((i-1 >= 0) && (obstacleGrid[i-1][j] != 1)) {
                //     res[i][j] += res[i-1][j];
                // }
                // if ((j-1 >= 0) && (obstacleGrid[i][j-1] != 1)) {
                //     res[i][j] += res[i][j-1];
                // }
            }
        }
        return res[m-1][n-1];
    }
};

int main() {
    vector<vector<int>> grids(3, vector<int>(3, 0));
    grids[1][1] = 1;
    Solution sol;
    int res = sol.uniquePathsWithObstacles(grids);
    cout << res << endl;
    return 0;
}
