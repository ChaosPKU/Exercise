/*
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
*/

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return 0;
        int maxN = *max_element(nums.begin(), nums.end());
        int minN = *min_element(nums.begin(), nums.end());
        int len = maxN - minN;
        if(len < 2) return len;
        vector<int> buck_max(n, INT_MIN);
        vector<int> buck_min(n, INT_MAX);
        for(int i = 0;i < n; ++ i){
            int index = (double)(nums[i] - minN) / len * (n - 1);
            buck_max[index] = max(buck_max[index], nums[i]);
            buck_min[index] = min(buck_min[index], nums[i]);
        }
        int gap = 0, pre = buck_max[0];
        for(int i = 1;i < n; ++ i){
            if(buck_max[i] == INT_MIN)
                continue;
            gap = max(gap, buck_min[i] - pre);
            pre = buck_max[i];
        }
        return gap;
    }
};
