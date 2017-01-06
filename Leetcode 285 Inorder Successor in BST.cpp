/*
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        //p有右子节点，可以直接找到；
        if(p->right){
            p = p->right;
            while(p->left)
                p = p->left;
            return p;
        }
        //p无右子节点，则中序遍历以p为最后一个节点的最大子树的父节点（最大子树必为该父节点的左子树）即为答案，若最大子树即整棵树，则无后继节点。
        TreeNode *candidate = NULL;
        while (root != p)
            root = (p->val > root->val) ? root->right : (candidate = root)->left;
        return candidate;
    }
};

// 也可以不单独考虑，直接找比P大的最小的数字即可。(大时移至左子树变小，小时移至右子树变大，相等时移至右子树，记录最后一个变小操作后的值)
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* candidate = NULL;
        while (root)
            root = (root->val > p->val) ? (candidate = root)->left : root->right;
        return candidate;
    }
};
