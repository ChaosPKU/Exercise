/*
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.
Example:

Input: "cbbd"

Output: "bb"
*/


class Solution {
public:
    string longestPalindrome(string s) {
        string str = "#";
        for(int i = 0;i < s.size(); ++ i)
            str += (s.substr(i,1) + "#");
        int len = str.size();
        int mx = 0, idx = 0;
        vector<int> p(len, 0);
        int tag = 0, maxlen = 0;
        for(int i = 0;i < len; ++ i){
            p[i] = mx > i ? min(p[2 * idx - i], mx - i) : 1;
            while(i - p[i] >= 0 && i + p[i] < len && str[i + p[i]] == str[i - p[i]]) p[i] ++;
            if(i + p[i] > mx) mx = i + p[i], idx = i;
            if(maxlen < p[i]) maxlen = p[i], tag = i;
        }
        return s.substr((tag - 1)/2 - (p[tag] - 2) / 2, p[tag] - 1);
    }
};
