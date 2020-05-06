#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using std::vector;
using std::cout;
using std::endl;
using std::multiset;


class Solution {
 public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int len = nums.size();
        int count = 0;
        multiset<int64_t> ss;
        vector<int64_t> sums(len + 1, 0);
        ss.insert(0);
        for (int i=0; i < len; ++i) {
            sums[i+1] = sums[i] + nums[i];
            auto lo = ss.lower_bound(sums[i+1] - upper);
            auto up = ss.upper_bound(sums[i+1] - lower);
            count += std::distance(lo, up);
            ss.insert(sums[i+1]);
        }

        return count;
    }


    // still time limit
    // int countRangeSum(vector<int>& nums, int lower, int upper) {
    //     int len = nums.size();
    //     int count = 0;
    //     vector<int64_t> tmp;
    //     vector<int64_t> sums(len+1, 0);
    //     tmp.reserve(len+1);
    //     tmp.push_back(0);
    //     for (int i{0}; i < len; ++i) {
    //         sums[i+1] = sums[i] + nums[i];
    //         int b1 = 0, b2 = 0;
    //         for (int j=0; j < tmp.size(); ++j) {
    //             int64_t sum = sums[i+1] - tmp[j];
    //             if (sum <= upper) {
    //                 if (sum < lower) {
    //                     break;
    //                 }
    //                 b1 = j;
    //                 break;
    //             }
    //         }
    //         for (int j=tmp.size()-1; j >= 0; --j) {
    //             int64_t sum = sums[i+1] - tmp[j];
    //             if (sum >= lower) {
    //                 if (sum > upper) {
    //                     break;
    //                 }
    //                 b2 = j + 1;
    //                 break;
    //             }
    //         }
    //         int left = 0, right = tmp.size();
    //         while (left < right) {
    //             int mid = left + (right - left) / 2;
    //             if (tmp[mid] > sums[i+1]) {
    //                 right = mid;
    //             } else {
    //                 left = mid + 1;
    //             }
    //         }
    //         tmp.insert(tmp.begin() + left, sums[i+1]);
    //
    //         // tmp.push_back(sums[i+1]);
    //         // std::sort(tmp.begin(), tmp.end());
    //
    //         count += b2 - b1;
    //     }
    //     return count;
    // }

    // time limit
    // int countRangeSum(vector<int>& nums, int lower, int upper) {
    //     int len = nums.size();
    //     vector<vector<int64_t>> mat(len, vector<int64_t>(len, 0));
    //     int count = 0;
    //     for (int i{0}; i < len; ++i) {
    //         for (int j{i}; j < len; ++j) {
    //             if (i == j) {
    //                 mat[i][j] = nums[i];
    //             } else if (i != 0 && j == i+1) {
    //                 mat[i][j] = mat[0][j] - mat[0][i-1];
    //             } else {
    //                 mat[i][j] = mat[i][j-1] + nums[j];
    //             }
    //             if (mat[i][j] >= lower && mat[i][j] <= upper) {
    //                 ++count;
    //             }
    //         }
    //     }
    //     return count;
    // }
};

int main() {
    Solution sol;
    // vector<int> in{-2, 5, -1};
    vector<int> in{2147483647, -2147483648, -1, 0};
    int count = sol.countRangeSum(in, -1, 0);
    cout << count << endl;
    return 0;
}
