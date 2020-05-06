#include<iostream>
#include<limits>

using std::cout;
using std::endl;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
 public:
    bool isValidBST(TreeNode* root) {
        if (root == NULL) {
            return true;
        }
        vector<int> v;
        bool valid = true;
        traverse(root, v);
        for (int i{0}; i < v.size()-1; ++i) {
            if (v[i] >= v[i+1]) {
                valid = false;
                break;
            }
        }
        return valid;
    }

    void traverse(TreeNode* root, vector<int> &in) {
        if (root == NULL) {
            return;
        }
        traverse(root->left, in);
        in.push_back(root->val);
        traverse(root->right, in);
    }
};


// not passed
// class Solution {
//  public:
//     bool isValidBST(TreeNode* root) {
//         int max = std::numeric_limits<int>::max();
//         int min = std::numeric_limits<int>::min();
//         bool valid = check(root, min, max);
//         return valid;
//     }
//
//     bool check(TreeNode *root, int min, int max) {
//         if (root == NULL) {
//             return true;
//         }
//         if (root->val <= min && root->val != std::numeric_limits<int>::min()) {
//             return false;
//         }
//         if (root->val >= max && root->val != std::numeric_limits<int>::max()) {
//             return false;
//         }
//         bool valid = true;
//         valid = check(root->left, min, root->val) && check(root->right, root->val, max);
//         return valid;
//     }
// };




int main() {
    Solution sol;
    return 0;
}
