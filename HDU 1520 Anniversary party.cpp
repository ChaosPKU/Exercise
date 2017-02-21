/*
 Anniversary party
 总时间限制: 1000ms 内存限制: 65536kB
 描述
 There is going to be a party to celebrate the 80-th Anniversary of the Ural State University. The University has a hierarchical structure of employees. It means that the supervisor relation forms a tree rooted at the rector V. E. Tretyakov. In order to make the party funny for every one, the rector does not want both an employee and his or her immediate supervisor to be present. The personnel office has evaluated conviviality of each employee, so everyone has some number (rating) attached to him or her. Your task is to make a list of guests with the maximal possible sum of guests' conviviality ratings.
 输入
 Employees are numbered from 1 to N. A first line of input contains a number N. 1 <= N <= 6 000. Each of the subsequent N lines contains the conviviality rating of the corresponding employee. Conviviality rating is an integer number in a range from -128 to 127. After that go N – 1 lines that describe a supervisor relation tree. Each line of the tree specification has the form:
 L K
 It means that the K-th employee is an immediate supervisor of the L-th employee. Input is ended with the line
 0 0
 输出
 Output should contain the maximal sum of guests' ratings.
 样例输入
 7
 1
 1
 1
 1
 1
 1
 1
 1 3
 2 3
 6 4
 7 4
 4 5
 3 5
 0 0
 样例输出
 5
*/
#include <iostream>
#include <vector>
using namespace std;
struct TreeNode {
    bool isRoot;
    int val;
    int idx;
    int res;
    int none_res;
    vector<TreeNode*> children;
    TreeNode(int v, int i) : val(v), isRoot(1), idx(i) {
        children.clear();
        none_res = 0;
        res = v;
    }
};
void DFS(TreeNode* root){
    if(!root) return;
    for(int i = 0;i < root->children.size(); ++ i)
        DFS(root->children[i]);
    for(int i = 0;i < root->children.size(); ++ i){
        root->res += root->children[i]->none_res;
        root->none_res += max(root->children[i]->res, root->children[i]->none_res);
    }
}
int main() {
    int N, D, L, K;
    TreeNode* root = NULL;
    cin >> N;
    vector<TreeNode*> trees;
    for(int i = 0;i < N; ++ i){
        cin >> D;
        trees.push_back(new TreeNode(D, i));
    }
    for(int i = 0;i < N - 1; ++ i){
        cin >> L >> K;
        trees[L - 1]->isRoot = 0;
        trees[K - 1]->children.push_back(trees[L - 1]);
    }
    for(int i = 0;i < N; ++ i)
        if(trees[i]->isRoot){
            root = trees[i];
            break;
        }
    DFS(root);
    cout << max(root->res, root->none_res) << endl;
    return 0;
}
