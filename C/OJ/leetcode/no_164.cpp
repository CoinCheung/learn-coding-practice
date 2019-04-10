#include<vector>
#include<algorithm>
#include<iostream>
#include<climits>

using namespace std;

class Solution {
 public:
    int maximumGap(vector<int>& nums) {
        int size = nums.size();
        if (size < 2) return 0;
        std::sort(nums.begin(), nums.end());
        int maxgap = 0;
        int gap = 0;
        for (int i{0}; i < size-1; ++i) {
            gap = nums[i+1] - nums[i];
            if (gap > maxgap) {
                maxgap = gap;
            }
        }
        return maxgap;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {3,4,12,9,6,7,5,4,6,8,3, 2};
    cout << sol.maximumGap(nums) << endl;
    cout << INT_MIN << endl;
    cout << INT_MAX << endl;
}
