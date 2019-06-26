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
            for (int j{i}; j < n_hists; ++j) {
                int area{0};
                int min = std::numeric_limits<int>::max();
                for (int m{i}; m <= j; ++m) {
                    if (min > heights[m]) {
                        min = heights[m];
                    }
                }
                area = (j - i + 1) * min;
                if (area > max) {
                    max = area;
                }
            }
        }
        return max;
    }

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
