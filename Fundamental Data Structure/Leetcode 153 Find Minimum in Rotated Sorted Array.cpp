/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = (int)nums.size() - 1;
        while(l < r){
            int m = (l + r) >> 1;
            if(nums[m] > nums.back()) l = m + 1;
            else r = m;
            // cout << l << " " << r << endl;
        }
        return nums[l];
    }
};
