#include "treenode.h"
#include<vector>
#include<string>
#include<iostream>
using namespace std;


TreeNode* TreeNode::buildTreeNode(vector<int>& data) {
    TreeNode* node = new TreeNode();
    TreeNode* head = node;
    for (int i = 0; i < data.size(); i++) {
        TreeNode* cur = new TreeNode(data[i]);
        // node->next = cur;
        // node = node->next;
        cout << "node index: " << i << ", " << "value is: " << data[i] << endl;
    }
}
