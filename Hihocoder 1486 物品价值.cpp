/*

描述
小Hi现在有n个物品，每个物品都有一个价值。并且这n个物品总共有m个不同的属性，每个物品都具有其中若干属性。

小Ho要从中选出若干物品，满足每个属性都正好有奇数个物品拥有，且被选出的物品价值总和最大。你能帮助小Ho完成任务么？

输入
第一行一个数T(<=10)，表示数据组数。对于每一组数据：

第一行两个数n，m（1<=n<=1000，m<=10）

接下来每两行描述一件物品。对于每一件物品：

第一行两个数v和s，表示其价值和所含属性数量(v<=100000,s<=m)

第二行s个数，表示该物品拥有的属性编号(1<=编号<=m)

输出
物品价值总和的最大值。

样例输入
1
3 2
2 1
1
2 1
2
5 2
1 2
样例输出
5

*/

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

int main(){
    int T, N, M, s, t;
    scanf("%d", &T);
    while(T --){
        scanf("%d%d", &N, &M);
        vector<int> value(N + 1, 0), attrs(N + 1, 0);
        for(int i = 1;i <= N; ++ i){
            scanf("%d%d", &value[i], &s);
            for(int j = 0;j < s; ++ j){
                scanf("%d", &t);
                attrs[i] |= (1 << (t - 1));
            }
        }
        vector<vector<int>> dp(N + 1, vector<int>(1 << M, 1 << 31));  //dp[i][j]表示从前i个物品中取，属性奇0偶1组合数字为j的最大价值
        int res = 0;
        for(int i = 0;i <= N; ++ i) dp[i][0] = 0;
        for(int i = 1;i <= N; ++ i)
            for(int j = 0;j < (1 << M); ++ j){
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j ^ attrs[i]] + value[i]);
                if(j == ((1 << M) - 1)) res = max(res, dp[i][j]);
            }
        printf("%d\n", res);
    }
}
