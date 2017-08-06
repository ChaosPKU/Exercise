/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
Given an integer array A1, A2 ... AN, you are asked to split the array into three continuous parts: A1, A2 ... Ap | Ap+1, Ap+2, ... Aq | Aq+1, Aq+2, ... AN.

Let S1, S2 and S3 denote the sums of each part:  

S1 = A1 + A2 + ... + Ap  

S2 = Ap+1 + Ap+2 + ... + Aq

S3 = Aq+1 + Aq+2 + ... + AN

A partition is acceptable if and only if the differences between S1, S2 and S3 (i.e. |S1 - S2|, |S2 - S3|, |S3 - S1|) are no more than 1.  

Can you tell how many different partitions are acceptable?

输入
The first line contains an integer N.  

The second line contains N integers, A1, A2 ... AN.  

For 30% of the data, N ≤ 100  

For 70% of the data, N ≤ 1000  

For 100% of the data, N ≤ 100000, -1000000 ≤ Ai ≤ 1000000

输出
The number of acceptable partitions.

样例解释
The three acceptable partitions are:  

3 | 2 | 1 0 2  

3 | 2 1 | 0 2  

3 | 2 1 0 | 2

样例输入
5
3 2 1 0 2
样例输出
3
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

typedef long long LL;

int main(){
    LL N, res = 0;
    cin >> N;
    vector<LL> nums(N + 1), sum(N + 1, 0);
    for(LL i = 1;i <= N; ++ i){
        cin >> nums[i];
        sum[i] = sum[i - 1] + nums[i];
    }
    LL mean = sum[N] / 3 - (sum[N] < 0); // 小于0的时候mean需要减去一个1;
    unordered_map<LL, LL> udmp;
    udmp[sum[1]] ++;
    for(LL i = 2; i < N; ++ i){
        if(sum[i] == 2 * mean){
            if(sum[N] - sum[i] == mean || sum[N] - sum[i] == mean + 1)
                res += udmp[mean];
        }
        else if(sum[i] == 2 * mean + 1){
            if(sum[N] - sum[i] == mean || sum[N] - sum[i] == mean + 1)
                res += udmp[mean] + udmp[mean + 1];
        }
        else if(sum[i] == 2 * mean + 2){
            if(sum[N] - sum[i] == mean)
                res += udmp[mean + 1];
        }
        udmp[sum[i]] ++;
    }
    cout << res << endl;
    return 0;
}
