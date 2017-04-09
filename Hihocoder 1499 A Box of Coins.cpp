/*
描述
Little Hi has a box which consists of 2xN cells as illustrated below.

+----+----+----+----+----+----+
| A1 | A2 | A3 | A4 | .. | AN |
+----+----+----+----+----+----+
| B1 | B2 | B3 | B4 | .. | BN |
+----+----+----+----+----+----+
There are some coins in each cell. For the first row the amounts of coins are A1, A2, ... AN and for the second row the amounts are B1, B2, ... BN.

Each second Little Hi can pick one coin from a cell and put it into an adjacent cell. (Two cells are adjacent if they share a common side. For example, A1 and A2 are adjacent; A1 and B1 are adjacent; A1 and B2 are not adjacent.)

Now Little Hi wants that each cell has equal number of coins by moving the coins. He wants to know the minimum number of seconds he needs to accomplish it.  

输入
The first line contains an integer, N. 2 <= N <= 100000  

Then follows N lines. Each line contains 2 integers Ai and Bi. (0 <= Ai, Bi <= 2000000000)  

It is guaranteed that the total amount of coins in the box is no more than 2000000000 and is a multiple of 2N.

输出
The minimum number of seconds.

样例输入
2
3 4
6 7
样例输出
4
*/

// 贪心，从第一列往后每次考虑一列情况，若两列内部不平衡，先内部平衡一下；若两列都不小于平均数，则把多余的移向后一列；若两列都不大于平均数，则都从后一列借至平均数，后一列被借成负数也没有关系，不影响最终分配策略；
// 牢记 long long 大法

#include <iostream>
#include <vector>
using namespace std;
int N, nxt = 0;
long long res = 0, num = 0;

void solve(vector<vector<long long>> &vtr, int i){
    if(i >= N) return;
    long long x = vtr[i][0] - num, y = vtr[i][1] - num, p, t;
    if(x * y < 0){
        p = x < 0;
        t = p ? min(-x, y) : min(x, -y);
        vtr[i][p] -= t;
        vtr[i][1 - p] += t;
        res += t;
        x = vtr[i][0] - num;
        y = vtr[i][1] - num;
    }
    if(x || y){
        if(x >= 0 && y >= 0) res += x + y;
        else res += - x - y;
        vtr[i + 1][0] += x;
        vtr[i + 1][1] += y;
    }
    solve(vtr, i + 1);
    return;
}

int main(){
    int i;
    scanf("%d", &N);
    vector<vector<long long>> vtr(N, vector<long long>(2, 0));
    for(i = 0;i < N; ++ i){
        scanf("%lld%lld", &vtr[i][0], &vtr[i][1]);
        num = num + vtr[i][0] + vtr[i][1];
    }
    num /= 2 * N;
    if(num) solve(vtr, 0);
    printf("%lld\n", res);
    return 0;
}
