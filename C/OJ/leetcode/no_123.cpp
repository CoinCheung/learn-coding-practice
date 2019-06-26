#include<vector>
#include<iostream>

using std::vector;
using std::cout;
using std::endl;

#include<algorithm>
using std::max;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }
        int first_buy{-100000}, first_sell{-10000};
        int second_buy{-100000}, second_sell{-10000};
        for (auto &price : prices) {
            first_buy = max(first_buy, -price);
            first_sell = max(price+first_buy, first_sell);

            second_buy = max(first_sell-price, second_buy);
            second_sell = max(price+second_buy, second_sell);
        }
        return second_sell;
    }
};



int main() {
    Solution sol;
    vector<int> prices = {3,3,5,0,0,3,1,4};
    cout << sol.maxProfit(prices) << endl;
}
