/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/

class Solution {
public:
    int minCut(string s) {
        int len = (int)s.size();
        vector<vector<bool>> mat(len, vector<bool>(len, 0));
        vector<int> res(len,len);
        res[0] = 0;
        for(int i = 0;i < len; ++ i)
            mat[i][i] = true;
        for(int i = 0;i < len - 1; ++ i)
            mat[i][i + 1] = (s[i] == s[i + 1]);
        for(int k = 3;k <= len; ++ k){
            for(int i = 0;i + k - 1 < len; ++ i){
                int j = i + k - 1;
                mat[i][j] = (mat[i+1][j-1] && s[i] == s[j]);
            }
        }
        for(int i = 1;i < len; ++ i){
            if(mat[0][i]){
                res[i] = 0;
                continue;
            }
            for(int j = 0;j < i; ++ j){
                if(mat[j + 1][i])
                    res[i] = min(res[i], res[j] + 1);
            }
        }
        return res[len - 1];
    }
};
