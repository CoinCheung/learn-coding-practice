#include<vector>

#include<algorithm>

using std::max;
using std::vector;


class Solution {
 public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.size() == 0 or k == 0) {
            return 0;
        }
        if (k > prices.size() / 2) {
            return greedy_method(prices);
        }
        vector<int> buys(k), sells(k);
        for (int i{0}; i < k; ++i) {
            buys[i] = -100000;
            sells[i] = -100000;
        }
        for (auto &el : prices) {
            for (int i{0}; i < k; ++i) {
                if (i == 0) {
                    buys[i] = max(buys[i], -el);
                } else {
                    buys[i] = max(buys[i], sells[i-1]-el);
                }
                sells[i] = max(sells[i], buys[i]+el);
            }
        }
        return sells[k-1];
    }

    int greedy_method(vector<int> prices) {
        if (prices.size() <= 1) {
            return 0;
        }
        int res{0};
        for (int i{1}; i < prices.size(); ++i) {
            if (prices[i] > prices[i-1]) {
                res += prices[i] - prices[i-1];
            }
        }
        return res;
    }
};


#include<iostream>
#include<climits>

using std::cout;
using std::endl;

int main() {
    Solution sol;
    // vector<int> vi{2, 4, 1};
    // vector<int> vi{3, 2, 6, 5, 0, 3};
    vector<int> vi{2, 4, 1};
    cout << sol.maxProfit(2, vi) << endl;
    int a{1000000000};
    cout << a << endl;
    return 0;
}
