/*
Given an array of integers, find out whether there are two distinct indices i and j in the array such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.
*/

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(k < 0 || t < 0) return false;
        set<int> window;
        for(int i = 0;i < nums.size(); ++ i){
            if(i > k) window.erase(nums[i-k-1]);
            auto pos = window.lower_bound(nums[i] - t);
            if(pos != window.end() && *pos - nums[i] <= t) return true;
            window.insert(nums[i]);
        }
        return false;
    }
};
