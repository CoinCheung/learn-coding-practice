#include<vector>
#include<algorithm>
#include<limits>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


using std::vector;

class Solution {
 public:
    int max_val{std::numeric_limits<int>::min()};

    int maxPathSum(TreeNode* root) {
        if (root == NULL) return 0;
        getMaxValue(root);
        return max_val;
    }

    int getMaxValue(TreeNode* root) {
        if (root == NULL) return 0;
        int curr_val = root->val;
        int left_val = getMaxValue(root->left);
        int right_val = getMaxValue(root->right);
        left_val = std::max(0, left_val);
        right_val = std::max(0, right_val);
        int res = left_val + right_val + curr_val;
        if (res > max_val) {
            max_val = res;
        }
        return std::max(curr_val, curr_val+std::max(left_val, right_val));
    }

    int get_n_nodes(TreeNode* r) {
        int n_nodes{0};
        if (r != NULL) {
            n_nodes += 1;
            n_nodes += get_n_nodes(r->left);
            n_nodes += get_n_nodes(r->right);
        }
        return n_nodes;
    }
};

int main() {
    Solution sol;
    return 0;
}
