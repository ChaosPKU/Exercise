/*
 描述
 小Hi最近参加了一场比赛，这场比赛中小Hi被要求将一棵树拆成3份，使得每一份中所有节点的权值和相等。
 
 比赛结束后，小Hi发现虽然大家得到的树几乎一模一样，但是每个人的方法都有所不同。于是小Hi希望知道，对于一棵给定的有根树，在选取其中2个非根节点并将它们与它们的父亲节点分开后，所形成的三棵子树的节点权值之和能够两两相等的方案有多少种。
 
 两种方案被看做不同的方案，当且仅当形成方案的2个节点不完全相同。
 
 输入
 每个输入文件包含多组输入，在输入的第一行为一个整数T，表示数据的组数。
 
 每组输入的第一行为一个整数N，表示给出的这棵树的节点数。
 
 接下来N行，依次描述结点1~N，其中第i行为两个整数Vi和Pi，分别描述这个节点的权值和其父亲节点的编号。
 
 父亲节点编号为0的节点为这棵树的根节点。
 
 对于30%的数据，满足3<=N<=100
 
 对于100%的数据，满足3<=N<=100000, |Vi|<=100, T<=10
 
 输出
 对于每组输入，输出一行Ans，表示方案的数量。
 
 样例输入
 2
 3
 1 0
 1 1
 1 2
 4
 1 0
 1 1
 1 2
 1 3
 样例输出
 1
 0
 */

/*
对于每个子树和为 total_sum / 3的点，总数加上根到此点路径上子树和为2 * total_sum / 3的点的个数，和不在此路径上子树和为total_sum / 3的点的个数(需要避免重复计算)。
 */


#include <iostream>
#include <vector>
using namespace std;

void getSubtreeSum(int &root, const vector<vector<int>> &linklist, const vector<int> &value, vector<int> &sum){
    sum[root] = value[root];
    for(int child : linklist[root]){
        getSubtreeSum(child, linklist, value, sum);
        sum[root] += sum[child];
    }
}

void DFS(int node, const vector<vector<int>> &linklist, const vector<int> &sum, const vector<int> &value, const int &n, int &num1, int &num2, long long &res, const int &root){
    if(sum[node] == n) res += num1 + num2;
    if(node != root && sum[node] == 2 * n) num2 ++;
    for(int child : linklist[node])
        DFS(child, linklist, sum, value, n, num1, num2, res, root);
    if(sum[node] == n) num1 ++;
    if(node != root && sum[node] == 2 * n) num2 --;
}
int main(){
    int T, N;
    int root, p, n, num1, num2;
    long long res;
    cin >> T;
    for(int i = 0;i < T; ++ i){
        cin >> N;
        vector<vector<int>> linklist(N);
        vector<int> value(N), sum(N);
        for(int i = 0;i < N; ++ i){
            cin >> value[i] >> p;
            if(p == 0) root = i;
            else linklist[p - 1].push_back(i);
        }
        getSubtreeSum(root, linklist, value, sum);
        if(sum[root] % 3 != 0)
            cout << 0 << endl;
        else {
            n = sum[root] / 3;
            num1 = num2 = res = 0;
            DFS(root, linklist, sum, value, n, num1, num2, res, root);
            cout << res << endl;
        }
    }
    return 0;
}
