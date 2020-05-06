#include<vector>
#include<queue>
#include<iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public: 
    vector<int> rightSideView(TreeNode* root) {
        int height = get_height(root);
        vector<int> res;
        if (height == 0) return res;
        res.reserve(height);
        queue<TreeNode*> q;
        res.push_back(root->val);
        if (root->left != NULL)
            q.push(root->left);
        if (root->right != NULL)
            q.push(root->right);
        q.push(NULL);
        if (q.size() == 1) return res;

        int val;
        while (not q.size() == 0) {
            TreeNode* ptr = q.front();
            q.pop();
            if (ptr == NULL) {
                res.push_back(val);
                if (q.size() == 0) break;
                q.push(NULL);
            } else {
                val = ptr->val;
                if (ptr->left != NULL) {
                    q.push(ptr->left);
                }
                if (ptr->right != NULL) {
                    q.push(ptr->right);
                }
            }
        }
        return res;
    }

    // vector<int> add_right(vector<int>& res)

    int get_height(TreeNode* root) {
        if (root == NULL) return 0;
        int h_left = 0, h_right = 0;
        if (root->left != NULL)
            h_left = get_height(root->left);
        if (root->right != NULL)
            h_right = get_height(root->right);
        return std::max(h_left, h_right) + 1;
    }
};


int main() {
    Solution sol;
    // TreeNode *root = new TreeNode(0);
    // sol.get_height(root);
    TreeNode* root = NULL;
    vector<int> res = sol.rightSideView(root);
    return 0;
}
