#include<string>
#include<iostream>
#include<vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;


class Solution {
 public:
    int minDistance(string word1, string word2) {
        int m = word1.size()+1, n = word2.size()+1;
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i{0}; i < m; ++i) {
            dp[i][0] = i;
        }
        for (int j{0}; j < n; ++j) {
            dp[0][j] = j;
        }

        for (int i{1}; i < m; ++i) {
            for (int j{1}; j < n; ++j) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    int min = dp[i-1][j];
                    if (min > dp[i][j-1]) {
                        min = dp[i][j-1];
                    }
                    if (min > dp[i-1][j-1]) {
                        min = dp[i-1][j-1];
                    }
                    dp[i][j] = min + 1;
                }
            }
        }
        return dp[m-1][n-1];
    }
};


int main() {
    Solution sol;
    // string s1("sea"), s2("eat");
    // string s1(""), s2("");
    // string s1("horse"), s2("ros");
    // string s1("intention"), s2("execution");
    string s1("a"), s2("ab");
    cout << sol.minDistance(s1, s2) << endl;

    return 0;
}
