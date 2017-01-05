/*

Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:

[-2, 0, 1]
[-2, 0, 3]
Follow up:
Could you solve it in O(n2) runtime?

*/

//对于这道题目来说，排序不影响结果，但却可以引入很好的性质。
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size(), res = 0;
        if(n < 3) return 0;
        sort(nums.begin(), nums.end());
        for(int i = 0;i < (int)nums.size() - 2; ++ i){
            if(nums[i] + nums[i + 1] + nums[i + 2] >= target) break;
            int j = i + 1, k = n - 1;
            while(j < k){
                while(j < k && nums[i] + nums[j] + nums[k] >= target) -- k;
                res += k - j;
                ++ j;
            }
        }
        return res;
    }
};
