/*
描述
小Hi有一棵N个节点的树，编号1-N，其中1号节点是整棵树的根。他把这棵树的N-1条边记录成N-1行，每行2个整数a和b，表示a是b的父节点。  

喜欢恶作剧的小Ho在小Hi的记录里加了一行两个整数，于是小Hi不得设法找出这行可疑的记录。具体来说，如果去掉某一行之后，余下N-1行按小Hi的规则（a是b的父节点）恰好能构成一棵N个节点的树，并且满足编号恰好是1-N且1号节点是根，那么被去掉的一行就被视为可疑的。  

你能帮小Hi找出所有可疑的记录吗？

输入
第一行包含一个整数N，表示树的节点数目。  

以下N行每行两个整数a和b，表示a是b的父节点。  

对于30%的数据，1 <= N <= 1000  

对于100%的数据, 1 <= N <= 100000， 1 <= a, b <= N

输入保证合法。

输出
输出一行包含若干个从小到大的整数，表示可疑的行号。（行号从1开始）

样例输入
3
1 2
1 3
1 3
样例输出
2 3
*/

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode{
    vector<int> parents;
    vector<int> row;
    vector<int> children;
    TreeNode(){parents.clear(); row.clear();};
};

void DFS(vector<TreeNode> &vtr, int root, int &counter, const int &p, const int &c){
    counter ++;
    for(int i = 0;i < vtr[root].children.size(); ++ i){
        if(root != p || vtr[root].children[i] != c)
            DFS(vtr, vtr[root].children[i], counter, p, c);
    }
}

int main() {
    int n, p, c, maxP = 0, f = 1, counter;
    cin >> n;
    vector<TreeNode> vtr(n + 1);
    for(int i = 1;i <= n; ++ i){
        cin >> p >> c;
        vtr[c].parents.push_back(p);
        vtr[c].row.push_back(i);
        vtr[p].children.push_back(c);
        maxP = max(maxP, int(vtr[c].parents.size()));
        if(vtr[c].parents.size() == 2) f = c;
    }
    if(maxP == 2) {
        vector<int> res;
        for(int i = 0;i < 2; ++ i){
            counter = 0;
            DFS(vtr, 1, counter, vtr[f].parents[i], f);
            if(counter == n)
                res.push_back(vtr[f].row[i]);
        }
        cout << res[0];
        if(res.size() >= 2) cout << " " << res[1];
        cout << endl;
    }
    else cout << vtr[1].row[0] << endl;
    return 0;
}
