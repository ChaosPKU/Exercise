/*
Count the number of prime numbers less than a non-negative number, n.
*/

class Solution {
public:
    int countPrimes(int n) {
        if(n <= 2)
            return 0;
        int res = n - 2;
        int *nums = new int[n + 1];
        for(int i = 0; i < n; ++ i)
            nums[i] = i;
        for(int i = 2; i <= sqrt(n - 1); ++ i){
            if(nums[i] == -1)
                continue;
            for(int j = i;j <= (n - 1) / i; ++ j){
                if(nums[i * j] != -1){
                    nums[i * j] = -1;
                    -- res;
                }
            }
        }
        delete []nums;
        return res;
    }
};
