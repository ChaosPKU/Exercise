/*
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary does not contain duplicate words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].
*/

class Solution {
private:
    bool wordBreak(string s, unordered_set<string>& wordDict, string& str, int begin, vector<string>& res, vector<bool>& flag){
        if(begin == s.size()){
            res.push_back(str);
            return true;
        }
        if(!flag[begin])
            return false;
        bool f = false;
        for(auto it = wordDict.begin(); it != wordDict.end(); ++ it){
            if(begin + (*it).size() <= s.size() && *it == s.substr(begin,(*it).size())){
                string tmp = str;
                if(str != "") str += " ";
                    str += *it;
                f = wordBreak(s,wordDict,str,begin + (*it).size(), res, flag) || f;
                str = tmp;
            }
        }
        flag[begin] = f;
        return f;
    }
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> res;
        string str = "";
        vector<bool> flag(s.size(),true);
        wordBreak(s,wordDict,str,0,res,flag);
        return res;
    }
};
