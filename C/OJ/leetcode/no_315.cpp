#include<iostream>
#include<algorithm>
#include<vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
 public:
    vector<int> countSmaller(vector<int>& nums) {
        int len = nums.size();
        vector<int> counts(len, 0);
        if (len == 0) {
            return counts;
        }
        vector<int> tmp;
        tmp.reserve(len);
        tmp.push_back(nums[len-1]);
        for (int i{len-2}; i >= 0; --i) {
            int n = nums[i];
            int left = 0, right = tmp.size();
            int mid;
            while (right > left) {
                mid = left + (right - left) / 2;
                if (tmp[mid] >= n) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            counts[i] = left;
            tmp.insert(tmp.begin() + left, nums[i]);
            // tmp.push_back(nums[i]);
            // std::sort(tmp.begin(), tmp.end());
        }
        return counts;
    }

    // still time limit
    // vector<int> countSmaller(vector<int>& nums) {
    //     int len = nums.size();
    //     vector<int> counts(len, 0);
    //     if (len == 0) {
    //         return counts;
    //     }
    //     int max = nums[len-1];
    //     for (int i{len-2}; i >= 0; --i) {
    //         if (nums[i] > max) {
    //             max = nums[i];
    //             counts[i] = len - 1 - i;
    //         } else {
    //             for (int j{i+1}; j < len; ++j) {
    //                 if (nums[j] < nums[i]) {
    //                     ++counts[i];
    //                 }
    //             }
    //         }
    //     }
    //     return counts;
    // }

    // time limit
    // vector<int> countSmaller(vector<int>& nums) {
    //     int len = nums.size();
    //     vector<int> counts(len, 0);
    //     for (int i{len-2}; i >= 0; --i) {
    //             for (int j{i+1}; j < len; ++j) {
    //                 if (nums[j] < nums[i]) {
    //                     ++counts[i];
    //                 }
    //         }
    //     }
    //     return counts;
    // }
};


int main() {
    vector<int> nums{-1, -1};
    // vector<int> nums{5, 2, 6, 1};
    // vector<int> nums{0, 1, 2};
    // vector<int> nums{0, 2, 1};
    Solution sol;
    vector<int> counts = sol.countSmaller(nums);
    for (auto &el : counts) {
        cout << el << ", ";
    }
    cout << endl;
    return 0;
}
