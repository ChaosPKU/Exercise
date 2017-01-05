/*
Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3.
*/
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int maxLen = 2, i = 0, j = 1, n = s.size(), length = 0;
        if(n <= 2) return n;
        int mp[256] = {0};
        mp[s[0]] ++;
        mp[s[1]] ++;
        length = 1 + (s[0] != s[1]);
        while(++ j < n){
            if(mp[s[j]] ++ == 0) length ++;
            if(length > 2){
                if(-- mp[s[i]] == 0) length --;
                ++ i;
            }
            else maxLen ++;
        }
        return maxLen;
    }
};
