#include<vector>
#include<iostream>

using std::vector;
using std::cout;
using std::endl;


class Solution {
 public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(), n{0};
        if (m <= 0) {
            return 0;
        }
        n = matrix[0].size();

        vector<vector<int>> height(m, vector<int>(n, 0));
        for (int i{0}; i < m; ++i) {
            for (int j{0}; j < n; ++j) {
                if (i == 0) {
                    if (matrix[i][j] == '1') {
                        height[i][j] = 1;
                    }
                } else {
                    if (matrix[i][j] == '1') {
                        height[i][j] = height[i-1][j] + 1;
                    }
                }
            }
        }
        int max{0};
        for (int i{0}; i < m; ++i) {
            for (int j{0}; j < n; ++j) {
                if ((j == n-1) || (height[i][j] > height[i][j+1])) {
                    int min = height[i][j];
                    int area = height[i][j];
                    if (area > max) {
                        max = area;
                    }
                    for (int k{j-1}; k >= 0; --k) {
                        if (height[i][k] < min) {
                            min = height[i][k];
                        }
                        area = min * (j + 1 -k);
                        if (max < area) {
                            max = area;
                        }
                    }
                }
            }
        }
        return max;
    }
};


int main() {
    Solution sol;
    vector<vector<char>> mat{{'1'}};
    int res = sol.maximalRectangle(mat);
    cout << res << endl;
    return 0;
}
