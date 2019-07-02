#include<vector>
#include<limits>

#include<iostream>

using namespace std;

using std::vector;


class Solution {
 public:
    int largestRectangleArea(vector<int>& heights) {
        int n_hists = heights.size();
        int max = 0;
        for (int i{0}; i < n_hists; ++i) {
            int area = heights[i];
            if ((i == n_hists-1) || heights[i] > heights[i+1]) {
                int min = heights[i];
                for (int j{i-1}; j >= 0 ; --j) {
                    if (heights[j] < min) {
                        min = heights[j];
                    }
                    int tmp = (i - j + 1) * min;
                    if (tmp > area) {
                        area = tmp;
                    }
                }
            }
            if (area > max) {
                max = area;
            }
        }
        return max;
    }

    // faster than 5%
    // int largestRectangleArea(vector<int>& heights) {
    //     int n_hists = heights.size();
    //     int max = 0;
    //     for (int i{0}; i < n_hists; ++i) {
    //         if ((i == n_hists-1) || (heights[i] > heights[i+1])) {
    //             int tmp = getPartialRectangeleArea(heights, i);
    //             if (tmp > max) {
    //                 max = tmp;
    //             }
    //         }
    //     }
    //
    //     return max;
    // }
    //
    // int getPartialRectangeleArea(vector<int>& heights, int pos) {
    //     int max = 0;
    //     for (int i{0}; i <= pos; ++i) {
    //         int min = std::numeric_limits<int>().max();
    //         for (int j{i}; j <= pos; ++j) {
    //             if (heights[j] < min) {
    //                 min = heights[j];
    //             }
    //         }
    //         int area = min * (pos + 1 - i);
    //         if (max < area) {
    //             max = area;
    //         }
    //     }
    //     return max;
    // }

    // time limit
    // int largestRectangleArea(vector<int>& heights) {
    //     int n_hists = heights.size();
    //     int max = 0;
    //     for (int i{0}; i < n_hists; ++i) {
    //         for (int j{i}; j < n_hists; ++j) {
    //             int area{0};
    //             int min = std::numeric_limits<int>::max();
    //             for (int m{i}; m <= j; ++m) {
    //                 if (min > heights[m]) {
    //                     min = heights[m];
    //                 }
    //             }
    //             area = (j - i + 1) * min;
    //             if (area > max) {
    //                 max = area;
    //             }
    //         }
    //     }
    //     return max;
    // }
};

int main() {
    Solution sol;
    vector<int> heights{2,1,5,6,2,3};
    auto max = sol.largestRectangleArea(heights);
    cout << max << endl;
    return 0;
}

