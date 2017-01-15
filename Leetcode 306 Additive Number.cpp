/*
Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.

For example:
"112358" is an additive number because the digits can form an additive sequence: 1, 1, 2, 3, 5, 8.

1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
"199100199" is also an additive number, the additive sequence is: 1, 99, 100, 199.
1 + 99 = 100, 99 + 100 = 199
Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.

Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.

Follow up:
How would you handle overflow for very large input integers?
*/


class Solution {
    private:
      bool check(string num1, string num2, string num){
        if(num1.size() > 1 && num1[0] == '0' || num2.size() > 1 && num2[0] == '0')
          return false;
        string sum = add(num1, num2);
        if(sum == num) return true;
        if(num.size() <= sum.size() || sum != num.substr(0, sum.size())) return false;
        else return check(num2, sum, num.substr(sum.size()));
      }
      string add(string &n, string &m){
        string res;
        int i=n.size()-1, j=m.size()-1, carry=0;
        while(i>=0 || j>=0){
          int sum=carry+(i>=0 ? (n[i--]-'0') : 0) + (j>=0?  (m[j--]-'0') : 0);
          res.push_back(sum%10+'0');
          carry=sum/10;
        }
        if(carry) res.push_back(carry+'0');
        reverse(res.begin(), res.end());
        return res;
      }
    public:
      bool isAdditiveNumber(string &num) {
        int n = num.size();
        for(int i = 1;i <= n / 2; ++ i){
          for(int j = 1;j <= (n - i) / 2; ++ j){
            if(check(num.substr(0, i), num.substr(i, j), num.substr(i + j)))
              return true;
          }
        }
        return false;
      }
    };
