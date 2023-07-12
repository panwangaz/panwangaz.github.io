#include<vector>
#include<iostream>
using namespace std;

//  Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* buildListNode(vector<int>& data) {
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

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head) return head;
        return sort(head);
    }

    ListNode* sort(ListNode* head) {
        if (!head) return head;
        ListNode* mid = findMid(head);
        ListNode* next = mid->next;
        mid->next = nullptr;
        ListNode* pre = sort(head);
        ListNode* post = sort(next);
        return merge(pre, post);
    }

    ListNode* findMid(ListNode* head) {
        if (!head) return head;
        ListNode* slow = head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* merge(ListNode* pre, ListNode* post) {
        if (!pre) return post;
        if (!post) return pre;
        ListNode* dummyHead = new ListNode();
        ListNode* cur = dummyHead;
        while (post && pre) {
            if (post->val > pre->val) {
                cur->next = pre;
                pre = pre->next;
            }
            else {
                cur->next = post;
                post = post->next;
            }
            cur = cur->next;
        }
        cur->next = post ? post : pre;
        return dummyHead->next;
    }
};

int main() {
    Solution solver = Solution();
    int data[5]{4,2,1,3};
    vector<int> input{4, 2, 1, 3};
    ListNode* node = buildListNode(input);
    solver.sortList(node);
    return 0;
}
