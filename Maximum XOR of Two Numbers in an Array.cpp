/*
Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.

Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

Could you do this in O(n) runtime?

Example:

Input: [3, 10, 5, 25, 2, 8]

Output: 28

Explanation: The maximum result is 5 ^ 25 = 28.
*/

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int res = 0;
        unordered_set<int> udst;
        for(int i = 31;i >= 0; -- i){
            res <<= 1;
            udst.clear();
            for(int n : nums)
                udst.insert(n >> i);
            for(int n : udst)
                if(udst.find(res ^ 1 ^ n) != udst.end()){
                    ++ res;
                    break;
                }
        }
        return res;
    }
};
