/*
描述
In a video game, Little Hi is going to assassinate the leader of an evil group, EL SUENO.

There are N high-value targets in the group, numbered from 1 to N. Each target has another target as his direct superior except for EL SUENO who has no superior. So the superior-subordinate hierarchy forms a tree-like structure. EL SUENO is at the root.

The cost of assassinating the i-th target is Ci. Before assassinating a target Little Hi has to obtain enough information about him. For the i-th target, Little Hi needs INi units of information. By assassinating a target Little Hi will obtain some information about the target's direct superior. More specifically, the i-th target has IPi units of information about his superior. So in order to assassinate EL SUENO, Little Hi needs to assassinate some of his direct subordinates so that the sum of information obtained is enough; assassinating the subordinates needs to assassinate their direct subordinates ... until it reaches some targets require zero information in advance. (Luckily if a target has no subordinate he always requires zero information.)

How Little Hi wants to know what is the minimum cost for successful assassinating EL SUENO.  

输入
The first line contains an integer N.

Then follow N lines. Each line describes a target with 4 integers, Fi, INi, IPi, Ci.  

Fi is i-th target's superior. For EL SUENO his Fi is zero.

INi is the amount of information needed to assassinate the i-th target. For a target has no subordinates his INi is always zero.

IPi is the amount of information the i-th target has about his superior Fi.

Ci is the cost of assassinating the i-th target.

For 30% of the data, 1 <= N <= 10, 0 <= INi, IPi <= 100

For 60% of the data, 1 <= N <= 100, 0 <= INi, IPi <= 1000

For 100% of the data, 1 <= N <= 2000, 0 <= Fi <= N, 0 <= INi, IPi <= 20000, 1 <= Ci <= 1000.

It is guaranteed that the N targets form a tree structure.

输出
The minimum cost. If Little Hi is not able to assassinate EL SUENO output a number -1.

样例输入
6
2 1 2 2
0 4 0 2
2 0 2 5
2 0 2 6
1 0 1 2
1 0 1 3
样例输出
11
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 2000000;

struct TreeNode{
    int in, ip, c, cost;
    vector<TreeNode *> children;
    TreeNode(){in = ip = c = cost = 0;}
};

void DFS(TreeNode *boss){
    if(!boss->in) return;
    int n = (int)boss->children.size(), i, j;
    for(int i = 0;i < n; ++ i)
        DFS(boss->children[i]);
    
//    vector<vector<int>> dp(n + 1, vector<int>(boss->in + 1, MAX));  // dp[i][j]表示从前i个子结点里挑出几个，满足提供信息总和不小于j所需的最小cost;
//    dp[0][0] = 0;
//    for(i = 1; i <= n; ++ i){
//        dp[i][0] = 0;
//        for(j = 1; j <= boss->in; ++ j)
//            dp[i][j] = min(dp[i - 1][j], boss->children[i - 1]->cost + (j < boss->children[i - 1]->ip ? 0 : dp[i - 1][j - boss->children[i - 1]->ip]));
//    }
//    boss->cost += dp[n][boss->in];
    
    vector<int> dp(boss->in + 1, MAX);
    dp[0] = 0;
    for(i = 1; i <= n; ++ i){
        for(j = boss->in; j >= 1; -- j)
            dp[j] = min(dp[j], boss->children[i - 1]->cost + (j < boss->children[i - 1]->ip ? 0 : dp[j - boss->children[i - 1]->ip]));
    }
    boss->cost += dp[boss->in];
    
    return ;
}

int main(){
    int N, f;
    scanf("%d", &N);
    TreeNode *boss = NULL;
    vector<TreeNode> Nodes(N + 1);
    for(int i = 1;i <= N; ++ i){
        scanf("%d%d%d%d", &f, &Nodes[i].in, &Nodes[i].ip, &Nodes[i].c);
        Nodes[i].cost = Nodes[i].c;
        if(!f) boss = &Nodes[i];
        else Nodes[f].children.push_back(&Nodes[i]);
    }
    DFS(boss);
    printf("%d\n", boss->cost > MAX ? -1 : boss->cost);
    return 0;
}
