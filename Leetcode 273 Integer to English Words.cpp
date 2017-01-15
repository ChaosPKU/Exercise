/*
Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Hint:

Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.
Group the number by thousands (3 digits). You can write a helper function that takes a number less than 1000 and convert just that chunk to words.
There are many edge cases. What are some good test cases? Does your code work with input such as 0? Or 1000010? (middle chunk is zero and should not be printed out)
*/

class Solution {
  private:
    string strs[40] = { "", " One", " Two", " Three", " Four", " Five", " Six", " Seven", " Eight", " Nine" , " Ten", " Eleven", " Twelve", " Thirteen", " Fourteen", " Fifteen", " Sixteen", " Seventeen", " Eighteen", " Nineteen" , "", "", " Twenty", " Thirty", " Forty", " Fifty", " Sixty", " Seventy", " Eighty", " Ninety" , "", " Thousand", " Million", " Billion", " Triliion" };
    string convert(int n){
      string res = "";
      if(n){
        int h = n / 100;
        n %= 100;
        int t = n / 10;
        int s = n % 10;
        if(h) res += strs[h] + " Hundred";
        if(t){
          if(t == 1){
            res += strs[10 + s];
            return res;
          }
          else res += strs[20 + t];
        }
        if(s) res += strs[s];
      }
      return res;
    }
  public:
      string numberToWords(int num) {
        string res = "";
        for(int i = 0;i < 4; ++ i){
          if(num % 1000)
          res = convert(num % 1000) + strs[30 + i] + res;
          num /= 1000;
        }
        return res.size() ? res.substr(1) : "Zero";
      }
    };
