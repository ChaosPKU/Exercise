/*
Given a non-empty string, encode the string such that its encoded length is the shortest.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

Note:
k will be a positive integer and encoded string will not be empty or have extra space.
You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.
Example 1:

Input: "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.
Example 2:

Input: "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
Example 3:

Input: "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".
Example 4:

Input: "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
Example 5:

Input: "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
*/

class Solution {
public:
    string helper(vector<vector<string>> &dp, string &s, int &i, int &j){
        string tmp = s.substr(i, j - i + 1);
        int pos = (tmp + tmp).find(tmp, 1);
        if(pos >= tmp.size()) return tmp;
        return to_string(tmp.size() / pos) + "[" + dp[i][i + pos - 1] + "]";
    }
    string encode(string s) {
        int n = s.size();
        vector<vector<string>> dp(n, vector<string>(n, ""));
        for(int step = 1;step <= n; ++ step){
            for(int i = 0;i + step - 1 < n; ++ i){
                int j = i + step - 1;
                dp[i][j] = s.substr(i, step);
                for(int k = i; k < j; ++ k){
                    if(dp[i][k].size() + dp[k + 1][j].size() < dp[i][j].size())
                        dp[i][j] = dp[i][k] + dp[k + 1][j];
                }
                string str = helper(dp, s, i, j);
                if(str.size() < dp[i][j].size()) dp[i][j] = str;
            }
        }
        return dp[0][n - 1];
    }
};
