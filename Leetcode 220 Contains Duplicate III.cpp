/*
Given an array of integers, find out whether there are two distinct indices i and j in the array such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.
*/


/*
Given an array of integers, find out whether there are two distinct indices i and j in the array such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.
*/

// O(n) version
// 当对所有下标范围在k之内的情况进行考虑，并且所有数字两两之间相差都大于t(大于等于t+1)的时候，返回false，否则为true。
// 所有数字两两之间相差都大于等于t+1，表明如果将数字放入大小为t+1的bucket中，则每个桶中必有一个(反过来则不成立，需要检查前后桶)，由此可得算法。
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(k <= 0 || t < 0) return false;
        unordered_map<int, int> window;
        for(int i = 0;i < nums.size(); ++ i){
            if(i > k) window.erase(floor((double)nums[i - k - 1] / (t + 1)));
            int key = floor((double)nums[i] / (t + 1));
            if(window.find(key) != window.end() || (window.find(key - 1) != window.end() && abs((long)window[key - 1] - nums[i]) <= t) || (window.find(key + 1) != window.end() && abs((long)window[key + 1] - nums[i]) <= t)) return true;
            window[key] = nums[i];
        }
        return false;
    }
};

// O(nlogk) version
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
