/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Examples:
pattern = "abab", str = "redblueredblue" should return true.
pattern = "aaaa", str = "asdasdasdasd" should return true.
pattern = "aabb", str = "xyzabcxzyabc" should return false.
Notes:
You may assume both pattern and str contains only lowercase letters.
*/

class Solution {
public:
    bool DFS(string &pattern, string &str, unordered_map<char, string>& udmp, unordered_set<string>& udst, int ptr, int sptr){
        if(ptr == pattern.size())
            return sptr == str.size();
        if(sptr >= str.size()) return false;
        for(int i = sptr;i < str.size(); ++ i){
            string s = str.substr(sptr, i - sptr + 1);
            if(udmp.find(pattern[ptr]) != udmp.end()){
                if(udmp[pattern[ptr]] != s) continue;
                else if(DFS(pattern, str, udmp, udst, ptr + 1, i + 1))
                    return true;
            }
            else{
                if(udst.find(s) != udst.end()) continue;
                udmp[pattern[ptr]] = s;
                udst.insert(s);
                if(DFS(pattern, str, udmp, udst, ptr + 1, i + 1))
                    return true;
                udst.erase(s);
                udmp.erase(pattern[ptr]);
            }
        }
        return false;
    }
    bool wordPatternMatch(string pattern, string str) {
        unordered_map<char, string> udmp;
        unordered_set<string> udst;
        return DFS(pattern, str, udmp, udst, 0, 0);
    }
};
