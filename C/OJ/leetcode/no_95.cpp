#include<vector>

using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
 public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> ret;
        if (n == 0) {
            return ret;
        }
        ret = generate(1, n);
        return ret;
    }

    vector<TreeNode*> generate(int st, int ed) {
        if (st > ed) {
            return vector<TreeNode*>(1, NULL);
        }
        if (st == ed) {
            return vector<TreeNode*>(1, new TreeNode(st));
        }
        vector<TreeNode*> res;
        for (int i{st}; i <= ed; ++i) {
            vector<TreeNode*> left = generate(st, i-1);
            vector<TreeNode*> right = generate(i+1, ed);
            for (int m{0}; m < left.size(); ++m) {
                for (int n{0}; n < right.size(); ++n) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left[m];
                    root->right = right[n];
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};

#include<iostream>

using namespace std;

int main() {
    Solution sol;
    auto ret = sol.generateTrees(0);
    cout << ret.size() << endl;

    return 0;
}
