/*

Given an integer array, your task is to find all the different possible increasing subsequences of the given array, and the length of an increasing subsequence should be at least 2 .

Example:
Input: [4, 6, 7, 7]
Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
Note:
The length of the given array will not exceed 15.
The range of integer in the given array is [-100,100].
The given array may contain duplicates, and two equal integers should also be considered as a special case of increasing sequence.

*/

class Solution {
public:
    void backtracking(vector<vector<int>> &res, vector<int> &vtr, vector<unordered_map<int, int>> &linklist, int b){
        if(vtr.size() >= 2)
            res.push_back(vtr);
        for(auto p : linklist[b]){
            vtr.push_back(p.first);
            backtracking(res, vtr, linklist, p.second);
            vtr.pop_back();
        }
        return;
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        int n = nums.size();
        vector<unordered_map<int ,int>> linklist(n);
        vector<vector<int>> res;
        unordered_map<int, int> udmp;
        for(int i = n - 1;i >= 0; -- i){
            udmp[nums[i]] = i;
            for(int j = n - 1;j > i; -- j)
                if(nums[j] >= nums[i])
                    linklist[i][nums[j]] = j;
        }
        vector<int> vtr;
        for(auto p : udmp){
            vtr.push_back(p.first);
            backtracking(res, vtr, linklist, p.second);
            vtr.pop_back();
        }
        return res;
    }
};
