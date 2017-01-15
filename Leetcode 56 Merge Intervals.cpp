/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
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
private:
    static bool cmp(const Interval &a, const Interval &b){
        if(a.start == b.start)
            return a.end < b.end;
        return a.start < b.start;
    }
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        int n = intervals.size();
        vector<Interval> res;
        if(!n) return res;
        sort(intervals.begin(),intervals.end(),cmp);
        int s = intervals[0].start;
        int e = intervals[0].start;
        for(int i = 1;i < n; ++ i){
            e = max(e, intervals[i-1].end);
            if(intervals[i].start <= e){
                continue;
            }
            res.push_back(Interval(s, e));
            s = intervals[i].start;
            e = intervals[i].end;
        }
        res.push_back(Interval(s, max(intervals[n-1].end,e)));
        return res;
    }
};
