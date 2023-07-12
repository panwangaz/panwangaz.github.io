#ifndef LISTNODE_H
#define LISTNODE_H

#include<vector>
using namespace std;

//  Definition for tree list.
struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode* buildTreeNode(vector<int>& x);
};

#endif LISTNODE_H
