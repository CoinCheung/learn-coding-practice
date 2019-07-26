#include<vector>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
 public:
    vector<vector<int>> connect;
    int count;
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
    }
};


/* class Solution {
 *  public:
 *     vector<vector<int>> connect;
 *     int count;
 *     vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
 *
 *         // count tree node number
 *         count = 0;
 *         vectro<TreeNode*> stack;
 *         stack.push_back(root);
 *         int size = 1;
 *         TreeNode* curr;
 *         while (true) {
 *             if (size == 0) {
 *                 break;
 *             }
 *             --size;
 *             curr = stack[size];
 *             stack.resize(size);
 *             ++count;
 *             if (curr->left != NULL) {
 *                 stack.push_back(curr->left);
 *                 ++size;
 *             }
 *             if (curr->right != NULL) {
 *                 stack.push_back(curr->right);
 *                 ++size;
 *             }
 *         }
 *
 *         // generate neighboring matrix
 *         connect = vector<vector<int>>(n_nodes, vector<int>(n_nodes, 0));
 *         stack.push_back(root);
 *         size = 1;
 *         while (true) {
 *             if (size == 0) {
 *                 break;
 *             }
 *             --size;
 *             curr = stack[size];
 *             stack.resize(size);
 *
 *             if (curr->let != NULL) {
 *                 int i = curr->val;
 *                 int j = curr->left->val;
 *                 connect[i][j] = 1;
 *                 connect[j][i] = 1;
 *             }
 *             if (curr->right != NULL) {
 *                 int i = curr->val;
 *                 int j = curr->right;
 *                 connect[i][j] = 1;
 *                 connect[j][i] = 1;
 *             }
 *         }
 *     }
 * }; */
