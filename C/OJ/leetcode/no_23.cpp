#include<vector>
#include<iostream>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
 public:
    ListNode* mergeKLists(const vector<ListNode*>& lists) {
        int k = lists.size();
        if (k == 0) return NULL;
        ListNode *res, *pt;
        vector<ListNode*> heap;
        heap.resize(k);
        for (int i{0}; i < k; ++i) {
            heap[i] = lists[i];
        }

        filter_heap(heap);
        if (heap[0] == NULL) return NULL;
        k = heap.size();

        adjustHeap(heap);
        res = heap[0];
        pt = res;
        heap[0] = heap[0]->next;
        if (heap[0] == NULL) {
            heap[0] = heap[k-1];
            --k;
            heap.resize(k);
        }

        while (k > 0) {
            adjustHeap(heap);
            pt->next = heap[0];
            pt = pt->next;
            heap[0] = heap[0]->next;

            if (heap[0] == NULL) {
                heap[0] = heap[k-1];
                --k;
                heap.resize(k);
            }
        }
        return res;
    }

    void filter_heap(vector<ListNode*>& heap) {
        int k = heap.size();
        for (int i{0}; i < k; ++i) {
            for (int j{0}; j < k-1; ++j) {
                if (heap[j] == NULL) {
                    auto tmp = heap[j];
                    heap[j] = heap[j+1];
                    heap[j+1] = tmp;
                }
            }
        }
        int rear = 0;
        for (int i{k-1}; i >= 0; --i) {
            if (heap[i] != NULL) {
                rear = i;
                break;
            }
        }
        heap.resize(rear+1);
    }

    void adjustHeap(vector<ListNode*>& heap) {
        int k = heap.size();
        int last;
        last = (k-1)/2;
        for (int i{last}; i >= 0; --i) {
            adjust(heap, i);
        }
    }

    void adjust(vector<ListNode*>& heap, int curr) {
        int child1, child2, small;
        int k = heap.size();
        child1 = (curr << 1) + 1;
        child2 = (curr << 1) + 2;
        if (child1 >= k) return;
        small = child1;
        if (child2 < k) {
            if (heap[child1]->val > heap[child2]->val) {
                small = child2;
            }
        }
        if (heap[curr]->val > heap[small]->val) {
            auto tmp = heap[curr];
            heap[curr] = heap[small];
            heap[small] = tmp;
            adjust(heap, small);
        }
    }
};


int main() {
    // Solution sol;
    // int n_node = 7;
    // int data[] = {2, 8, 3, 6, 4, 6, 5};
    // vector<ListNode*> heap;
    // heap.reserve(n_node);
    // for (int i=0; i < n_node; ++i) {
    //     heap.push_back(new ListNode(data[i]));
    // }
    // sol.adjustHeap(heap);
    // for (int i=0; i < n_node; ++i) {
    //     cout << data[i] << ", ";
    // }
    // cout << endl;
    // for (int i=0; i < n_node; ++i) {
    //     cout << heap[i]->val << ", ";
    // }
    
    Solution sol;
    vector<ListNode*> list;
    list.reserve(1);
    list.push_back(NULL);
    sol.mergeKLists(list);
    list.push_back(NULL);
    list.push_back(new ListNode(1));
    sol.mergeKLists(list);
    return 0;
}
