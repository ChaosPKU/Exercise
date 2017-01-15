/*
Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
*/

class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size(), i = 0;
        if(k == 0) return num;
        if(n == k) return "0";
        stack<char> stk;
        for(;i < num.size(); ++ i){
            while(!stk.empty() && stk.top() > num[i] && k > 0){
                stk.pop();
                k --;
            }
            if(k == 0) break;
            if(num[i] != '0')
                stk.push(num[i]);
        }
        string s;
        while(!stk.empty()){
            s.push_back(stk.top());
            stk.pop();
        }
        reverse(s.begin(), s.end());
        s = s + num.substr(i);
        i = 0;
        while(i < s.size() && s[i] == '0') ++ i;
        return i == s.size() ? "0" : s.substr(i, s.size() - k);
    }
};
