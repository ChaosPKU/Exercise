/*
 #1482 : 出勤记录II
 时间限制:10000ms
 单点时限:1000ms
 内存限制:256MB
 描述
 小Hi的算法课老师每次上课都会统计小Hi的出勤记录。迟到会被记录一个L，缺席会被记录一个A，按时上课会被记录一个O。
 
 一学期结束，小Hi的出勤记录可以看成是一个只包含LAO的字符串，例如"OOOOLOOOLALLO……"。
 
 如果小Hi整学期缺席不超过1次，并且没有连续3次迟到，小Hi的出勤记录就算合格。
 
 现在给出字符串的长度N，小Hi想知道长度为N的出勤记录中，合格的记录总共有多少种。
 
 例如长度为3的合格出勤记录有19种：OOO OOL OOA OLO OAO LOO AOO OLL OLA OAL LOL LOA AOL LLO LAO ALO LLA LAL ALL。
 
 输入
 一个整数N(1 <= N <= 100000)。
 
 输出
 长度为N的合格记录总数。由于结果可能很大，你只需输出结果模109+7的余数。
 
 样例输入
 3
 样例输出
 19
 */
//dp[i][0]表示长度为i的字符串中没有A的个数, dp[i][1]表示长度为i的字符串中存在一个i的A的个数


#include <stdio.h>
const int mod = 1e9 + 7;
int dp[100005][2];
int main(){
    int T;
    scanf("%d", &T);
    dp[1][0] = 2; dp[1][1] = 1;
    dp[2][0] = 4; dp[2][1] = 4;
    dp[3][0] = 7; dp[3][1] = 12;
    for(int i = 4;i <= 100000; ++ i){
        dp[i][0] = ((dp[i - 1][0] + dp[i - 2][0]) % mod + dp[i - 3][0]) % mod;
        dp[i][1] = ((dp[i][0] + dp[i - 1][1]) % mod + (dp[i - 2][1] + dp[i - 3][1]) % mod) % mod;
    }
    int res = (dp[T][0] + dp[T][1]) % mod;
    printf("%d\n", res);
    return 0;
}
