/*

Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
For example:
Given BST [1,null,2,2],
   1
    \
     2
    /
   2
return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).

Subscribe to see which companies asked this question.

*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void getMaxFreq(TreeNode *root, int &mfq, int &pre, int &cnt){
        if(!root) return;
        getMaxFreq(root->left, mfq, pre, cnt);
        getMaxFreq(root->right, mfq = max(mfq, cnt), pre = root->val, ++ (cnt *= (root->val == pre)));
    }
    void getMode(TreeNode *root, int &mfq, int &pre, int &cnt, vector<int> &res){
        if(!root) return;
        getMode(root->left, mfq, pre, cnt, res);
        if (mfq == ++ (cnt *= (root->val == pre))) res.push_back(root->val);
        getMode(root->right, mfq, pre = root->val, cnt, res);
    }
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        int pre = 0, cnt = 0, mfq = 0;
        getMaxFreq(root, mfq, pre, cnt);
        getMode(root, mfq, pre, cnt = 0, res);
        return res;
    }
};
