/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],
   1
    \
     2
    /
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(!root) return res;
        stack<TreeNode *> stk;
        TreeNode *node = NULL;
        stk.push(root);
        while(!stk.empty()){
            node = stk.top();
            if(node->left){
                stk.push(node->left);
                node->left = NULL;
            }
            else{
                stk.pop();
                res.push_back(node->val);
                if(node->right) stk.push(node->right);
            }
        }
        return res;
    }
};
