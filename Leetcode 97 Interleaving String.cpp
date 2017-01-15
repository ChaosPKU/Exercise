/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s3.size() != s1.size() + s2.size())
            return false;
        vector<vector<bool>> res(s1.size() + 1, vector<bool>(s2.size() + 1, 0));
        res[0][0] = 1;
        for(int i = 1;i <= s1.size(); ++ i){
            if(s1[i - 1] == s3[i - 1])
                res[i][0] = 1;
            else
                break;
        }
        for(int i = 1;i <= s2.size(); ++ i){
            if(s2[i - 1] == s3[i - 1])
                res[0][i] = 1;
            else
                break;
        }
        for(int i = 1; i <= s1.size(); ++ i)
            for(int j = 1;j <= s2.size(); ++ j){
                res[i][j] = (res[i - 1][j] && (s1[i - 1] == s3[i + j - 1])) || (res[i][j - 1] && (s2[j - 1] == s3[i + j - 1]));
            }
        return res[s1.size()][s2.size()];
    }
};
