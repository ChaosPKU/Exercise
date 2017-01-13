/*
We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.

However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.

Example:

n = 10, I pick 8.

First round:  You guess 5, I tell you that it's higher. You pay $5.
Second round: You guess 7, I tell you that it's higher. You pay $7.
Third round:  You guess 9, I tell you that it's lower. You pay $9.

Game over. 8 is the number I picked.

You end up paying $5 + $7 + $9 = $21.
Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.

Hint:

The best strategy to play the game is to minimize the maximum loss you could possibly face. Another strategy is to minimize the expected loss. Here, we are interested in the first scenario.
Take a small example (n = 3). What do you end up paying in the worst case?
Check out this article if you're still stuck.
The purely recursive implementation of minimax would be worthless for even a small n. You MUST use dynamic programming.
As a follow-up, how would you modify your code to solve the problem of minimizing the expected loss, instead of the worst-case loss?
*/

// O(n^3) time complexity
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        for(int len = 2; len <= n; ++ len){
            for(int i = 1;i + len - 1 <= n; ++ i){
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                for(int k = i;k <= j; ++ k)
                    dp[i][j] = min(max(dp[i][k - 1], dp[k + 1][j]) + k, dp[i][j]);
            }
        }
        return dp[1][n];
    }
};

// O(n^2) time complexity from http://artofproblemsolving.com/community/c296841h1273742
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n + 2, vector<int>(n + 2));  //因为要防止K-1和K+1越界，所以+2;
        for(int b = 2; b <= n; ++ b){
            int k0 = b - 1;
            deque<pair<int, int>> dqu;
            for(int a = b - 1; a ; -- a){
                if(dp[a][k0 - 1] > dp[k0 + 1][b]){
                    if(!dqu.empty() && dqu.front().second == k0) // 在单调队列里，不仅值是有序的，序号也是有序的，K0也是单调递减的，如果队列头不是K0，那么队列中肯定就没有了。
                        dqu.pop_front();
                    -- k0;
                }
                int num = a + dp[a + 1][b];
                while(!dqu.empty() && num < dqu.back().first) dqu.pop_back();
                dqu.emplace_back(num, a);
                int f1 = dp[a][k0] + k0 + 1, f2 = dqu.front().first;
                dp[a][b] = f1 < f2 ? f1 : f2;
            }
        }
        return dp[1][n];
    }
};
