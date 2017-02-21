/*
Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has, please find out a way you can make one square by using up all those matchsticks. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.

Your input will be several matchsticks the girl has, represented with their stick length. Your output will either be true or false, to represent whether you could make one square using all the matchsticks the little match girl has.

Example 1:
Input: [1,1,2,2,2]
Output: true

Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
Example 2:
Input: [3,3,3,3,4]
Output: false

Explanation: You cannot find a way to form a square with all the matchsticks.
Note:
The length sum of the given matchsticks is in the range of 0 to 10^9.
The length of the given matchstick array will not exceed 15.
*/

class Solution {
public:
    int n = 0;
    void DFS(int mask, vector<int>& nums, vector<int>& masks, int depth, int rest){
        if(rest == 0){
            masks.push_back(mask);
            return;
        }
        if(depth == n)
            return;
        if(rest >= nums[depth])
            DFS(mask | (1 << depth), nums, masks, depth + 1, rest - nums[depth]);
        DFS(mask, nums, masks, depth + 1, rest);
    }
    bool makesquare(vector<int>& nums) {
        n = nums.size();
        int mask = 0;
        long sum = accumulate(nums.begin(), nums.end(), 0l);
        if(sum & 0x3) return false;
        long len = sum >> 2;
        vector<int> masks;
        DFS(mask, nums, masks, 0, len);
        unordered_set<int> udst;
        for(int i = 0;i < masks.size(); ++ i)
            for(int j = i + 1; j < masks.size(); ++ j){
                if((masks[i] & masks[j]) == 0){
                    int tmp = masks[i] | masks[j];
                    if(udst.find(tmp ^ ((1 << n) - 1)) != udst.end())
                        return true;
                    udst.insert(tmp);
                }
            }
        return false;
    }
};
