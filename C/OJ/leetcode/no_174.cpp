#include<vector>
#include<iostream>
#include<limits>

using std::vector;
using std::numeric_limits;
using std::cout;
using std::endl;


class Solution {
 public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = 0;
        if (m > 0) {
            n = dungeon[0].size();
        }
        vector<vector<int>> need(m, vector<int>(n, 0));
        need[m-1][n-1] = 1 - dungeon[m-1][n-1];
        // cout << need[m-1][n-1] << endl;
        if (need[m-1][n-1] <= 0) {
            need[m-1][n-1] = 1;
        }
        // cout << need[m-1][n-1] << endl;
        for (int i{m-1}; i >= 0; --i) {
            for (int j{n-1}; j >= 0; --j) {
                if (i == m-1 && j == n-1) {
                    continue;
                }
                int s1{10000000}, s2{10000000};
                if (i < m-1) {
                    s1 = need[i+1][j];
                }
                if (j < n-1) {
                    s2 = need[i][j+1];
                }
                if (s1 < s2) {
                    need[i][j] = s1 - dungeon[i][j];
                } else {
                    need[i][j] = s2 - dungeon[i][j];
                }
                if (need[i][j] <= 0) {
                    need[i][j] = 1;
                }
            }
        }
        
        // for (int i{0}; i < m; ++i) {
        //     for (int j{0}; j < n; ++j) {
        //         cout << need[i][j] << ", ";
        //     }
        //     cout << endl;
        // }
        return need[0][0];
    }
    // int calculateMinimumHP(vector<vector<int>>& dungeon) {
    //     int m = dungeon.size(), n = 0;
    //     if (m > 0) {
    //         n = dungeon[0].size();
    //     }
    //     vector<vector<int>> health(m, vector<int>(n, 0));
    //     health[0][0] = dungeon[0][0];
    //     vector<vector<int>> mins(m, vector<int>(n, 0));
    //     mins[0][0] = dungeon[0][0];
    //     if (mins[0][0] > 0) {
    //         mins[0][0] = 0;
    //     }
    //     for (int i{0}; i < m; ++i) {
    //         for (int j{0}; j < n; ++j) {
    //             if (i == 0 && j == 0) {
    //                 continue;
    //             }
    //             int st1 = numeric_limits<int>::min();
    //             int st2 = numeric_limits<int>::min();
    //             int pre1 = st1, pre2 = st1;
    //             int min1 = st2, min2 = st2;
    //             int min;
    //             if (i > 0) {
    //                 min1 = mins[i-1][j];
    //                 pre1 = health[i-1][j];
    //             }
    //             if (j > 0) {
    //                 min2 = mins[i][j-1];
    //                 pre2 = health[i][j-1];
    //             }
    //             if (min1 > min2) {
    //                 health[i][j] = health[i-1][j] + dungeon[i][j];
    //                 mins[i][j] = mins[i-1][j];
    //             } else {
    //                 health[i][j] = health[i][j-1] + dungeon[i][j];
    //                 mins[i][j] = mins[i][j-1];
    //             }
    //             if (health[i][j] < mins[i][j]) {
    //                 mins[i][j] = health[i][j];
    //             }
    //         }
    //     }
    //     for (int i{0}; i < m; ++i) {
    //         for (int j{0}; j < n; ++j) {
    //             cout << mins[i][j] << ", ";
    //         }
    //         cout  << endl;
    //     }
    //     int res = 1;
    //     if (mins[m-1][n-1] < 0) {
    //         res = 1 - mins[m-1][n-1];
    //     }
    //     return res;
    // }
};


int main() {
    // vector<vector<int>> in{{100}};
    vector<vector<int>> in{
        {-2,-3,3},
        {-5,-10,1},
        {10,30,-5}};
    // vector<vector<int>> in{
    //         {1,-3,3},
    //         {0,-2,0},
    //         {-3,-3,-3}
    //     };
    Solution sol;
    int res = sol.calculateMinimumHP(in);
    cout << res << endl;
    return 0;
}
