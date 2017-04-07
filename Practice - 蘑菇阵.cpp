/*
题目描述
现在有两个好友A和B，住在一片长有蘑菇的由n＊m个方格组成的草地，A在(1,1),B在(n,m)。现在A想要拜访B，由于她只想去B的家，所以每次她只会走(i,j+1)或(i+1,j)这样的路线，在草地上有k个蘑菇种在格子里(多个蘑菇可能在同一方格),问：A如果每一步随机选择的话(若她在边界上，则只有一种选择)，那么她不碰到蘑菇走到B的家的概率是多少？

输入描述:
第一行N，M，K(1 ≤ N,M ≤ 20, k ≤ 100),N,M为草地大小，接下来K行，每行两个整数x，y，代表(x,y)处有一个蘑菇。


输出描述:
输出一行，代表所求概率(保留到2位小数)

输入例子:
2 2 1
2 1

输出例子:
0.50
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main(){
    int n, m, k, x, y;
    while(cin >> n >> m >> k){
        vector<vector<bool> > grid(n + 1, vector<bool>(m + 1, 0));
        vector<vector<double> > dp(n + 1, vector<double>(m + 1, 0));
        for(int i = 0; i < k; ++ i){
            cin >> x >> y;
            grid[x][y] = 1;
        }
        if(grid[1][1] || grid[n][m]){
            cout << "0.00" << endl;
            return 0;
        }
        dp[1][1] = 1.;
        for(int i = 2;i <= m; ++ i)
            if(grid[1][i]) break;
            else dp[1][i] = 0.5 * dp[1][i - 1];
        for(int i = 2;i <= n; ++ i)
            if(grid[i][1]) break;
            else dp[i][1] = 0.5 * dp[i - 1][1];

        for(int i = 2;i < n; ++ i)
            for(int j = 2; j < m; ++ j)
                dp[i][j] = grid[i][j] ? 0 : dp[i - 1][j] * 0.5 + dp[i][j - 1] * 0.5;

        for(int i = 2;i < m; ++ i)
            dp[n][i] = grid[n][i] ? 0 : dp[n][i - 1] + dp[n - 1][i] * 0.5;
        for(int i = 2;i < n; ++ i)
            dp[i][m] = grid[i][m] ? 0 : dp[i - 1][m] + dp[i][m - 1] * 0.5;

        cout << setprecision(2) << setiosflags(ios::fixed) << dp[n - 1][m] + dp[n][m - 1] << endl;
    }
    return 0;
}
