#include<vector>
#include<iostream>
#include<string>

using namespace std;

class Solution {
 public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int len = n;
        int i0 = 0, j0 = 0;
        int tmp;
        while (len > 0) {
            for (int j{j0}; j < j0+len-1; ++j) {
                tmp = matrix[i0][j];
                matrix[i0][j] = matrix[n-1-j][i0];
                matrix[n-1-j][i0] = matrix[n-1-i0][n-1-j];
                matrix[n-1-i0][n-1-j] = matrix[j][n-1-i0];
                matrix[j][n-1-i0] = tmp;
            }
            ++i0; ++j0;
            len -= 2;
        }
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix;
    int n = 4;
    matrix.resize(n);
    for (int i{0}; i < n; ++i) {
        matrix[i].resize(n);
    }
    matrix[0] = {5, 1, 9, 11};
    matrix[1] = {2, 4, 8, 10};
    matrix[2] = {13, 3, 6, 7};
    matrix[3] = {15, 14, 12, 16};

    for (int i{0}; i < n; ++i) {
        for (int j{0}; j < n; ++j)
            cout << matrix[i][j] << ", ";
        cout << endl;
    }
    cout << string("===+++++======") << endl;
    sol.rotate(matrix);
    for (int i{0}; i < n; ++i) {
        for (int j{0}; j < n; ++j)
            cout << matrix[i][j] << ", ";
        cout << endl;
    }
    return 0;
}
