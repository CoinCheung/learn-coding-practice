#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

using namespace std;


class Solution {
 public:
    unordered_map<string, vector<string>> dict;

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string> res;
        if (s.size() == 0) {
            return res;
        }
        if (dict.count(s) != 0) {
            return dict[s];
        }
        int len = wordDict.size();
        for (int i{0}; i < len; ++i) {
            int sz = wordDict[i].size();
            if (sz > s.size()) {
                continue;
            }
            string sub = s.substr(0, sz);
            if (sub == wordDict[i]) {
                string rem = s.substr(sz);
                if (rem == "") {
                    res.push_back(wordDict[i]);
                } else {
                    vector<string> part = wordBreak(rem, wordDict);
                    if (dict.count(rem) == 0) {
                        dict[rem] = part;
                    }
                    for (auto &item : part) {
                        res.push_back(wordDict[i] + " " + item);
                    }
                }
            }
        }
        return res;
    }
};


int main() {
    Solution sol;
    // string sin("catsanddog");
    // vector<string> wordDict{"cat", "cats", "and", "sand", "dog"};
    string sin("pineapplepenapple");
    vector<string> wordDict{"apple", "pen", "applepen", "pine", "pineapple"};

    vector<string> res = sol.wordBreak(sin, wordDict);
    for (auto &el : res) {
        cout << el << endl;
    }
    return 0;
}
