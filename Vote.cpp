/*
 Problem
 
 A and B are the only two candidates competing in a certain election. We know from polls that exactly N voters support A, and exactly M voters support B. We also know that N is greater than M, so A will win.
 
 Voters will show up at the polling place one at a time, in an order chosen uniformly at random from all possible (N + M)! orders. After each voter casts their vote, the polling place worker will update the results and note which candidate (if any) is winning so far. (If the votes are tied, neither candidate is considered to be winning.)
 
 What is the probability that A stays in the lead the entire time -- that is, that A will always be winning after every vote?
 
 Input
 
 The input starts with one line containing one integer T, which is the number of test cases. Each test case consists of one line with two integers N and M: the numbers of voters supporting A and B, respectively.
 
 Output
 
 For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the probability that A will always be winning after every vote.
 
 y will be considered correct if y is within an absolute or relative error of 10-6 of the correct answer. See the FAQ for an explanation of what that means, and what formats of real numbers we accept.
 
 Limits
 
 1 ≤ T ≤ 100.
 Small dataset
 
 0 ≤ M < N ≤ 10.
 Large dataset
 
 0 ≤ M < N ≤ 2000.
 */
// 令P(i, j)表示概率，N(i, j)表示方法数。显然，i<=j时，P(i, j)=0, i>0,j=0时，P(i, j)=1。N(i, j) = N(i - 1, j) + N(i, j - 1)。P(i, j) = N(i , j) / ((i+j)! / i!j!)。由此，可得P的递推式。
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
const int L = 2001;
double dp[L][L];
int main(){
    memset(dp, 0, sizeof(dp));
    for(int i = 1;i < L; ++ i)
        dp[i][0] = 1;
    for(int j = 1;j < L; ++ j)
        for(int i = j + 1; i < L; ++ i){
            double p = (double)i / (i + j);
            dp[i][j] = dp[i - 1][j] * p + dp[i][j - 1] * (1 - p);
        }
    int T, M, N;
    scanf("%d", &T);
    for(int k = 1;k <= T; ++ k){
        scanf("%d%d", &M, &N);
        printf("Case #%d: %.8lf\n", k, dp[M][N]);
    }
    return 0;
}

