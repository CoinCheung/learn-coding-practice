#include<vector>
#include<iostream>
#include<algorithm>

using std::vector;
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
    TreeNode* p1;
    TreeNode* p2;
    TreeNode* pre;

    void recoverTree(TreeNode* root) {
        if (root == NULL) {
            return;
        }
        p1 = p2 = pre = NULL;
        find(root);
        if (p1 == NULL || p2 == NULL) {
            return;
        }
        std::swap(p1->val, p2->val);
    }

    void find(TreeNode* root) {
        if (root == NULL) {
            return;
        }
        find(root->left);
        if (pre == NULL) {
            pre = root;
        } else {
            if (pre->val > root->val) {
                if (p1 == NULL) {
                    p1 = pre;
                    p2 = root;
                } else {
                    p2 = root;
                }
            }
        }
        pre = root;
        find(root->right);
    }
};


// 83% / 42%
// class Solution {
//  public:
//     void recoverTree(TreeNode* root) {
//         if (root == NULL) {
//             return;
//         }
//         vector<int> vi;
//         traverse(root, vi);
//         std::sort(vi.begin(), vi.end());
//         int pos = 0;
//         recover(root, vi, pos);
//     }
//
//     void traverse(TreeNode* root, vector<int>& vi) {
//         if (root == NULL) {
//             return;
//         }
//         traverse(root->left, vi);
//         vi.push_back(root->val);
//         traverse(root->right, vi);
//     }
//
//     void recover(TreeNode* root, vector<int>& vi, int &pos) {
//         if (root == NULL) {
//             return;
//         }
//         recover(root->left, vi, pos);
//         root->val = vi[pos];
//         ++pos;
//         recover(root->right, vi, pos);
//     }
// };


int main() {
    Solution sol;

    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(3);
    // root->left->right = new TreeNode(2);

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(2);

    sol.recoverTree(root);
    return 0;
}
