/*
Given a data stream input of non-negative integers a1, a2, ..., an, ..., summarize the numbers seen so far as a list of disjoint intervals.

For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:

[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]
Follow up:
What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?

Credits:
Special thanks to @yunhong for adding this problem and creating most of the test cases.
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
class SummaryRanges {
public:
    struct comp{
        bool operator()(const Interval &a, const Interval &b){
            return a.start < b.start;
        }
    };
    set<Interval, comp> st;
    
    /** Initialize your data structure here. */
    SummaryRanges() {
        st.clear();
    }
    
    void addNum(int val) {
        auto it = st.lower_bound(Interval(val, val)), last = it;
        int start = val, end = val;
        
        
        // if(it != st.begin() && (--it)->end + 1 < val) it ++;
        // while(it != st.end() && val + 1 >= it->start && val - 1 <= it->end)
        // {
        //     start = min(start, it->start);
        //     end = max(end, it->end);
        //     it = st.erase(it);
        // }
        if(it -> start == val) return;
        if(last != st.begin() && (-- last) -> end + 1 >= val){
            if(last -> end >= val) return;
            start = last -> start;
            it = st.erase(last);
        }
        if(it != st.end() && it -> start == val + 1){
            end = it -> end;
            it = st.erase(it);
        }
        
        st.insert(it, Interval(start, end));
    }
    
    vector<Interval> getIntervals() {
        return vector<Interval>(st.begin(), st.end());
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
