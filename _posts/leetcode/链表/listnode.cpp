#include<vector>
#include<string>
#include<iostream>
#include "listnode.h"
using namespace std;

ListNode* ListNode::buildListNode(vector<int>& data) {
    ListNode* node = new ListNode();
    ListNode* head = node;
    for (int i = 0; i < data.size(); i++) {
        ListNode* cur = new ListNode(data[i]);
        node->next = cur;
        node = node->next;
        cout << "node index: " << i << ", " << "value is: " << data[i] << endl;
    }
    return head->next;
}

void ListNode::printListNode(ListNode* node) {
    ListNode* cur = node;
    int index = 0;
    while (cur) {
        cout << "node index: " << index++ << ", " << "value is: " << cur->val << endl;
        cur = cur->next;
    }
}
