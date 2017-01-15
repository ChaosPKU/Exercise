/*
Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example:
Given "bcabc"
Return "abc"

Given "cbacdcbc"
Return "acdb"
*/

class Solution {
  public:
    string removeDuplicateLetters(string s) {
      int m[256] = {0}, visited[256] = {0};
      string res = "0";
      for(auto c : s) m[c] ++;
      for(auto c : s){
          m[c] --;
          if(visited[c]) continue;
          while(res.back() > c && m[res.back()]){
              visited[res.back()] = 0;
              res.pop_back();
          }
          res += c;
          visited[c] = 1;
      }
      return res.substr(1);
    }
  };
