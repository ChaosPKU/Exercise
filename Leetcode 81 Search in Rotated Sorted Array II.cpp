/*
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int b = 0, e = n - 1;
        while(b < e){
            int m = b + (e - b) / 2;
            if(target == nums[m]) return true;
            if(nums[b] == nums[e] && nums[b] == nums[m]){
                -- e;
            }
            else if((nums[b] > target) ^ (target > nums[m]) ^ (nums[m] < nums[b]))
                b = m + 1;
            else
                e = m;
        }
        if(target == nums[b]) return true;
        else return false;
    }
};
