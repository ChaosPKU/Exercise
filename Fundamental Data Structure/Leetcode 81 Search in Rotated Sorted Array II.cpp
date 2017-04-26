/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int b = 0, e = (int)nums.size() - 1;
        while(b < e){
            int m = (b + e) >> 1;
            if(nums[m] == target)
                return true;
            if(nums[m] == nums.back()){
                for(int k = b; k <= e; ++ k)
                    if(nums[k] == target) return 1;
                return 0;
            }
            if((nums[m] > nums.back()) ^ (nums.back() >= target) ^ (target > nums[m]))
                e = m;
            else b = m + 1;
        }
        return e >= 0 && nums[b] == target ? 1 : 0;
    }
};
