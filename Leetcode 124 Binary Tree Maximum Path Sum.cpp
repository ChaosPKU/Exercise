/*
Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.
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
private:
    int DFS(TreeNode* root, int& res){
        if(!root) return 0;
        int l = DFS(root->left, res), r  = DFS(root->right, res);
        res = max(max(l,0) + max(r,0) + root->val, res);
        return max(max(l, r), 0) + root->val;
    }
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        DFS(root, res);
        return res;
    }
};
