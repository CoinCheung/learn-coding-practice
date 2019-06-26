#include<iostream>
#include<limits>
#include<vector>

using std::vector;
using std::cout;
using std::endl;

int matrix_chain(vector<int>& vi);

int main() {
    vector<int> vi{30, 35, 155, 10, 20, 25};
    int res = matrix_chain(vi);
    cout << res << endl;
    return 0;
}

/* 虽然解释是从上到下的，找最优点，把当前分割点和最优子结构加起来。但是这种实现其实是从下到上的，先两个两个计算出来，再三个三个的找最优，也就是说在两个的基础上，找三个的最佳分割。一直这样下去，得到整体的最佳分。 */

int matrix_chain(vector<int>& vi) {
    int n_mat = vi.size()-1;
    vector<vector<int>> m(n_mat, vector<int>(n_mat, 0));
    for (int i{0}; i < n_mat; ++i) {
        m[i][i] = 0;
    }
    int min = std::numeric_limits<int>::max();
    for (int l{2}; l <= n_mat; ++l) {
        for (int i{0}; i <= n_mat - l; ++i) {
            int j = i + l - 1;
            m[i][j] = vi[i] * vi[i+1] * vi[j+1] + m[i+1][j];
            for (int k{i+1}; k < j; ++k) {
                int cost = m[i][k] + m[k+1][j] + vi[i]*vi[k+1]*vi[j+1];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }
    return m[0][n_mat-1];
}
