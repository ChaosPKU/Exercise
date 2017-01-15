/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".
Hint:

No scary math, just apply elementary math knowledge. Still remember how to perform a long division?
Try a long division on 4/9, the repeating part is obvious. Now try 4/333. Do you see a pattern?
Be wary of edge cases! List out as many test cases as you can think of and test your code thoroughly.
*/

class Solution {
    public:
      string fractionToDecimal(int numerator, int denominator) {
        int minus = 1;
        if((numerator < 0) ^ (denominator < 0) && (numerator * denominator)) minus = -1;
        long long n = abs((long long)numerator), d = abs((long long)denominator);
        char buffer[32];
        sprintf(buffer, "%lld", n / d);
        string res = buffer;
        long long num = n % d;
        if(!num) return minus == 1 ? res : ("-" + res);
        res += ".";
        int cnt = res.size() - 1;
        unordered_map<long long, int> m;
        auto alter = m.find(num);
        while(alter == m.end() && num){
          long long tmpn = num;
          bool flag = false;
          while((num*=10) < d){
            res += "0";
            ++ cnt;
            m[num / 10] = cnt;
            flag = true;
          }
          sprintf(buffer, "%lld", num / d);
          res += buffer;
          cnt += 1;
          if(!flag)
            m[tmpn] = cnt;
          else
            m[num / 10] = cnt;
          num = num % d;
          alter = m.find(num);
        }
        if(num)
          res = res.substr(0, alter->second) + "(" + res.substr(alter->second) + ")";
        return minus == 1 ? res : ("-" + res);
      }
    };
