/*
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/

class Solution {
private:
    void backtracking(vector<string> &res, string &s, string &str, int i, int k){
        if(i == s.size() && k == 4){
            res.push_back(str);
            return;
        }
        if(k >= 4)
            return;
        for(int j = 1; j + i <= s.size(); ++ j){
            string tmp = str, news = s.substr(i, j);
            int newi = stoi(news);
            if(news.size() > 1 && news[0] == '0')
                break;
            if(newi >= 0 && newi <= 255){
                if(!str.empty()) str += ".";
                str += news;
                backtracking(res, s, str, i + j, k + 1);
                str = tmp;
            }
            else
                break;
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        string str = "";
        backtracking(res, s, str, 0, 0);
        return res;
    }
};
