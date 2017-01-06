/*
Given a sorted integer array where the range of elements are in the inclusive range [lower, upper], return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].

*/

class Solution {
public:
    string get_range(long b, long e){
        return (e == b) ? to_string(e) : string(to_string(b) + "->" + to_string(e));
    }
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> result;
        long pre = (long)lower - 1;
        for(int i = 0; i <= nums.size(); i ++){
            long cur = (i == nums.size() ? (long)upper + 1 : nums[i]);
            if(cur - 2 >= pre)
                result.push_back(get_range(pre + 1, cur - 1));
            pre = cur;
        }
        return result;
    }
};
