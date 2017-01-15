/*

Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true

*/

class Solution {
public:
    bool isMatch(string s, string p) {
        int slen = s.size(), plen = p.size();
        vector<vector<bool>> res(plen + 1, vector<bool>(slen + 1, 0));
        res[0][0] = true;
        for(int i = 1;i <= slen; ++ i)
            res[0][i] = false;
        for(int i = 2;i <= plen; i += 2)
            if(p[i - 1] == '*')
                res[i][0] = true;
            else
                break;
        for(int i = 1;i <= plen; ++ i)
            for(int j = 1;j <= slen; ++ j){
                if(p[i - 1] != '*')
                    res[i][j] = res[i - 1][j - 1] && (p[i - 1] == s[j - 1] || p[i - 1] == '.');
                else{
                    res[i][j] = res[i - 2][j] || (res[i][j - 1] && (p[i - 2] == s[j - 1] || p[i - 2] == '.'));
                }
            }
        return res[plen][slen];
    }
};
