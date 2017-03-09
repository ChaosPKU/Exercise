/*
 一幢 N 层的大楼，给你 M 个鸡蛋。如果在第 n 层扔下鸡蛋，鸡蛋不碎，那么从第 n-1 层扔鸡蛋，都不碎。这两只鸡蛋一模一样，不碎的话可以扔无数次。最高从哪层楼扔下时鸡蛋不会碎？
 提出一个策略, 保证能测出鸡蛋恰好会碎的楼层, 并使此策略在最坏情况下所扔次数最少。
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
using namespace std;

// Time: O(MN^2), Space: O(N);
int main() {
   int N, M;
   scanf("%d%d", &N, &M);
   vector<vector<int> > dp(N + 1, vector<int>(2, 0));
   for(int i = 0;i <= N; ++ i) dp[i][1] = i;
   for(int m = 2; m <= M; ++ m)
       for(int n = 1;n <= N; ++ n){
           dp[n][m & 1] = n;
           for(int i = 1; i <= n; ++ i)
               dp[n][m & 1] = min(dp[n][m & 1], 1 + max(dp[i - 1][(m - 1) & 1], dp[n - i][m & 1]));
       }

   cout << dp[N][M & 1] << endl;
   return 0;
}


// Time: O(MN), Space: O(N);
// DP(0, m) = 0, (m >= 1)
// DP(n, 1) = n, (n >= 1) (保证能测出鸡蛋恰好会碎的楼层)
// DP(n, m) = min(i<-[1, n]){max{DP(i - 1, m - 1)(碎), DP(n - i, m)(不碎)} + 1};
// 随着i的增大,碎子树高度不减,不碎子树高度不增,可以证得 DP(n, m) >= DP(n - 1, m), 所以可以优化时间复杂度

int main(){
    int N, M;
    scanf("%d%d", &N, &M);
    int i, m, n, tmp;
    vector<vector<int> > dp(N + 1, vector<int>(2, 0));
    for(i = 0;i <= N; ++ i) dp[i][1] = i;
    for(m = 2; m <= M; ++ m){
        i = 1;
        for(n = 1;n <= N; ++ n){
            dp[n][m & 1] = 1 + max(dp[i - 1][(m - 1) & 1], dp[n - i][m & 1]);
            while(i < n && dp[n][m & 1] > (tmp = 1 + max(dp[i][(m - 1) & 1], dp[n - i - 1][m & 1]))){
                dp[n][m & 1] = tmp;
                ++ i;
            }
        }
    }
    cout << dp[N][M & 1] << endl;
    return 0;
}

// 注意到 DP(n, m) <= max{DP(i - 1, m - 1)(碎), DP(n - i, m)(不碎)} + 1, 对于i<-[1, n]
// 令 i = 1, 可得DP(n, m) <= DP(n - 1, m) + 1; 所以最内层循环中的while可以改为if(i只有一次变大的机会)。


// 注意到, 若构建一颗判定树, 其叶子节点个数共有 N + 1 个, 所以树的高度至少为 [log2(N + 1)] + 1, (这里先用[]表示向上取整), 此时比较次数为[log2(N + 1)]。
// 如果 M >= [log2(N + 1)], 题目将退化成二分查找, 此时可以知道[log2(N + 1)]是下限并且是可以达到的下限, 可以直接输出 [log2(N + 1)]。所以对于M比较大的情况可以继续优化, 问题的复杂度不会超过 O(N * min(logN, M)) 。

// 换一种思路，另g(u, v)表示用v个鸡蛋做u次实验，所能确定的楼的最高高度(楼最高表示最好情况鸡蛋都不碎，但受限于次数和鸡蛋数，以及仍需确保在鸡蛋碎的情况下能够完成对所有当前楼层以下的所有楼层完成检验)。
// 显然，g(u, v) = g(u - 1, v - 1) + 1 + g(u - 1, v)，且g(1, v) = 1, g(u, 1) = u;
// 算法目标即为找到满足条件的u使得g(u - 1, v) < N <= g(u, v);
// 算法的空间复杂度显然是O(M),时间复杂度则是uv的取值规模。注意到g(u, v)是一个严格不小于C(u, v)，即组合数的数字, 可以证明max(u)是和N开M次方同阶的。

int main(){
    int N, M;
    scanf("%d%d", &N, &M);
    int logN = floor(log(N + 0.0) / log(2.0)) + 1;
    if(M >= logN) {
        cout << logN << endl;
        return 0;
    }
    vector<int> dp(M + 1, 0);
    for(int i = 1;i <= M; ++ i) dp[i] = 1;
    for(int i = 2;i <= N; ++ i){
        dp[M] += dp[M - 1] + 1;
        if(dp[M] >= N) {
            cout << i << endl;
            return 0;
        }
        for(int j = M - 1; j >= 1; -- j)
            dp[j] += dp[j - 1] + 1;
    }
}
