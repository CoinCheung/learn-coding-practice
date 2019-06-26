#include<iostream>
#include<vector>
using namespace std;

class Solution {
 public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        int profit = 0;
        for (int i{0}; i < prices.size()-1; ++i) {
            if (prices[i] < prices[i+1]) {
                profit += prices[i+1] - prices[i];
            }
        }
        return profit;
    }
};


int main() {
    Solution sol;
    vector<int> prices = {};
    cout << prices.size() << endl;
    sol.maxProfit(prices);
}
