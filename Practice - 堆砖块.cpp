/*
小易有n块砖块，每一块砖块有一个高度。小易希望利用这些砖块堆砌两座相同高度的塔。为了让问题简单，砖块堆砌就是简单的高度相加，某一块砖只能使用在一座塔中一次。小易现在让能够堆砌出来的两座塔的高度尽量高，小易能否完成呢。 
输入描述:
输入包括两行：
第一行为整数n(1 ≤ n ≤ 50)，即一共有n块砖块
第二行为n个整数，表示每一块砖块的高度height[i] (1 ≤ height[i] ≤ 500000)


输出描述:
如果小易能堆砌出两座高度相同的塔，输出最高能拼凑的高度，如果不能则输出-1.
保证答案不大于500000。

输入例子:
3
2 3 5

输出例子:
5
*/

#include <iostream>
#include <vector>
using namespace std;
const int maxN = 500010;
int main(){
    int n, i, j, p = 0, res = 0;
    cin >> n;
    vector<int> value(n);
    for(i = 0;i < n; ++ i) cin >> value[i];
    vector<vector<int>> dp(2, vector<int>(maxN, 0)); // dp[i][j]表示从前i个中选两组，两组差异为j的时候两组中较大者的最大值
    for(i = 0;i < n; ++ i){
        dp[p][value[i]] = max(dp[1 - p][value[i]], value[i]);
        for(j = 0;j <= maxN; ++ j)
            if(dp[1 - p][j]){
                dp[p][j] = max(dp[1 - p][j], dp[p][j]);  // 不选择j
                if(j + value[i] < maxN) dp[p][j + value[i]] = max(dp[p][j + value[i]], dp[1 - p][j] + value[i]);  // 选择j并放入较大组
                if(j >= value[i]) dp[p][j - value[i]] = max(dp[p][j - value[i]], dp[1 - p][j]);  // 选择j放入较小组且较小组未能超过较大组
                else dp[p][value[i] - j] = max(dp[p][value[i] - j], dp[1 - p][j] + value[i] - j);  // 选择j放入较大组且较小组成为新的较大组
            }
        
        p = 1 - p;  // 滚动数组优化空间
    }
    if(!(res = dp[1 - p][0])) res = -1;
    cout << res << endl;
    return 0;
}
