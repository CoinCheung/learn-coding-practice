#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<set>

using namespace std;


class Solution {
 public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int len = s.size();
        vector<bool> st(len + 1, false);
        set<string> dict(wordDict.begin(), wordDict.end());
        st[0] = true;
        int max_len = 0;
        for (auto& el : wordDict) {
            dict.insert(el);
            if (el.size() > max_len) {
                max_len = el.size();
            }
        }

        for (int i=0; i < len; ++i) {
            if (!st[i]) {
                continue;
            }
            for (int j=i+1; j < len+1; ++j) {
                if (dict.count(s.substr(i, j-i)) > 0) {
                    st[j] = true;
                }
                if (st[len]) {
                    return true;
                }
                if (j-i > max_len) {
                    break;
                }
            }
        }
        return false;
    }
};


int main() {
    Solution sol;
    // string s("leetcode");
    // vector<string> dict{"leet", "code"};
    // string s("applepenapple");
    // vector<string> dict{"apple", "pen"};
    string s("catsandog");
    vector<string> dict{"cats", "dog", "sand", "and", "cat"};

    if (sol.wordBreak(s, dict)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    return 0;
}
