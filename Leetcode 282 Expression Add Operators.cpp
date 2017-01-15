/*
Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Examples: 
"123", 6 -> ["1+2+3", "1*2*3"] 
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []
*/

class Solution {
  private:
    void helper(vector<string> &res, string s, int pos, string num, int target, long last, long pre, char op){
      if(pos == num.size() && last == target){
        res.push_back(s);
      }
      else{
        for(int i = pos + 1; i <= num.size(); ++ i){
          string t = num.substr(pos, i - pos);
          long now = stol(t);
          if(to_string(now).size() != t.size()) continue;
          helper(res, s + "+" + t, i, num, target, last + now, now, '+');
          helper(res, s + "-" + t, i, num, target, last - now, now, '-');
          helper(res, s + "*" + t, i, num, target, op == '+' ? (last - pre + pre * now) : (op == '-' ? (last + pre - pre * now) : (pre * now)) , pre * now, op);
        }
      }
    }
  public:
    vector<string> addOperators(string num, int target) {
      vector<string> res;
      if(num.empty()) return res;
      for(int i = 1;i <= num.size(); ++ i){
        string s = num.substr(0, i);
        long cur = stol(s);
        if(to_string(cur).size() != s.size()) continue;
        helper(res,s,i,num,target,cur,cur,'#');
      }
      return res;
    }
  };
