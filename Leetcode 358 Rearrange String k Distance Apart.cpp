/*

Given a non-empty string str and an integer k, rearrange the string such that the same characters are at least distance k from each other.

All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".

Example 1:
str = "aabbcc", k = 3

Result: "abcabc"

The same letters are at least distance 3 from each other.
Example 2:
str = "aaabc", k = 3 

Answer: ""

It is not possible to rearrange the string.
Example 3:
str = "aaadbbcc", k = 2

Answer: "abacabcd"

Another possible answer is: "abcabcda"

The same letters are at least distance 2 from each other.

*/

class Solution {
public:
    string rearrangeString(string str, int k) {
        if(str.size() == 1 || !k) return str;
        int n = str.size();
        unordered_map<char, int> udmp;
        priority_queue<pair<int, char>> pq;
        for(char c : str) udmp[c] ++;
        if(udmp.size() < k) return "";
        for(auto p : udmp)
            pq.push(make_pair(p.second, p.first));
        string res = "";
        vector<pair<int, char>> cache;
        while(!pq.empty()){
            cache.clear();
            int count = min(k, n);
            for(int i = 0;i < count; ++ i){
                if(pq.empty()) return "";
                auto p = pq.top();
                pq.pop();
                res.push_back(p.second);
                if(-- p.first > 0) cache.push_back(p);
                -- n;
            }
            for(auto p : cache) pq.push(p);
        }
        return res;
    }
};
