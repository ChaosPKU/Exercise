/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
*/

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int left = 0, right = n - 1, res = 0;
        int maxleft = 0, maxright = 0;
        while(left < right){
            if(height[left] <= height[right]){
                if(height[left] >= maxleft) maxleft = height[left];
                else res += maxleft - height[left];
                ++ left;
            }
            else{
                if(height[right] >= maxright) maxright = height[right];
                else res += maxright - height[right];
                --right;
            }
        }
        return res;
    }
};
