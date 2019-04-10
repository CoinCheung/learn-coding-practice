#include<vector>

using namespace std;
 
class Solution {
 public:
    int findMin(vector<int>& nums) {
        int size = nums.size();
        int res = nums[0];
        for (int i{0}; i < size-1; ++i) {
            if (nums[i] > nums[i+1]) {
                res = nums[i+1];
            }
        }
        return res;
    }
};
