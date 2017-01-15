/*

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)

Note:
You can assume that you can always reach the last index.

*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size(),ans = 1;
        if(!n) return 0;
        if(n == 1) return 0;
        int t = nums[0], i = 0, m = 0;
        for(i = 0,m = nums[0];i < n - 1 && i <= m; ++ i){
            t = max(t, i + nums[i]);
            if(i == m){
                m = t;
                ans ++;
            }
        }
        return ans;
    }
};
