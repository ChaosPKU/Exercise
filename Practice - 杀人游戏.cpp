/*
大意是，有n个人，每次从奇数位的人中抽一个杀掉，杀掉的人后面的人把空位补上，直到杀至最后一人，问原来的n个人里面每个位置的人活到最后的概率有多大？
*/
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main(){
    int N, n, m, a, b;
    int maxN = 10000;
    double p1, p2;
    vector<vector<double>> dp(maxN + 1, vector<double>(maxN + 1, 0)); // dp[i][j] 表示从i个人开始杀，直至杀至最后一人时，初始编号为j的人活下来的概率;
//    dp[2][1] = 0;  // 不管有几个人，1号都是必死无疑。
    dp[2][2] = 1;
    for(int i = 3;i <= maxN; ++ i)
        for(int j = 2; j <= i; ++ j){
            a = j / 2;
            b = (i + 1) / 2;
            p1 = (double)a / b;  // j之前的人被杀的概率(不包括j)
            p2 = (j & 1) ? (1 - (double)(a + 1) / b) : (1 - p1);  // j之后的人被杀的概率(不包括j)
            dp[i][j] = p1 * dp[i - 1][j - 1] + p2 * dp[i - 1][j];
        }
    cin >> N;
    while(N -- ){
        cin >> n >> m;
        cout << setiosflags(ios::fixed) << setprecision(8) << dp[n][m] << endl;
    }
    return 0;
}


// https://www.zhihu.com/question/55445739
// 这道题可以求出通项公式 P(n, i) = [i / 2] / ([n / 2] * [(n + 1) / 2])  可以根据上述DP推导过程用归纳法求得正确性，所以用通项公式来求代码复杂度就变成O(1)了([]表示下取整)

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main(){
    int N, n, m;
    cin >> N;
    while(N -- ){
        cin >> n >> m;
//         cout << setiosflags(ios::fixed) << setprecision(8) << (m / 2) / (double)((n / 2) * ((n + 1) / 2)) << endl;
        cout << setiosflags(ios::fixed) << setprecision(8) << (double)(m / 2) / (n * n / 4) << endl;
    }
    return 0;
}


// 如果题目改成求所有人存活的期望轮数
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main(){
    int N, n, m, a, b;
    int maxN = 10000;
    double p1, p2;
    vector<vector<double>> dp(maxN + 1, vector<double>(maxN + 1, 0)); // dp[i][j] 表示从i个人开始杀，直至杀至最后一人时，初始编号为j的人活下来的概率;
//    dp[2][1] = 0;   // 不多于两个人时，1号都是第一轮必死。
    dp[2][2] = 1;
    
    for(int i = 3; i <= maxN; ++ i)
        dp[i][1] = (1 - (1.0 / ((i + 1) / 2))) * (1 + dp[i - 1][1]);   // 多于两个人时，1号有不遭遇一轮游的希望
    
    for(int i = 3;i <= maxN; ++ i)
        for(int j = 2; j <= i; ++ j){
            a = j / 2;
            b = (i + 1) / 2;
            p1 = (double)a / b;  // j之前的人被杀的概率(不包括j)
            p2 = (j & 1) ? (1 - (double)(a + 1) / b) : (1 - p1);  // j之后的人被杀的概率(不包括j)
            dp[i][j] = p1 * (dp[i - 1][j - 1] + 1) + p2 * (dp[i - 1][j] + 1);
        }
    cin >> N;
    while(N -- ){
        cin >> n >> m;
        cout << setiosflags(ios::fixed) << setprecision(8) << dp[n][m] << endl;
    }
    return 0;
}
