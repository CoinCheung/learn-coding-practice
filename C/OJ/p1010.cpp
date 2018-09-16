#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>

/* 
 * 这个注意的地方是: 
 * 1. 做DFS的时候，当num == 4的时候，判断完了就直接return, 不要放在下一层迭代里面去判断是否num == 5。这样会增加一轮判断，影响效率，而且改变了req的值会使结果不准确
 * 2. 这里的DFS是有截断的，当ind[i]是j的时候，迭代的下一层ind[i+1]要从j开始，而不是从0开始，这样就避免了顺序不同引入的重复，可以减小次数。不这样会超时
 *  */

using std::cout;
using std::cin;
using std::endl;
using std::vector;


class Solution {
    public:
        int data[4];
        int inds[4];
        int type_num;
        int num;
        int max;

        void init();
        void Cal();
};


void Solution::init() {
    type_num = 0;
    num = 0;
    max = -1;
}


void Solution::Cal() {
    max = -1;
    type_num = 0;
    for (int i{0}; i < num; ++i) {
        if (max < data[i]) max = data[i];
    }

    for (int i{0}; i < num; ++i) {
        ++type_num;
        for (int j{0}; j < i; ++j) {
            if (inds[j] == inds[i]) {
                --type_num;
                break;
            }
        }
    }
}


void Solve(int stmps[], int st_num, const int req, Solution& res,
        bool& none, bool& tie, int& type_num);
void DFS(int req, int digit, Solution& res, const int stmps[], const int st_num,
        bool& none, bool& tie, Solution& best);
    

int main() {

    int n;
    int cus_num;
    bool tie;
    bool none;
    int type_num;
    int stmps[300];
    int st_ind;
    int reqs[300];
    int rq_ind;
    // vector<int> reqs;
    Solution res;
    // reqs.reserve(200);

    while (scanf("%d", &n) != EOF) {
        for(int i{0}; i < 27; ++i) stmps[i] = 0;
        st_ind = 0;
        rq_ind = 0;
        stmps[st_ind++] = n;
        while(scanf("%d", &n)) {
            if (n == 0) break;
            stmps[st_ind++] = n;
        }
        while(scanf("%d", &n)) {
            if (n == 0) break;
            reqs[rq_ind++] = n;
        }

        cus_num = rq_ind;
        for (int i{0}; i < cus_num; ++i) {
            Solve(stmps, st_ind, reqs[i], res, none, tie, type_num);

            if (tie) {
                printf("%d (%d): tie\n", reqs[i], res.type_num);
            } else if (none) {
                printf("%d ---- none\n", reqs[i]);
            } else {
                printf("%d (%d):", reqs[i], res.type_num);
                for (int i{0}; i < res.num; ++i) {
                    printf(" %d", res.data[i]);
                }
                cout << "\n";
            }
        }
    }
    return 0;
}


void Solve(int stmps[], int st_num, const int req, Solution& res,
        bool& none, bool& tie, int& type_num) {
    none = true;
    tie = false;

    Solution curr;
    curr.init();
    res.init();
    DFS(req, 0, curr, stmps, st_num, none, tie, res);

    type_num = res.type_num;
}


void DFS(int req, int digit, Solution& curr, const int stmps[], const int st_num,
        bool& none, bool& tie, Solution& best) {
    if (req < 0) return;
    if (req == 0) {
        none = false;
        curr.Cal();
        if (curr.type_num > best.type_num) {
            tie = false;
            best = curr;
            return;
        } else if (curr.type_num == best.type_num) {
            if (curr.num < best.num) {
                tie = false;
                best = curr;
                return;
            } else if (curr.num == best.num) {
                if (curr.max > best.max) {
                    tie = false;
                    best = curr;
                    return;
                } else if (curr.max == best.max) {
                    tie = true;
                    return;
                }
            }
        }
    }
    if (curr.num == 4) return; // 在这里判断，而且判断是否 num == 4，而不是5

    ++curr.num;
    int types = st_num;
    for (int i{digit}; i < types; ++i) {  // 这里每次从digit开始，而不是0开始，之前搜索过的解后面就不再搜索了
        curr.data[curr.num-1] = stmps[i];
        curr.inds[curr.num-1] = i;
        DFS(req - stmps[i], i, curr, stmps, st_num, none, tie, best);
    }
    --curr.num;
}
