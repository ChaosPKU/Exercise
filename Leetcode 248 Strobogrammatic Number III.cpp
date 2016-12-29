/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

For example,
Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.

Note:
Because the range might be a large number, the low and high numbers are represented as string.
*/
//与2不同，按单个生成元素是否满足条件决定退出条件。
class Solution {
public:
    bool compare(string s1, string s2){
        if(s1.size() < s2.size()) return true;
        else if(s1.size() > s2.size()) return false;
        for(int i = 0;i < s1.size(); ++ i)
            if(s1[i] < s2[i]) return true;
            else if(s1[i] > s2[i]) return false;
        return true;
    }
    int strobogrammaticInRange(const vector<string>& nums, const string& low, const string& high, string t, int cnt){
	    if (!compare(t, high)) return cnt;
	    if(compare(low, t) && compare(t, high)) {
	        if(t.size() == 1 || (t.size() > 1 && t[0] != '0'))
	            cnt ++;
	    }
	    for(int i = 0;i < nums.size(); i += 2)
	        cnt = strobogrammaticInRange(nums, low, high, nums[i] + t + nums[i + 1], cnt);
	    return cnt;
    }
    int strobogrammaticInRange(string low, string high) {
        if(!compare(low, high)) return 0;
        vector<string> nums({"0", "0", "1", "1", "6", "9", "8", "8", "9", "6"});
        int cnt = strobogrammaticInRange(nums, low, high, "", 0);
    	cnt = strobogrammaticInRange(nums, low, high, "0", cnt);
    	cnt = strobogrammaticInRange(nums, low, high, "1", cnt);
    	cnt = strobogrammaticInRange(nums, low, high, "8", cnt);
    	return cnt;
    }
};
