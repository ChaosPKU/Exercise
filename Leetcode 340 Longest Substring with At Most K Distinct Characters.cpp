/*
Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = “eceba” and k = 2,

T is "ece" which its length is 3.
*/

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int i = 0,j = 0, maxLen = 0, n = s.size(), length = 0;
        if(n <= k) return n;
        int mp[256] = {0};
        while(j < n){
            if(mp[s[j++]] ++ == 0) ++ length;
            if(length <= k)
                maxLen ++;
            else if(-- mp[s[i ++]] == 0) 
                length --;
        }
        return maxLen;
    }
};
