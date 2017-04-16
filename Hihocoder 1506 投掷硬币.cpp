/*
描述
小Hi有一枚神奇的硬币。已知第i次投掷这枚硬币时，正面向上的概率是Pi。  

现在小Hi想知道如果总共投掷N次，其中恰好M次正面向上的概率是多少。

输入
第一行包含两个整数N和M。

第二行包含N个实数P1, P2, ... PN。  

对于30%的数据，1 <= N <= 20  

对于100%的数据，1 <= N <= 1000, 0 <= M <= N, 0 <= Pi <= 1

输出
输出一行一个实数表示恰好M次正面向上的概率。注意行末需要包含一个换行符'\n'。  

输出与标准答案误差在0.001以内都被视为正确。

样例输入
2 1
0.5 0.5
样例输出
0.500000
*/

#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    vector<double> dp(m + 1, 0), p(n + 1, 0);
    for(int i = 1;i <= n; ++ i)
        cin >> p[i];
    dp[0] = 1 - p[1];
    dp[1] = p[1];
    for(int i = 2;i <= n; ++ i)
        for(int j = min(i, m);j >= 0; -- j)
            dp[j] = dp[j] * (1 - p[i]) + dp[j - 1] * p[i];
    cout << dp[m] << endl;
    return 0;
}
