/*
Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:
Given nums = [-2, 5, -1], lower = -2, upper = 2,
Return 3.
The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2.
*/

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        multiset<long> mst;
        mst.insert(0);
        int res = 0, i;
        long sum = 0;
        for(int i = 0;i < nums.size(); ++ i){
            sum += nums[i];
            res += distance(mst.lower_bound(sum - upper), mst.upper_bound(sum - lower));
            mst.insert(sum);
        }
        return res;
    }
};
