#include<string>
#include<vector>
#include<set>
#include<queue>
#include<iostream>

using std::string;
using std::vector;
using std::set;
using std::queue;
using std::cout;
using std::endl;


class Solution {
 public:
    vector<string> removeInvalidParentheses(string s) {
        queue<string> q;
        set<string> ss;
        vector<string> res;

        q.push(s);
        ss.insert(s);
        while (!q.empty()) {
            string tmp = q.front();
            q.pop();
            int count = 0;
            for (int i{0}; i < tmp.size(); ++i) {
                if (tmp[i] == '(') {
                    ++count;
                } else if (tmp[i] == ')') {
                    --count;
                }
                if (count < 0) {
                    break;
                }
            }
            if (count < 0) {
                int cnt = 0;
                int j = 0;
                for (; j < tmp.size(); ++j) {
                    if (tmp[j] == '(') {
                        ++cnt;
                    } else if (tmp[j] == ')') {
                        --cnt;
                        string t = tmp.substr(0, j) + tmp.substr(j+1);
                        if (ss.count(t) == 0) {
                            ss.insert(t);
                            q.push(t);
                        }
                    }
                    if (cnt < 0) {
                        break;
                    }
                }
            } else if (count > 0) {
                int cnt = 0;
                int j = tmp.size()-1;
                for (; j >= 0; --j) {
                    if (tmp[j] == ')') {
                        ++cnt;
                    } else if (tmp[j] == '(') {
                        --cnt;
                        string t = tmp.substr(0, j) + tmp.substr(j+1);
                        if (ss.count(t) == 0) {
                            ss.insert(t);
                            q.push(t);
                        }
                    }
                    if (cnt < 0) {
                        break;
                    }
                }
                for (int m{j}; m < tmp.size()-1; ++m) {
                    if (tmp[m] == '(') {
                        string t = tmp.substr(0, m) + tmp.substr(m+1);
                        if (ss.count(t) == 0) {
                            q.push(t);
                            ss.insert(t);
                        }
                    }
                }
            } else {
                res.push_back(tmp);
                continue;
            }
        }
        return res;
    }
};


int main() {
    Solution sol;
    // string in{"()())()"};
    // string in{"(a)())()"};
    string in{")("};
    vector<string> res = sol.removeInvalidParentheses(in);
    for (auto &el : res) {
        cout << el << endl;
    }
    return 0;
}
