/*
Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n^2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?
*/
// O(n log n)的版本
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        vector<int> vtr({nums[0]}); // 保存当前各长度递增子序列末尾数字最小的
        for(int i = 1;i < nums.size(); ++ i){
            int b = 0, e = vtr.size(), m = 0;
            while(b < e){
                m = b + (e - b) / 2;
                if(vtr[m] < nums[i])
                    b = m + 1;
                else e = m;
            }
            if(b == vtr.size()) vtr.push_back(nums[i]);
            else vtr[b] = min(vtr[b], nums[i]);
        }
        return vtr.size();
    }
};
