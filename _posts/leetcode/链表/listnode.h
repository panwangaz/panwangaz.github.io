#ifndef LISTNODE_H
#define LISTNODE_H

#include<vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    ListNode* buildListNode(vector<int>& x);
    void printListNode(ListNode* node);
};


#endif
