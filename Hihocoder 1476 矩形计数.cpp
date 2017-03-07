/*

在由N行M列个单位正方形组成的矩形中，有K个单位正方形是黑色的，其余单位正方形是白色的。  
你能统计出一共有多少个不同的子矩形是完全由白色单位正方形组成的吗？

输入
第一行三个整数:N, M和K。

之后K行每行包括两个整数R和C，代表一个黑色单位正方形的位置。

1 <= N，M <= 1000  

1 <= K <= 10  

1 <= R <= N  

1 <= C <= M

输出
输出一个整数表示满足条件的子矩形个数。

样例输入
3 3 1
2 3 
样例输出
24

*/

/*
每个矩形以右下角的点的坐标为代表
全白矩形中,以i,j为代表的子矩形共有i*j个
i,j位置处有一个黑点,影响到了以i,j为左上角的矩形内部所有代表点的计数,共(m-i+1)*(n-i+1),每个代表点减少计数i*j个
考虑同时包含多个黑点才计数的情况,需要考虑以max(i),max(j)为左上角的矩形内部所有代表点的计数,每个代表点减少计数min(i)*min(j)个,
基于以上原则考虑容斥原理
*/

#include <cstdio>
#include <iostream>
using namespace std;

#define     bits(x)     __builtin_popcount(x)
#define     LL          long long
int N, M, K;
int R[10], C[10];

int main() {
    int i, j;
    scanf("%d%d%d", &N, &M, &K);
    for(i = 0; i < K; ++ i)
        scanf("%d%d", &R[i], &C[i]);
    LL res = (LL)N * (N + 1) / 2 * M * (M + 1) / 2;
    for(i = 1;i < (1 << K); ++ i){
        int min_x = 1e6, max_x = 0, min_y = 1e6, max_y = 0;
        for(j = 0;j < K; ++ j){
            if(i & (1 << j)){
                min_x = min(min_x, R[j]);
                max_x = max(max_x, R[j]);
                min_y = min(min_y, C[j]);
                max_y = max(max_y, C[j]);
            }
        }
        if(bits(i) % 2) res -= (LL)min_x * min_y * (N - max_x + 1) * (M - max_y + 1);
        else res += (LL)min_x * min_y * (N - max_x + 1) * (M - max_y + 1);
    }
    printf("%lld\n", res);
    return 0;
}
