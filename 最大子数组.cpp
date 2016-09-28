/*
给定一个整数数组和一个整数 k，找出 k 个不重叠子数组使得它们的和最大。每个子数组的数字在数组中的位置应该是连续的。返回最大的和。子数组最少包含一个数。
样例
给出数组 [-1,4,-2,3,-2,3] 以及 k = 2，返回 8
*/
class Solution {
public:
    /**
     * @param nums: A list of integers
     * @param k: An integer denote to find k non-overlapping subarrays
     * @return: An integer denote the sum of max k non-overlapping subarrays
     */
    int maxSubArray(vector<int> nums, int k) {
        int n = nums.size();
        vector<int> res(n + 1, 0);
        for(int l = 1;l <= k; ++ l){
            for(int i = n; i >= l; -- i){
                res[i] = INT_MIN;
                int tmp = 0;
                for(int j = i - 1;j >= l - 1; -- j){
                    tmp = max(nums[j], tmp + nums[j]);
                    res[i] = max(res[i], res[j] + tmp);
                }
            }
        }
        return res[n];
    }
};
