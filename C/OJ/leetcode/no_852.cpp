#include<vector>

using std::vector;

class Solution {
 public:
    int peakIndexInMountainArray(vector<int>& A) {
        int peak_idx{1};
        int len{A.size()};

        for (int i{1}; i < len-1; ++i) {
            if (A[i-1] < A[i] && A[i] > A[i+1]) {
                peak_idx = i;
                break;
            }
        }
        return peak_idx;
    }
};


#include<iostream>

using std::cout;
using std::endl;

int main() {
    Solution sol;
    vector<int> in{3, 4, 5, 1};
    cout << sol.peakIndexInMountainArray(in) << endl;
    
    return 0;
}
