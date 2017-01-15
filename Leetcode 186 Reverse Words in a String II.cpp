/*
Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?
*/

class Solution {
public:
    void reverseWords(string &s) {
        int b = 0, e = 0, n = s.size(), pb = 0, pe = 0;
        while(e < n){
            while(b < n && s[b] == ' ') ++ b;
            if(b == n) break;
            e = b + 1;
            while(e < n && s[e] != ' ') ++ e;
            pb = b, pe = e - 1;
            while(pb < pe)
                swap(s[pb++], s[pe--]);
            b = e;
        }
        reverse(s.begin(), s.end());
    }
};
