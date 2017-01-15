/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
/*

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        if(!n) return ans;
        int cnt[2] = {0,0};
        auto it1 = nums.begin() + n / 3;
        auto it2 = nums.end() - n / 3 - 1;
        nth_element(nums.begin(),it1,nums.end());
        nth_element(nums.begin(),it2,nums.end());
        for(int i = 0;i < n; ++ i){
            if(nums[i] == (*it1))
                ++ cnt[0];
            else if(nums[i] == (*it2))
                ++ cnt[1];
        }
        if(cnt[0] > n / 3) ans.push_back(*it1);
        if(cnt[1] > n / 3) ans.push_back(*it2);
        return ans;
    }
};
