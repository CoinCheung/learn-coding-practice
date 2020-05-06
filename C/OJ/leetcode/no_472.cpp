#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
#include<set>
#include<numeric>

using namespace std;


// seems that unordered set is much faster than set
// hash map is faster than rb-tree
class Solution {
 public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> res;
        unordered_set<string> ss(words.begin(), words.end());
        // res.reserve(words.size());
        // std::sort(words.begin(), words.end(), [&](string s1, string s2){
        //         return s1.size() < s2.size();
        //         });

        for (auto &el : words) {
            int len = el.size();
            if (len == 0) {
                continue;
            }
            // ss.insert(el);
            vector<int> dp(len+1, 0);
            dp[0] = 1;
            for (int i{1}; i <= len; ++i) {
                for (int j{0}; j < i; ++j) {
                    if (i-j < len && dp[j] && ss.find(el.substr(j, i-j)) != ss.end()) {
                        dp[i] = 1;
                        break;
                    }
                }
            }
            if (dp[len] == 1) {
                res.push_back(el);
            }
        }
        return res;
    }
};


// too slow and too large: 5% faster and 5% less memory
// class Solution {
//  public:
//     vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
//         vector<string> res;
//         set<string> ss;
//         res.reserve(words.size());
//         std::sort(words.begin(), words.end(), [&](string s1, string s2){
//                 return s1.size() < s2.size();
//                 });
//
//         int last_len = 0;
//         for (auto &el : words) {
//             int len = el.size();
//             if (len == 0) {
//                 continue;
//             }
//             ss.insert(el);
//             vector<int> dp(len+1, 0);
//             dp[0] = 1;
//             for (int i{0}; i < len; ++i) {
//                 if (dp[i] == 0) {
//                     continue;
//                 }
//                 for (int j{i+1}; j <= len; ++j) {
//                     if (j-i < len && ss.find(el.substr(i, j-i)) != ss.end()) {
//                         dp[j] = 1;
//                     }
//                     if (j-i > last_len) {
//                         break;
//                     }
//                 }
//                 if (dp[len] == 1) {
//                     res.push_back(el);
//                     break;
//                 }
//                 last_len = len;
//             }
//         }
//         return res;
//     }
// };

// time limit
// class Solution {
//  public:
//     vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
//         vector<string> res;
//         unordered_set<string> ss(words.begin(), words.end());
//         res.reserve(words.size());
//
//         for (auto &el : words) {
//             int len = el.size();
//             if (len == 0) {
//                 continue;
//             }
//             vector<int> dp(len+1, 0);
//             dp[0] = 1;
//             for (int i{0}; i < len; ++i) {
//                 if (dp[i] == 0) {
//                     continue;
//                 }
//                 for (int j{i+1}; j <= len; ++j) {
//                     string sub = el.substr(i, j-i);
//                     if (j-i < len && ss.count(sub) != 0) {
//                         dp[j] = 1;
//                     }
//                 }
//             }
//             if (dp[len] == 1) {
//                 res.push_back(el);
//             }
//         }
//         return res;
//     }
// };


int main() {
    Solution sol;
    vector<string> in{"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
    // vector<string> in{"a","b","ab","abc"};
    // vector<string> in{"",};
    auto res = sol.findAllConcatenatedWordsInADict(in);
    for (auto &el : res) {
        cout << el << endl;
    }
    return 0;
}
