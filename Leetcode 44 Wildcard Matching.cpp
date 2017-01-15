/*
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/

// Greedy version
class Solution {
public:
    bool isMatch(string s,string p){
        int ssize = s.size();
        int psize = p.size();
        int match = 0, startID = -1;
        int i = 0,j = 0;
        while(i < ssize){
            if(j < psize && (p[j] == '?' || p[j] == s[i])){
                ++ i;
                ++ j;
            }
            else if(j < psize && p[j] == '*'){
                match = i;
                startID = j;
                ++ j;
            }
            else if(startID != -1){
                ++ match;
                j = startID + 1;
                i = match;
            }
            else{
                return false;
            }
        }
        while(j < psize && p[j] == '*')
            ++ j;
        return j == psize;
    }
};

// DP version
class Solution {
public:
    bool isMatch(string s,string p){
        int ssize = s.size();
        int psize = p.size();
        vector<vector<bool> > res(ssize + 1,vector<bool>(psize + 1,0));
        res[0][0] = 1;
        for(int i = 1;i <= psize; ++ i)
            res[0][i] = res[0][i - 1] && p[i - 1] == '*';
        for(int j = 1;j <= psize; ++ j){
            for(int i = 1;i <= ssize; ++ i){
                if(s[i - 1] == p[j - 1] || p[j - 1] == '?')
                    res[i][j] = res[i - 1][j - 1];
                else if(p[j - 1] == '*'){
                    res[i][j] = res[i - 1][j] || res[i][j - 1];
                }
            }
        }
        return res[ssize][psize];
    }
};
