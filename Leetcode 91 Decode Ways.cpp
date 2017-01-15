/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.
*/

class Solution {
public:
    int numDecodings(string s) {
        if(s.size() == 0 || s[0] == '0') return 0;
        if(s.size() == 1) return 1;
        #define checkzero(x) (s[x] != '0')
        #define check(x) (s[x - 1] == '1' || (s[x - 1] == '2' && s[x] < '7'))
        int pre1 = checkzero(0), pre2 = check(1) + pre1 * checkzero(1);
        for(int i = 2;i < s.size(); ++ i){
            int tmp = pre1 * check(i) + pre2 * checkzero(i);
            pre1 = pre2;
            pre2 = tmp;
        }
        return pre2;
    }
};
