/*
描述
小Hi最近游戏上瘾，就让小Ho找一个游戏给他玩。

小Ho想到了那个经典的农夫携狼、山羊、白菜过河的问题，进而回忆起从前玩过的八人过河游戏。

游戏规则是，警察、罪犯、父亲、母亲、两个男孩和两个女孩要过河，小船最多承载两人，只有警察、父亲和母亲能开船。在河的任意一岸或船上，都成立以下事件。

如果罪犯身边没有警察，则罪犯会攻击身边的所有人；如果罪犯身边没有人，则罪犯不会发动攻击。

如果父亲身边没有母亲，则父亲会攻击身边的女孩；如果父亲身边没有女孩，则父亲不会发动攻击。

如果母亲身边没有父亲，则母亲会攻击身边的男孩；如果父亲身边没有男孩，则父亲不会发动攻击。

游戏的目的是让八人在没有任何人发动攻击的情况下都顺利过河。

小Ho把这个游戏安利给小Hi，聪明的小Hi一下子就想出了解法。但小Hi并不满足，他将这个游戏归纳为了一个更具一般性的问题：

有n个人（编号0到n-1）要过河，其中某些人之间具有攻击或制约的单向关系，某些人具有掌舵能力。小船最多承载m个人。

如果B在A的身边，且A能攻击B，则A在不被制约的情况下会立刻攻击B。

如果C能制约A，则C在A的身边时A不能做出攻击行为。

一条船能够开动，仅当其上存在具有掌舵能力的人。

要求输出小船最少的渡河次数（从河的一岸到另一岸算1次），如果不能让所有人都顺利过河，输出-1。

小Hi希望你来玩这个游戏。

输入
第一行为正整数n (n <= 16)和m (m <= 16)，代表总人数与小船最大负载人数。

第二行为正整数a, b, c.

接下来a行，每行两个非负整数x和y，表示x能够攻击y。

接下来b行，每行两个非负整数x和y，表示x能够制约y。

接下来c行，每行一个非负整数x，表示x能够掌舵。

输出
输出仅一行，为最少渡河次数。如果不能顺利过河，输出-1。

样例输入
4 2
2 2 1
1 2
2 3
0 1
0 2
0
样例输出
7
*/

#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>
using namespace std;
#define bits(x) __builtin_popcount(x)
int dp[2][1 << 16];
bool vis[2][1 << 16];
int son[20], par[20];
int boat, tot;
int n, m, a, b, c;

bool safe(int x){
    for(int i = 0;i < n; ++ i)
        if((x >> i & 1) && (par[i] & x) == 0 && (son[i] & x)) // 第i个人在，且没有可以制约他的人，且存在他可以伤害的人
            return 0;
    return 1;
}

int main(){
    int x, y, i, status, s, r;
    scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);
    for(i = 0;i < a; ++ i){
        scanf("%d%d", &x, &y);
        son[x] |= 1 << y; // 他可以伤害的人
    }
    for(i = 0;i < b; ++ i){
        scanf("%d%d", &x, &y);
        par[y] |= 1 << x; // 可以制约他的人
    }
    for(i = 0;i < c; ++ i){
        scanf("%d", &x);
        boat |= 1 << x;   // 可以开船的人
    }
    tot = (1 << n) - 1;
    memset(dp, 0x7f, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    dp[0][tot] = 0;
    queue<int> q;
    q.push(tot << 1);  // 每个状态最后一位表示船的位置(此岸还是彼岸)
    vis[0][tot] = 1;
    while(!q.empty()){
        status = q.front();
        q.pop();
        x = status >> 1; // 此岸的人
        s = status & 1;  // 船的位置
        for(i = x; i; i = (i - 1) & x){  // 遍历这次那些人要开船走
            if(bits(i) > m || (i & boat) == 0) continue;  // 超载或者没有可以开船的人
            y = x ^ i ^ tot;  // 彼岸的人
            if(!safe(i) || !safe(x ^ i) || !safe(y)) continue;  // 此岸彼岸或船上存在不安全现象
            if(dp[s ^ 1][y] <= dp[s][x] + 1) continue;  // 记忆化搜索剪枝
            dp[s ^ 1][y] = dp[s][x] + 1;
            if(!vis[s ^ 1][y]) q.push((y << 1) | (s ^ 1));
            vis[s ^ 1][y] = 1;
        }
    }
    r = dp[1][tot];
    if(r < 0) r = -1;
    printf("%d\n", r);
    return 0;
}
