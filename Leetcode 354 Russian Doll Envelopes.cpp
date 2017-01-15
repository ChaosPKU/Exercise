/*
You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
*/

class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end());
        vector<int> res;
        res.reserve(envelopes.size());
        int i=0;
        while(i < envelopes.size()){
            deque<vector<int>::iterator> dq;
            int cur = envelopes[i].first;
            while(i < envelopes.size() && envelopes[i].first == cur){
                dq.push_front(lower_bound(res.begin(), res.end(), envelopes[i++].second));
            }
            for(int j = 0;j < dq.size(); ++ j){
                if(dq[j] == res.end()) res.push_back(envelopes[i - j - 1].second);
                else *(dq[j]) = envelopes[i - j - 1].second;
            }
        }
        return res.size();
    }
};
