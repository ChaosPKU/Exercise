#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Tree {
    TreeNode *root;
    unordered_map<int, int> inorder_map;
    
    Tree(){root = NULL;};
    
    Tree(const vector<int> &inorder, const vector<int> &porder, const bool &op, const bool &print_null){
        int n = (int)inorder.size(), _n = (int)porder.size();
        if(n != _n) throw "Invalid Construction!";
        inorder_map.clear();
        for(int i = 0;i < n; ++ i)
            inorder_map[inorder[i]] = i;
        if(op) {
            root = gen_tree_from_in_pre(inorder, porder, 0, n - 1, 0, n - 1);
            postorder_traversal(print_null);
        }
        else {
            root = gen_tree_from_in_post(inorder, porder, 0, n - 1, 0, n - 1);
            preorder_traversal(print_null);
        }
    }
    TreeNode *gen_tree_from_in_pre(const vector<int> &inorder, const vector<int> &preorder, int ib, int ie, int pb, int pe){
        if(ie < ib || pe < pb) return NULL;
        TreeNode *node = new TreeNode(preorder[pb]);
        int im = inorder_map[preorder[pb]];
        node->left = gen_tree_from_in_pre(inorder, preorder, ib, im - 1, pb + 1, pb + 1 + im - 1 - ib);
        node->right = gen_tree_from_in_pre(inorder, preorder, im + 1, ie, pe - ie + im + 1, pe);
        return node;
    }
    TreeNode *gen_tree_from_in_post(const vector<int> &inorder, const vector<int> &postorder, int ib, int ie, int pb, int pe){
        if(ie < ib || pe < pb) return NULL;
        TreeNode *node = new TreeNode(postorder[pe]);
        int im = inorder_map[postorder[pe]];
        node->left = gen_tree_from_in_post(inorder, postorder, ib, im - 1, pb, pb + im - 1 - ib);
        node->right = gen_tree_from_in_post(inorder, postorder, im + 1, ie, pe - ie + im, pe - 1);
        return node;
    }
    
    void inorder_traversal(const bool &print_null){
        inorder_traversal(root, print_null);
        cout << endl;
    }
    void inorder_traversal(TreeNode *node, const bool &print_null){
        if(!node) {if(print_null) cout << "null "; return;}
        inorder_traversal(node->left, print_null);
        cout << node->val << " ";
        inorder_traversal(node->right, print_null);
    }
    
    void preorder_traversal(const bool &print_null){
        preorder_traversal(root, print_null);
        cout << endl;
    }
    void preorder_traversal(TreeNode *node, const bool &print_null){
        if(!node) {if(print_null) cout << "null "; return;}
        cout << node->val << " ";
        preorder_traversal(node->left, print_null);
        preorder_traversal(node->right, print_null);
    }
    
    void postorder_traversal(const bool &print_null){
        postorder_traversal(root, print_null);
        cout << endl;
    }
    void postorder_traversal(TreeNode *node, const bool &print_null){
        if(!node) {if(print_null) cout << "null "; return;}
        postorder_traversal(node->left, print_null);
        postorder_traversal(node->right, print_null);
        cout << node->val << " ";
    }
};

int main(){
    vector<int> inorder({2, 1, 3});
    vector<int> preorder({1, 2, 3});
//    vector<int> postorder({2, 3, 1});
    Tree tree(inorder, preorder, 1, 1); // 第一个参数一定是inorder遍历数组, 第三个参数是1则第二个是preorder, 否则是postorder, 第四个参数表示是否打印null节点。
    return 0;
}
