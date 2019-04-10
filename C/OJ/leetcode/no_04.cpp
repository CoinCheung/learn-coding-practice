#include<iostream>
#include<vector>
using namespace std;


class Solution {
 public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int k = (m + n) >> 1;
        int64_t max_val = 10000000000;

        int pos1{0}, pos2{0};
        int64_t val1, val2;
        int64_t last, curr;
        val1 = max_val;
        if (pos1 < m) {
            val1 = nums1[pos1];
        }
        val2 = max_val;
        if (pos2 < n) {
            val2 = nums2[pos2];
        }
        if (val1 < val2) {
            curr = val1;
        } else {
            curr = val2;
        }
        for (int i{0}; i < k; ++i) {
            val1 = max_val;
            if (pos1 < m) {
                val1 = nums1[pos1];
            }
            val2 = max_val;
            if (pos2 < n) {
                val2 = nums2[pos2];
            }
            if (val1 < val2) {
                ++pos1;
                val1 = max_val;
                if (pos1 < m) {
                    val1 = nums1[pos1];
                }
            } else {
                ++pos2;
                val2 = max_val;
                if (pos2 < n) {
                    val2 = nums2[pos2];
                }
            }
            last = curr;
            if (val1 < val2) {
                curr = val1;
            } else {
                curr = val2;
            }
        }
        bool even = (m+n)%2 == 0;
        double res;
        if (even) {
            res = (curr+last)/2.0;
        } else {
            res = static_cast<double>(curr);
        }
        return res;
    }
};


int main() {
    Solution sol;
    vector<int> num1, num2;
    num1.push_back(1001);
    num2.push_back(1000);

    auto res = sol.findMedianSortedArrays(num1, num2);
    cout << res << endl;

    return 0;
}
