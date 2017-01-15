/*
Implement pow(x, n)
*/

class Solution {
public:
    double myPow(double x, int n) {
        unsigned long long p;
        if(n < 0) {
            x = 1 / x;
            p = -n;
        }
        else
            p = n;
        double res = p & 1 ? x : 1;
        while(p){
            p = p >> 1;
            x = x * x;
            res *= p & 1 ? x : 1;
        }
        return res;
    }
};
