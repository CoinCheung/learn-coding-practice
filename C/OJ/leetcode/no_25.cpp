#include<iostream>

using std::cout;
using std::endl;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
 public:
    void reverse(ListNode* h, ListNode* r) {
        ListNode *p1, *p2, *p3;
        p1 = h;
        p2 = p1->next;
        if (p2 != NULL) {
            p3 = p2->next;
        }
        while (true) {
            p2->next = p1;
            if (p2 == r) {
                break;
            }
            p1 = p2;
            p2 = p3;
            p3 = p3->next;
        }
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;
        ListNode* tmp{head};
        int len{0};
        while (tmp != NULL) {
            ++len;
            tmp = tmp->next;
        }
        int n_sublist = len / k;
        if (n_sublist == 0) return head;

        ListNode *h, *r, *pre, *next, *new_head{NULL};;
        h = head;
        for (int i{0}; i < n_sublist; ++i) {
            r = h;
            for (int j{1}; j < k; ++j) {
                r = r->next;
            }
            next = r->next;
            reverse(h, r);
            h->next = next;
            if (i == 0) {
                new_head = r;
            } else {
                pre->next = r;
            }
            pre = h;
            h = next;
        }
        return new_head;
    }

    void print(ListNode* head) {
        while (head != NULL) {
        // for (int i{0}; i < 5; ++i) {
            cout << head->val << endl;
            head = head->next;
        }

    }
        //
        //
        // ListNode *p1, *p2, *p3, *res, *new_head{NULL};;
        // for (int i{0}; i < n_sublist; ++i) {
        //     p1 = head;
        //     p2 = head->next;
        //     p3 = p2->next;
        //     for (int j{0}; j < k-1; ++j) {
        //         p2->next = p1;
        //         p1 = p2;
        //         p2 = p3;
        //         if (p3->next != NULL) {
        //             p3 = p3->next;
        //         }
        //     }
        //     head->next = p1->next;
        //     head = p1->next;
        //     if (i == 0) {
        //         cout << "new head: " << new_head << endl;
        //         new_head = p1;
        //     }
        // }
        // return new_head;
    // }
};


int main() {
    Solution sol;
    int k=2;
    ListNode *head{new ListNode(1)};
    ListNode *curr{head};
    for (int i{1}; i < 5; ++i) {
        curr->next = new ListNode(i+1);
        curr = curr->next;
    }
    auto res = sol.reverseKGroup(head, 2);
    // while (res != NULL) {
    for (int i{0}; i < 5; ++i) {
        cout << res->val << endl;
        res = res->next;
    }
    return 0;
}
