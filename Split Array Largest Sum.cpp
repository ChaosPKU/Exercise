/*
Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

Note:
Given m satisfies the following constraint: 1 ≤ m ≤ length(nums) ≤ 14,000.

Examples:

Input:
nums = [7,2,5,10,8]
m = 2

Output:
18

Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
*/

class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        if(!n) return 0;
        int k, tmp;
        long long minN, t;
        vector<long long> dp(nums.begin(), nums.end());
        for(int i = 1;i < n; ++ i)
            dp[i] += dp[i - 1];
        vector<long long> sum(dp.begin(), dp.end());
        for(int i = 1;i < m; ++ i){
            k = n - 1;
            bool flag = true;
            for(int j = n - 1; j >= i; -- j){
                minN = dp[j];
                tmp = k;
                for(; k >= 0; -- k){
                    t = max(dp[k], sum[j] - sum[k]);
                    if(minN > t){
                        minN = t;
                        tmp = k;
                    }
                    if(k > 0 && t < max(sum[j] - sum[k - 1], dp[k - 1]))
                        break;
                }
                k = tmp;
                dp[j] = minN;
            }
        }
        return dp[n - 1];
    }
};

/*
class Solution {
private:
    bool doable (const vector<int>& nums, int cuts, long long max) {
        int acc = 0;
        for (num : nums) {
            // This step is unnecessary for this problem. I didn't discard this line because I want doable function more generalized.
            if (num > max) return false;
            else if (acc + num <= max) acc += num;
            else {
                --cuts;
                acc = num;
                if (cuts < 0) return false;
            }
        }
        return true;
    }
    
public:
    int splitArray(vector<int>& nums, int m) {
        long long left = 0, right = 0;
        for (num : nums) {
            left = max(left, (long long)num);
            right += num;
        }
        
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (doable(nums, m - 1, mid)) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
*/
