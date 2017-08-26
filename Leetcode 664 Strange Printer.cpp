/*
There is a strange printer with the following two special requirements:

The printer can only print a sequence of the same character each time.
At each turn, the printer can print new characters starting from and ending at any places, and will cover the original existing characters.
Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.

Example 1:
Input: "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".
Example 2:
Input: "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.
Hint: Length of the given string will not exceed 100.
*/
class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        if(n == 0) return 0;
        vector<vector<int> > dp(n + 1, vector<int>(n + 1, 0));
        for(int i = 1; i <= n; ++ i)
            dp[i][i] = 1;
        
        for(int d = 1;d < n; ++ d){
            for(int i = 1; i + d <= n; ++ i){
                int j = i + d;
                dp[i][j] = dp[i][j - 1] + 1;
                for(int k = i; k < j; ++ k){
                    if(s[k - 1] == s[j - 1])
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j - 1]);
                } 
            }
        }
        return dp[1][n];
    }
};
