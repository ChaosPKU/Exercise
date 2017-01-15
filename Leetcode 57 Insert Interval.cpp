/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        int len = intervals.size();
        vector<Interval> res;
        int left = newInterval.start;
        bool flag = true;
        bool flag2 = true;
        int right = newInterval.end;
        for(Interval i : intervals){
            if(i.end < newInterval.start)
                res.push_back(i);
            else if(i.start <= newInterval.start){
                if(flag){
                    left = i.start;
                    flag = false;
                    right = max(right, i.end);
                }
            }
            else if(i.start <= newInterval.end){
                right = max(right, i.end);
            }
            else {
                if(flag2){
                    res.push_back(Interval(left, right));
                    flag2 = false;
                }
                res.push_back(i);
            }
        }
        if(flag2)
            res.push_back(Interval(left, right));
        return res;
    }
};
