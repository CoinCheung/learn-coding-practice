#include<iostream>
#include<algorithm>
#include<limits>
#include<vector>


using namespace std;


// very slow: 5%
class Solution {
 public:
    vector<vector<int>> dists;
    vector<vector<int>> visited;

    int swimInWater(vector<vector<int>>& grid) {
        int m = grid.size();
        int n;
        if (m > 0) {
            n = grid[0].size();
        }
        int int_max = numeric_limits<int>::max();
        dists = vector<vector<int>>(m, vector<int>(n, int_max));
        visited = vector<vector<int>>(m, vector<int>(n, 0));
        dists[0][0] = grid[0][0];

        dfs(grid, 0, 0);

        return dists[m-1][n-1];
    }

    void dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size(), n;
        if (m > 0) {
            n = grid[0].size();
        }
        vector<vector<int>> dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        vector<int> xs(m*n);
        vector<int> ys(m*n);
        int len=0;
        xs[len] = i;
        ys[len] = j;
        ++len;
        while (len > 0) {
            --len;
            i = xs[len];
            j = ys[len];
            for (auto &dir : dirs) {
                int i_next = i + dir[0], j_next = j + dir[1];
                if (i_next < 0 || i_next > m-1 || j_next < 0 || j_next > n-1) {
                    continue;
                }
                int max = std::max(dists[i][j], grid[i_next][j_next]);
                if (max < dists[i_next][j_next]) {
                    dists[i_next][j_next] = max;
                    xs[len] = i_next;
                    ys[len] = j_next;
                    ++len;
                }
            }
        }
    }
};


// time limit
// class Solution {
//  public:
//     vector<vector<int>> dists;
//     vector<vector<int>> visited;
//
//     int swimInWater(vector<vector<int>>& grid) {
//         int m = grid.size();
//         int n;
//         if (m > 0) {
//             n = grid[0].size();
//         }
//         int int_max = numeric_limits<int>::max();
//         dists = vector<vector<int>>(m, vector<int>(n, int_max));
//         visited = vector<vector<int>>(m, vector<int>(n, 0));
//         dists[0][0] = grid[0][0];
//
//         dfs(grid, 0, 0);
//
//         return dists[m-1][n-1];
//     }
//
//     void dfs(vector<vector<int>>& grid, int i, int j) {
//         int m = grid.size(), n;
//         if (m > 0) {
//             n = grid[0].size();
//         }
//         vector<vector<int>> dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
//         for (auto &dir : dirs) {
//             int i_next = i + dir[0], j_next = j + dir[1];
//             if (i_next < 0 || i_next > m-1 || j_next < 0 || j_next > n-1) {
//                 continue;
//             }
//             int max = std::max(dists[i][j], grid[i_next][j_next]);
//             if (max >= dists[i_next][j_next]) {
//                 continue;
//             } else {
//                 dists[i_next][j_next] = max;
//                 dfs(grid, i_next, j_next);
//             }
//         }
//     }
// };


int main() {
    Solution sol;
    // vector<vector<int>> in{{0, 2}, {1, 3}};
    // vector<vector<int>> in{{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}};
    vector<vector<int>> in{{10,12,4,6},{9,11,3,5},{1,7,13,8},{2,0,15,14}};

    int res = sol.swimInWater(in);
    cout << endl << res << endl;
    return 0;
}
