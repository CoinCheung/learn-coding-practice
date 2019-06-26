#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>

using std::vector;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;


// class Solution {
//  public:
//     vector<int> findSubstring(string s, vector<string>& words) {
//         int n_words = words.size();
//         int slen = s.size();
//         int n_chars{0};
//         vector<int> used(n_words, 0);
//         map<char, vector<int>> m;
//         for (int i{0}; i < n_words; ++i) {
//             n_chars += words[i].size();
//             char c = words[i][0];
//             if (m.count(c) == 0) {
//                 m[c] = vector<int>();
//             }
//             m[c].push_back(i);
//         }
//         if (slen == 0 || n_chars == 0) {
//             return vector<int>();
//         }
//
//         vector<int> res;
//         for (int i{0}; i <= slen-n_chars; ++i) {
//             for (auto &el : used) {
//                 el = 0;
//             }
//             int idx = find_subs(s, i, m, words, used);
//
//             if (idx != -1) {
//                 res.push_back(i);
//             }
//         }
//         return res;
//     }
//
//     int find_subs(
//             string& s,
//             int st,
//             map<char, vector<int>>& m,
//             vector<string>& words,
//             vector<int>& used
//         ) {
//         int all_used = 1;
//         for (auto &el : used) {
//             if (el == 0) {
//                 all_used = 0;
//                 break;
//             }
//         }
//         if (all_used == 1) {
//             return 1;
//         }
//         int res = -1;
//         char c = s[st];
//         auto ids = m[c];
//         for (auto &el : ids) {
//             if (used[el] == 1) {
//                 continue;
//             }
//             auto str = words[el];
//             int len = str.size();
//             // cout << s.substr(st, len) << endl;
//             if (s.substr(st, len) != str) {
//                 continue;
//             }
//             used[el] = 1;
//             st += len;
//             res = find_subs(s, st, m, words, used);
//             if (res != -1) {
//                 return res;
//             }
//             used[el] = 0;
//             st -= len;
//         }
//
//         return res;
//     }
// };


class Solution {
 public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int slen = s.size();
        int n_words = words.size();
        if (slen == 0 || n_words == 0) {
            return vector<int>();
        }
        int wsize = words[0].size();
        int wlen = wsize * n_words;
        if (slen < wlen) {
            return vector<int>();
        }

        unordered_map<string, int> counts;
        unordered_map<string, int> tmp;
        for (auto &el : words) {
            if (counts.count(el) == 0) {
                counts[el] = 0;
                tmp[el] = 0;
            }
            counts[el] += 1;
        }

        vector<int> res;
        for (int i{0}; i <= slen - wlen; ++i) {
            for (auto &el : tmp) {
                el.second = 0;
            }
            int flag = 0;
            for (int j{0}; j < n_words; ++j) {
                string sub = s.substr(i+j*wsize, wsize);
                if (counts.count(sub) == 0 || tmp[sub] > counts[sub]) {
                    flag = 1;
                    break;
                }
                tmp[sub] += 1;
            }
            if (flag == 1) {
                continue;
            }
            flag = 0;
            for (auto &el : tmp) {
                if (el.second != counts[el.first]) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                res.push_back(i);
            }
        }
        return res;
    }
};

int main() {
    string s("");
    vector<string> words;//{"foo", "bar"};
    Solution sol;
    auto res = sol.findSubstring(s, words);
    for (auto &el : res) {
        cout << el << endl;
    }
    return 0;
}
