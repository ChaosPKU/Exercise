/*
描述
给定N个数A1, A2, A3, ... AN，小Ho想从中找到两个数Ai和Aj(i ≠ j)使得乘积Ai × Aj × (Ai AND Aj)最大。其中AND是按位与操作。  

小Ho当然知道怎么做。现在他想把这个问题交给你。

输入
第一行一个数T，表示数据组数。(1 <= T <= 10)  

对于每一组数据：

第一行一个整数N（1<=N<=100,000）

第二行N个整数A1, A2, A3, ... AN (0 <= Ai <220)

输出
一个数表示答案

样例输入
2
3
1 2 3
4
1 2 4 5
样例输出
12
80
*/

// 问题的关键在于如何把O(n^2)的复杂度降低到O(nlogn)级别。



// 一种思路可以先把所有a&b可能的结果枚举出来，则对相同的a&b，a*b*a&b最大的就是a&b再乘以最大的a和b。但复杂度很高。
#include <iostream>
#include <memory.h>
using namespace std;

int num[1 << 20][2];

int main(){
    int T, N, A, K;
    long long R;
    scanf("%d", &T);
    while(T --){
        scanf("%d", &N);
        memset(num, 0, sizeof(num));
        R = 0;
        while(N --){
            scanf("%d", &A);
            for(K = A; K > 0; K = A & (K - 1))
                if(A >= num[K][0]){
                    num[K][1] = num[K][0];
                    num[K][0] = A;
                }
                else if(A > num[K][1])
                    num[K][1] = A;
        }
        for(long long k = 1; k < 1 << 20; ++ k)
            R = max(R, (long long)k * num[k][0] * num[k][1]);
        printf("%lld\n", R);
    }
    return 0;
}

