/* 
 * 1. 网上说的DFS方法是不完整的DFS，没有办法正确回溯，如果正确回溯会超时
 * 2. 使用DP的方法，able[i][j] 表示将第1, 2, ... i种石头组合到一起后是否能取到value是j
 * 实际上是先计算able[1][]，也就是只有第一种石头时都有哪些值可以取到，再在able[1][]
 * 的基础上计算able[2][]，也就是加进去第二种石头后都可以取到哪些值...
 * 截断的方法是，每次只计算value < half的情况，如果组合起来的value大于half了，后
 * 面的都不用计算了
 *  */
#include <iostream>
#include <vector>


using std::cout;
using std::cin;
using std::endl;
using std::vector;


bool DFS(int value, vector<int>& vn, int hf);
bool Divide(vector<int>& vn, int hf);


int main() {

    vector<int> nums(7);
    int sum;
    int half;
    int ind{0};

    std::ios_base::sync_with_stdio(false);

    while (cin >> nums[1] >> nums[2] >>
            nums[3] >> nums[4] >> nums[5] >> nums[6]) {
        sum = 0;
        for (int i{1}; i < 7; ++i) sum += i * nums[i];
        if (sum == 0) return 0;

        if ((sum & 0x0001) == 1) {
            cout << "Collection #" << ++ind << ":\n";
            cout << "Can't be divided.\n\n";
            continue;
        } else half = sum >> 1;

        if (Divide(nums, half)) {
            cout << "Collection #" << ++ind << ":\n";
            cout << "Can be divided.\n\n";
        } else {
            cout << "Collection #" << ++ind << ":\n";
            cout << "Can't be divided.\n\n";
        }
    }
    return 0;
}


bool DFS(int value, vector<int>& vn, int hf) {
    bool res;

    if (value == hf) return true;
    if (value > hf) return false;

    for (int i{6}; i >= 1; --i) {
        if (vn[i] == 0) continue;
        if (value + i > hf) continue;
        --vn [i];
        res = DFS(value + i, vn, hf);
        if (res) return true;
        // ++ vn[i];
    }
    return false;
}


bool Divide(vector<int>& vn, int hf) {
    bool able[7][100000] = {false};
    int ind;

    for (int i{0}; i <= vn[1]; ++i) {
        if (i == hf) return true;
        able[1][i] = true;
    }

    for (int i{2}; i < 7; ++i) {
        for (int j{0}; j <= hf; ++j) {
            if (able[i - 1][j]) {
                able[i][j] = true;
                for (int k{1}; k <= vn[i]; ++k) {
                    ind = j + k * i;
                    if (ind == hf) return true;
                    able[i][ind] = true;
                }
            }

        }
    }

    return false;
}
