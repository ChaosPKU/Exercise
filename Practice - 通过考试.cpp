/*
题目描述		
小明同学要参加一场考试，考试一共有n道题目，小明必须做对至少60%的题目才能通过考试。考试结束后，小明估算出每题做对的概率，p1,p2,...,pn。你能帮他算出他通过考试的概率吗？

输入
输入第一行一个数n（1<=n<=100），表示题目的个数。第二行n个整数，p1,p2,...,pn。表示小明有pi%的概率做对第i题。（0<=pi<=100）
样例输入
4
50 50 50 50
输出
小明通过考试的概率，最后结果四舍五入，保留小数点后五位。
样例输出
0.31250
时间限制
C/C++语言：1000MS其它语言：3000MS	
内存限制
C/C++语言：65536KB其它语言：589824KB
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;
int main(){
    int n, i, j, t;
    cin >> n;
    vector<int> p(n + 1);
    for(i = 1;i <= n; ++ i) cin >> p[i];
    double P, res = 0;
    vector<vector<double>> dp(2, vector<double>(n + 1, 0));
    
    dp[0][0] = 1;
    t = 1;
    for(i = 1; i <= n; ++ i){
        P = p[i] / 100.;
        dp[t][0] = dp[1 - t][0] * (1 - P);
        for(j = 0; j <= i; ++ j){
            dp[t][j] = dp[1 - t][j] * (1 - P) + dp[1 - t][j - 1] * P;
        }
        t = 1 - t;
    }
    
    for(i = ceil(0.6 * n); i <= n; ++ i)
        res += dp[1 - t][i];
    cout << setiosflags(ios::fixed) << setprecision(5) << res << endl;
    
    return 0;
}
