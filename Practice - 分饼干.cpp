/*
2017网易笔试
易老师购买了一盒饼干，盒子中一共有k块饼干，但是数字k有些数位变得模糊了，看不清楚数字具体是多少了。易老师需要你帮忙把这k块饼干平分给n个小朋友，易老师保证这盒饼干能平分给n个小朋友。现在你需要计算出k有多少种可能的数值 
输入描述:
输入包括两行：

第一行为盒子上的数值k，模糊的数位用X表示，长度小于18(可能有多个模糊的数位)

第二行为小朋友的人数n


输出描述:
输出k可能的数值种数，保证至少为1

输入例子:
9999999999999X
3

输出例子:
4
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    int i, j, k, mod, tot = 0, tmp;
    string str;
    cin >> str >> mod;
    int n = (int)str.size();
    vector<int> value;
    for(i = n - 1, k = 1;i >= 0; -- i, k *= 10){
        k %= mod;
        if(str[i] == 'X') value.push_back(k);
        else tot = (tot + (str[i] - '0') * k) % mod;
    }
    
    n = (int)value.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(mod, 0));
    for(i = 0;i < 10; ++ i) dp[0][(i * value[0]) % mod] += 1;
    for(i = 0;i < n - 1; ++ i){
        tmp = i == n - 2 && str[0] == 'X';
        for(j = 0;j < mod; ++ j)
            for(k = tmp;k < 10; ++ k)
                dp[i + 1][(j + k * value[i + 1]) % mod] += dp[i][j];
    }
    
    cout << dp[n - 1][(mod - tot) % mod] << endl;
    return 0;
}
