/*
时间限制：1秒 空间限制：32768K
题目描述
git是一种分布式代码管理工具，git通过树的形式记录文件的更改历史，比如： base'<--base<--A<--A' ^ | --- B<--B' 小米工程师常常需要寻找两个分支最近的分割点，即base.假设git 树是多叉树，请实现一个算法，计算git树上任意两点的最近分割点。 （假设git树节点数为n,用邻接矩阵的形式表示git树：字符串数组matrix包含n个字符串，每个字符串由字符'0'或'1'组成，长度为n。matrix[i][j]=='1'当且仅当git树种第i个和第j个节点有连接。节点0为git树的根节点。） 
输入例子:
[01011,10100,01000,10000,10000],1,2
输出例子:
1
*/

class Solution {
public:
    struct TreeNode{
        int val;
        vector<TreeNode *> children;
        TreeNode(int _v):val(_v){children.clear();}
    };
    TreeNode *DFS(TreeNode *root, TreeNode *a, TreeNode *b){
        if(!root || root == a || root == b) return root;
        TreeNode *t = NULL, *res = NULL;
        int counter = 0;
        for(int i = 0;i < root->children.size(); ++ i){
            t = DFS(root->children[i], a, b);
            if(t) {
                counter ++;
                res = t;
            }
        }
        if(counter == 2) return root;
        else return res;
    };
    
    /**
     * 返回git树上两点的最近分割点
     * 
     * @param matrix 接邻矩阵，表示git树，matrix[i][j] == '1' 当且仅当git树中第i个和第j个节点有连接，节点0为git树的跟节点
     * @param indexA 节点A的index
     * @param indexB 节点B的index
     * @return 整型
     */
    int getSplitNode(vector<string> matrix, int indexA, int indexB) {
		if(matrix.empty()) return -1;
        int n = matrix.size();
        vector<TreeNode*> vtr;
        vector<bool> flags(n, 1);
        for(int i = 0;i < n; ++ i) vtr.push_back(new TreeNode(i));
        queue<TreeNode *> q;
        q.push(vtr[0]);
        flags[0] = 0;
        while(!q.empty()){
            TreeNode *t = q.front();
            q.pop();
            for(int i = 0;i < n; ++ i){
                if(matrix[t->val][i] == '1' && flags[i]){
                    t->children.emplace_back(vtr[i]);
                    q.push(vtr[i]);
                    flags[i] = 0;
                }
            }
        }
        TreeNode *res = DFS(vtr[0], vtr[indexA], vtr[indexB]);
        return res->val;
    }
};
