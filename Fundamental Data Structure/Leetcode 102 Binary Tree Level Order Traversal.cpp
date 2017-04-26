/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
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
    void DFS(TreeNode* root, vector<vector<int>> &res, int depth){
        if(!root) return;
        if(res.size() == depth)
            res.push_back(vector<int>());
        res[depth].push_back(root->val);
        DFS(root->left, res, depth + 1);
        DFS(root->right, res, depth + 1);
    }
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        DFS(root, res, 0);
        return res;
    }
};
