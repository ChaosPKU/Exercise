/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/

class Solution {
public:
    vector<vector<int> > fourSum(vector<int>& nums, int& target) {
        vector<vector<int> > res;
        int n = (int)nums.size();
        sort(nums.begin(), nums.end());
        for(int i = 0;i < n - 3; ++ i){
            for(int j = i + 1;j < n - 2; ++ j){
                int ptr = j + 1,back_ptr = n - 1;
                while(ptr < back_ptr){
                    int sum = nums[i] + nums[j] + nums[ptr] + nums[back_ptr];
                    if(sum == target){
                        res.push_back(vector<int>({nums[i],nums[j],nums[ptr],nums[back_ptr]}));
                        int a = nums[ptr],b = nums[back_ptr];
                        while(ptr < back_ptr && nums[ptr] == a){
                            ++ ptr;
                        }
                        while(back_ptr > ptr && nums[back_ptr] == b){
                            -- back_ptr;
                        }
                    }
                    else if(sum < target)
                        ++ ptr;
                    else -- back_ptr;
                }
                while(j + 1 < n - 2 && nums[j + 1] == nums[j])
                    ++ j;
            }
            while(i + 1 < n - 3 && nums[i + 1] == nums[i])
                ++ i;
        }
        return res;
    }
};
