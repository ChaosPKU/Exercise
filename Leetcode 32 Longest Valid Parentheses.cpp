/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/


class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> dp(s.size() + 1, 0);
        int m = 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') dp[i + 1] = dp[i - 1] + 2;
                if (s[i - 1] == ')' && i - dp[i] > 0 && s[i - dp[i] - 1] == '(') dp[i + 1] = dp[i] + 2 + dp[i - dp[i] - 1];
            }
            if (m < dp[i + 1]) m = dp[i + 1];
        }
        return m;
    }
};
