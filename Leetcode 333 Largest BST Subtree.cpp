/*
Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.

Note:
A subtree must include all of its descendants.
Here's an example:
    10
    / \
   5  15
  / \   \ 
 1   8   7
The Largest BST Subtree in this case is the highlighted one. 
The return value is the subtree's size, which is 3.
Hint:

You can recursively use algorithm similar to 98. Validate Binary Search Tree at each node of the tree, which will result in O(nlogn) time complexity.
Follow up:
Can you figure out ways to solve it with O(n) time complexity?
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
    // 0 代表 无节点， -1 代表 不合法；
    int DFS(TreeNode *root, int &res, int &minNum, int &maxNum){
        if(!root) return 0;
        int lmin = 0, lmax = 0, rmin = 0, rmax = 0, l = DFS(root->left, res, lmin, lmax), r = DFS(root->right, res, rmin, rmax);
        if(l == -1 || r == -1 || (l && root->val < lmax) || (r && root->val > rmin)) return -1;
        minNum = l ? lmin : root->val;
        maxNum = r ? rmax : root->val;
        res = max(res, l + r + 1);
        return l + r + 1;
    }
    int largestBSTSubtree(TreeNode* root) {
        int res = 0, minNum = 0, maxNum = 0;
        DFS(root, res, minNum, maxNum);
        return res;
    }
};
