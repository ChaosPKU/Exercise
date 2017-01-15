/*
Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/

class Solution {
public:
    string multiply(string num1, string num2) {
        string res(num1.size() + num2.size(), '0');
        for(int i = num1.size() - 1; i >= 0; -- i){
            for(int j = num2.size() - 1; j >= 0; -- j){
                int tmp = res[i + j + 1] - '0' + (num1[i] - '0') * (num2[j] - '0');
                res[i + j + 1] = tmp % 10 + '0';
                res[i + j] += tmp / 10;
            }
        }
        int pos = 0;
        while(pos < res.size() - 1 && res[pos] == '0')
            ++ pos;
        return res.substr(pos);
    }
};
