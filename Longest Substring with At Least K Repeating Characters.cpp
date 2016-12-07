/*
Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
*/
class Solution {
public:
    int helper(const string &s, int b, int e, int k){
        if(e - b < k) return 0;
        int cnt[26]{};
        for(int i = b;i < e; ++ i) ++ cnt[s[i] - 'a'];
        int res = 0, l = b;
        bool flag = true;
        for(int i = b;i < e;++ i)
            if(cnt[s[i] - 'a'] < k){
                flag = false;
                res = max(res, helper(s, l, i, k));
                l = i + 1;
            }
        if(flag) return e - b;
        else return max(res, helper(s, l, e, k));
    }
    int longestSubstring(string s, int k) {
        return helper(s, 0, s.size(), k);
    }
};
