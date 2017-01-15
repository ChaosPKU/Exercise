/*
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note: 
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:

Given [3, 1, 5, 8]

Return 167

    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        vector<int> tmp({1});
        tmp.insert(tmp.end(), nums.begin(), nums.end());
        tmp.push_back(1);
        swap(tmp, nums);
        int n = nums.size();
        if(!n) return 0;
        vector<vector<int>> res(n + 1, vector<int>(n + 2, 0));
        res[n - 1][n - 1]  = nums[n - 1];
        for(int d = 3; d <= n; ++ d){
            for(int i = 0; i + d - 1 < n; ++ i){
                int left = i, right = i + d - 1;
                for(int k = left + 1;k < right; ++ k)
                    res[left][right] = max(res[left][right], res[left][k] + res[k][right] + nums[left] * nums[k] * nums[right]);
            }
        }
        return res[0][n - 1];
    }
};
   
