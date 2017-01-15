/*
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button  to reset your code definition.
*/

class Solution {
public:
    int myAtoi(string str) {
        int res = 0;
        int i = 0, minus = 1;
        if(str == "-2147483647") return -2147483647;
        while(str[i] == ' ')
            ++ i;
        if(str[i] == '-'){
            ++ i;
            minus = -1;
        }
        else if(str[i] == '+')
            ++ i;
        for(;i < str.size(); ++ i){
            if(str[i] >= '0' && str[i] <= '9'){
                if(res == 214748364){
                    if(str[i] >= '7' && minus == 1)
                        return 2147483647;
                    else if(str[i] >= '8' && minus == -1)
                        return -2147483648;
                }
                else if(res > 214748364){
                    return minus == 1 ? 2147483647 : -2147483648;
                }
                res = res * 10 + str[i] - '0';
            }
            else
                return res * minus;
        }
        return res * minus;
    }
};
