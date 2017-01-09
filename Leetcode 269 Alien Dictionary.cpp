/*
There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
The correct order is: "wertf".

Note:
You may assume all letters are in lowercase.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.
*/

class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> udmp;
        vector<int> indegree(26);
        unordered_set<char> udst;
        int n = words.size(), counter = 0;
        for(int i = 0;i < n - 1; ++ i){
            int b = 0, e = 0;
            bool flag = true;
            while(b < words[i].size() && e < words[i + 1].size()){
                udst.insert(words[i][b]);
                if(flag && words[i][b] != words[i + 1][e]){
                    if(udmp[words[i + 1][e]].find(words[i][b]) != udmp[words[i + 1][e]].end()) return "";  // 判断是否有b < e 且 b > e的情况存在
                    udmp[words[i][b]].insert(words[i + 1][e]);
                    flag = false;
                    
                }
                ++ b;
                ++ e;
            }
            if(flag && b < words[i].size()) // len(b) > len(e) 但尚未比较出大小
                return "";
            while(b < words[i].size())
                udst.insert(words[i][b ++]);
        }
        for(char c : words[n - 1])
            udst.insert(c);
        
        for(auto p : udmp)
            for(char c : p.second)
                indegree[c - 'a'] ++;  // 求所有点的入度

        string str = "";
        while(udst.size() > 0){
            vector<char> vtr;
            for(char c : udst){
                if(indegree[c - 'a'] == 0){
                    str += c;
                    for(char cc : udmp[c])
                        -- indegree[cc - 'a'];
                    vtr.push_back(c);
                }
            }
            if(vtr.empty()) return ""; // 单次循环无法删点，则必存在环
            for(char c : vtr) udst.erase(c);
        }
        return str;
    }
};
