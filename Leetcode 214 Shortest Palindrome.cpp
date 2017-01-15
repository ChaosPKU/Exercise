/*
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".
*/

class Solution {
  public:
    string shortestPalindrome(string s) {
        string r = s;
        reverse(r.begin(), r.end());
        string l = s + "#" + r;
        vector<int> p(l.size(), 0);
        for(int i = 1;i < l.size(); ++ i){
            int j = p[i - 1];
            while(j > 0 && l[i] != l[j])
                j = p[j - 1];
            p[i] = j + (l[i] == l[j]);
        }
        return r.substr(0, r.size() - p.back()) + s;
    }
  };
