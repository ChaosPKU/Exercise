/*
Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example:
(1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6]. 
(2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].

Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?
*/

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        auto midptr = nums.begin() + n / 2;
        nth_element(nums.begin(), midptr, nums.end());
        #define trans(x) nums[(2 * x + 1) % (n | 1)]
        int i = 0,j = 0,k = n - 1;
        int mid = *midptr;
        while(j <= k){
            if(trans(j) > mid){
                swap(trans(i ++),trans(j ++));
            }
            else if(trans(j) == mid){
                j ++;
            }
            else{
                swap(trans(k --), trans(j));
            }
        }
    }
};
