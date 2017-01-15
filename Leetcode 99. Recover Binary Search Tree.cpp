/*

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
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
    TreeNode *fir = NULL, *sec = NULL;
    void DFS(TreeNode *root, bool &flag){
        if(!root) return;
        DFS(root->left, flag);
        if(flag){
            if(fir && fir->val > root->val){
                flag = false;
                sec = root;
            }
            else fir = root;
        }
        else{
            if(!(sec && sec->val < root->val))
                sec = root;
        }
        DFS(root->right, flag);
    }
public:
    void recoverTree(TreeNode* root) {
        fir = NULL, sec = NULL;
        bool flag = true;
        DFS(root, flag);
        swap(fir->val, sec->val);
    }
};
