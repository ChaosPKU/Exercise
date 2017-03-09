/*
 一幢 N 层的大楼，给你 M 个鸡蛋。如果在第 n 层扔下鸡蛋，鸡蛋不碎，那么从第 n-1 层扔鸡蛋，都不碎。这两只鸡蛋一模一样，不碎的话可以扔无数次。最高从哪层楼扔下时鸡蛋不会碎？
 提出一个策略, 保证能测出鸡蛋恰好会碎的楼层, 并使此策略在最坏情况下所扔次数最少。
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

//int main() {
//    int N, M;
//    scanf("%d%d", &N, &M);
//    vector<vector<int> > dp(N + 1, vector<int>(2, 0));
//    for(int i = 0;i <= N; ++ i) dp[i][1] = i;
//    for(int m = 2; m <= M; ++ m)
//        for(int n = 1;n <= N; ++ n){
//            dp[n][m & 1] = n;
//            for(int i = 1; i <= n; ++ i)
//                dp[n][m & 1] = min(dp[n][m & 1], 1 + max(dp[i - 1][(m - 1) & 1], dp[n - i][m & 1]));
//        }
//
//    cout << dp[N][M & 1] << endl;
//    return 0;
//}


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


// 注意到, 若构建一颗判定树, 其叶子节点个数共有 N + 1 个, 所以树的高度至少为 [log2(N + 1)] + 1, (这里先用N + 1表示向上取整), 此时比较次数为[log2(N + 1)]。如果 M >= [log2(N + 1)], 题目将退化成二分查找, 此时可以知道[log2(N + 1)]是下限并且是可以达到的下限, 可以直接输出 [log2(N + 1)]。所以对于M比较大的情况可以继续优化, 问题的复杂度不会超过 O(N * min(logN, M)) 。
