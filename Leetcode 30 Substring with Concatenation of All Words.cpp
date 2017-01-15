/*
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int slen = s.size(), wslen = words.size();
        if(slen <= 0 || wslen <= 0) return res;
        int wlen = words[0].size();
        int window = wlen * wslen;
        if(slen < window) return res;
        unordered_map<string, int> dict;
        for(string word : words)
            ++ dict[word];
        for(int i = 0;i <= slen - window; ++ i){
            unordered_map<string, int> tdict(dict);
            int cnt = wslen, j = 0;
            for(;j < wslen; ++ j){
                string str = s.substr(i + j * wlen, wlen);
                if(tdict[str] == 0)
                    break;
                else{
                    tdict[str] -= 1;
                    -- cnt;
                }
            }
            if(j < wslen) continue;
            else res.push_back(i);
        }
        return res;
    }
};
