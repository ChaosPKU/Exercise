/*

时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Ho得到了一个数组作为他的新年礼物，他非常喜欢这个数组！

在仔细研究了几天之后，小Ho成功的将这个数组拆成了若干段，并且每段的和都不为0！

现在小Ho希望知道，这样的拆分方法一共有多少种？

两种拆分方法被视作不同，当且仅当数组断开的所有位置组成的集合不同。

输入
每组输入的第一行为一个正整数N，表示这个数组的长度

第二行为N个整数A1~AN，描述小Ho收到的这个数组

对于40%的数据，满足1<=N<=10

对于100%的数据，满足1<=N<=105, |Ai|<=100

输出
对于每组输入，输出一行Ans，表示拆分方案的数量除以(109+7)的余数。

样例输入
5
1 -1 0 2 -2
样例输出
5

*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <bitset>
using namespace std;

const int mod = pow(10, 9) + 7;
int main() {
    int N;
    while(cin >> N){
        vector<int> vtr(N, 0);
        for(int i = 0;i < N; ++ i)
            cin >> vtr[i];
        unordered_map<int, int> udmp;
        vector<int> dp(N + 1, 0);
        vector<int> sum(N + 1, 0);
        int S = 0;
        
        for(int i = 1;i <= N; ++ i)
            sum[i] = sum[i - 1] + vtr[i - 1];

        for(int i = 1;i <= N; ++ i){
            dp[i] += (S - udmp[sum[i]] + mod) % mod;
            if(sum[i] != 0) dp[i] += 1;
            dp[i] %= mod;
            S = (S + dp[i]) % mod;
            udmp[sum[i]] = (udmp[sum[i]] + dp[i]) % mod;
        }
        cout << dp[N]<< endl;
    }
    return 0;
}
