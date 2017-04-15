/*
 Problem Description
 Zero has an old printer that doesn't work well sometimes. As it is antique, he still like to use it to print articles. But it is too old to work for a long time and it will certainly wear and tear, so Zero use a cost to evaluate this degree.
 One day Zero want to print an article which has N words, and each word i has a cost Ci to be printed. Also, Zero know that print k words in one line will cost
 
 M is a const number.
 Now Zero want to know the minimum cost in order to arrange the article perfectly.
 
 
 Input
 There are many test cases. For each test case, There are two numbers N and M in the first line (0 ≤ n ≤ 500000, 0 ≤ M ≤ 1000). Then, there are N numbers in the next 2 to N + 1 lines. Input are terminated by EOF.
 
 
 Output
 A single number, meaning the mininum cost to print the article.
 
 
 Sample Input
 5 5
 5
 9
 5
 7
 5
 
 
 Sample Output
 230
 
 
 Author
 Xnozero
 
 
 Source
 2010 ACM-ICPC Multi-University Training Contest（7）——Host by HIT
 */
/*
 来源于 http://blog.csdn.net/xingyeyongheng/article/details/25912663
 假设sum[i]表示前i项和
 dp[i]表示前i项需要花费的最少值
 则dp[i]=min((sum[i]-sum[j])^2+m+dp[j]);//j=0~i-1
 =>dp[i]=min(sum[i]*sum[i]+2*sum[i]*sum[j]+sum[j]*sum[j]+m+dp[j]);
 由于存在sum[i]*sum[j]和i有关的这一项,所以不可能用单调队列来维护
 2*sum[i]*sum[j]+sum[j]*sum[j]+m+dp[j]的最小值
 这个时候怎么办?根据题意我们是要寻找到最优的j
 所以假设k<j<i
 有2*sum[i]*sum[j]+sum[j]*sum[j]+m+dp[j]<2*sum[i]*sum[k]+sum[k]*sum[k]+m+dp[k]
 =>(sum[j]*sum[j]+dp[j]-(sum[k]*sum[k]+dp[k]))/(2*sum[j]-2*sum[k])<sum[i];
 令
 yj=sum[j]*sum[j]+dp[j]
 yk=sum[k]*sum[k]+dp[k]
 xj=2*sum[j];
 xk=2*sum[k]
 所以=>(yj-yk)/(xj-xk)<sum[i]则表示j比k更优
 是连接点j和点k的直线的斜率
 相对于点i最优的是j,
 则在0~j相对于i+1,i+2...n点j肯定是最优的,因为满足sum[i+x]>sum[i]>yj-yk)/(xj-xk)
 则只需要继续判断j+1~i+x之间是否有点更优,有的话j就不用保存了，这个过程用单调队列实行
 而对于点i应该添加到队列中
 比较i与点q[tail-1],q[tail-1]与点q[tail-2]的斜率k1,k2,
 若k1<=k2则将点q[tail-1]去除,因为后面肯定是先k1<sum[i+x]
 也就是点i肯定比q[tail-1]更优
 然后重复比较直到k1>k2
 */

#include <iostream>
#include <deque>
#include <vector>
using namespace std;
int compare1(const vector<int> &dp, const vector<int> &sum, const int &i, const int &j, const int k){
    return (dp[j] + sum[j] * sum[j] - dp[i] - sum[i] * sum[i]) <= (sum[j] - sum[i]) * k;
}
int compare2(const vector<int> &dp, const vector<int> &sum, const int &i, const int &j, const int &k){
    int yi = dp[i] + sum[i] * sum[i], yj = dp[j] + sum[j] * sum[j], yk = dp[k] + sum[k] * sum[k];
    int xi = sum[i], xj = sum[j], xk = sum[k];
    return (yk - yj) * (xj - xi) <= (yj - yi) * (xk - xj);
}

int main(){
    int n, m, t;
    while(cin >> n >> m){
        deque<int> dqu;
        vector<int> dp(n + 1, 0), sum(n + 1, 0);
        dqu.push_back(0);
        for(int i = 1;i <= n; ++ i){
            cin >> sum[i];
            sum[i] += sum[i - 1];
            while(dqu.size() > 1 && compare1(dp, sum, dqu.front(), *(dqu.begin() + 1), 2 * sum[i]))
                dqu.pop_front();
            t = dqu.front();
            dp[i] = dp[t] + sum[t] * sum[t] + sum[i] * sum[i] + m - 2 * sum[t] * sum[i];
            while(dqu.size() > 1 && compare2(dp, sum, *(dqu.end() - 2), dqu.back(), i))
                dqu.pop_back();
            dqu.push_back(i);
        }
        cout << dp[n] << endl;
    }
    return 0;
}
