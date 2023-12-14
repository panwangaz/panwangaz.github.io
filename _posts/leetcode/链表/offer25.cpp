#include "listnode.h"
#include<vector>
#include<iostream>
using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int val = 0, pre = 0;
        ListNode* rl1 = reverse(l1);
        ListNode* rl2 = reverse(l2);
        ListNode* head = new ListNode();
        ListNode* dh = head;
        while (rl1 || rl2) {
            val += pre;
            if (rl1) {
                val += rl1->val; rl1 = rl1->next;
            }
            if (rl2) {
                val += rl2->val; rl2 = rl2->next;
            }
            pre = val / 10;
            val %= 10;
            ListNode* cur = new ListNode(val);
            dh->next = cur;
            dh = dh->next;
            val = 0;
        }
        if (pre == 1) dh->next = new ListNode(pre);
        return reverse(head->next);
    }

    ListNode* reverse(ListNode* head) {
        if (!head) return head;
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
};

int main() {
    Solution solver = Solution();
    vector<int> input{4, 2, 1, 3};
    vector<int> input1{2, 4, 2};
    cout << "node1: " << endl;
    ListNode* node = ListNode().buildListNode(input);
    cout << "node2: " << endl;
    ListNode* node1 = ListNode().buildListNode(input1);

    ListNode* ans = solver.addTwoNumbers(node, node1);
    cout << "the sum of node1 & node2: " << endl;
    ListNode().printListNode(ans);
    return 0;
}
