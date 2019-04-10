#include<iostream>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x): val(x), next(NULL) {}
};

class Solution {
 public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int c = 0;
        int val1, val2;
        ListNode *res, *pt, *last;
        res = new ListNode(0);
        pt = res;
        while (true) {
            val1 = 0;
            val2 = 0;
            if (l1 == NULL && l2 == NULL && c == 0) break;
            if (l1 != NULL) {
                val1 = l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                val2 = l2->val;
                l2 = l2->next;
            }

            res->val = val1 + val2 + c;
            c = 0;
            if (res->val > 9) {
                c = 1;
                res->val -= 10;
            }
            last = res;
            res->next = new ListNode(0);
            res = res->next;
        }
        delete res;
        last->next = NULL;
        return pt;
    }
};


int main() {
    Solution sol;
    ListNode *l1;
    l1 = new ListNode(0);
    // l1 = new ListNode(2);
    // l1->next = new ListNode(4);
    // l1->next->next = new ListNode(3);
    ListNode *l2;
    l2 = new ListNode(0);
    // l2 = new ListNode(5);
    // l2->next = new ListNode(6);
    // l2->next->next = new ListNode(4);

    ListNode *res = sol.addTwoNumbers(l1, l2);
    while (res != NULL) {
        std::cout << res->val << ", ";
        res = res->next;
    }
    std::cout << std::endl;
    return 0;
}
