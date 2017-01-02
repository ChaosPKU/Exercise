/*
Given a list of words (without duplicates), please write a program that returns all concatenated words in the given list of words.

A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

Example:
Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
 "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
Note:
The number of elements of the given array will not exceed 10,000
The length sum of elements in the given array will not exceed 600,000.
All the input string will only include lower case letters.
The returned elements order does not matter.
*/
//用Hash表来加速DFS
class Solution {
public:
    bool check(const unordered_set<string> &udmp, const string &s, int b, int cnt, unordered_set<string> &hashset){
        if(b == s.size()) return cnt > 1;
        for(int i = 1;b + i <= s.size(); ++ i){
            if(udmp.find(s.substr(b, i)) == udmp.end()) continue;
            string tmp = s.substr(b + i);
            if(tmp != "" && hashset.find(tmp) != hashset.end()) return true;
            if(check(udmp, s, b + i, cnt + 1, hashset)) {
                if(tmp != "") hashset.insert(tmp);
                return true;
            }
        }
        return false;
    }
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> res;
        if(words.size() < 2) return res;
        int maxLen = 0, n = words.size(), cnt= 0;
        unordered_set<string> udmp(words.begin(), words.end()), hashset;
        for(string s : words){
            if(check(udmp, s, 0, 0, hashset))
                res.push_back(s);
        }
        return res;
    }
};
