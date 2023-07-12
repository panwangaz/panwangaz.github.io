#include<vector>
#include<string>
#include<iostream>
using namespace std;

struct ListNode {
    ListNode* next;
    int val;
    ListNode(int x) : val(x), next(NULL) {}
};
