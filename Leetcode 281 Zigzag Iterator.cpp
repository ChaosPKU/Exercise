/*
Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question - Update (2015-09-18):
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

[1,2,3]
[4,5,6,7]
[8,9]
It should return [1,4,8,2,5,9,3,6,7].
*/

class ZigzagIterator {
public:
    queue<pair<vector<int>::iterator, vector<int>::iterator>> Q;
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if(!v1.empty()) Q.push(make_pair(v1.begin(), v1.end()));
        if(!v2.empty()) Q.push(make_pair(v2.begin(), v2.end()));
    }

    int next() {
        vector<int>::iterator begin = Q.front().first, end = Q.front().second;
        Q.pop();
        if(begin + 1 != end)
            Q.push(make_pair(begin + 1, end));
        return *begin;
    }

    bool hasNext() {
        return !Q.empty();
    }
};

/*
class ZigzagIterator {
public:
    int flg = 0, ctr = 0, counter = 0, tot = 0;
    vector<vector<int>> vtr;
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if(!v1.empty()) vtr.push_back(v1);
        if(!v2.empty()) vtr.push_back(v2);
        tot = v1.size() + v2.size();
        while(counter < tot){
            if(flg == vtr.size()){
                flg = 0;
                ctr ++;
            }
            if(vtr[flg].size() > ctr)
                break;
            ++ flg;
        }
        cout << flg << " " << ctr << endl;
    }

    int next() {
        ++ counter;
        return vtr[flg ++][ctr];
    }

    bool hasNext() {
        if(counter < tot){
            while(true){
                if(flg == vtr.size()){
                    flg = 0;
                    ctr ++;
                }
                if(vtr[flg].size() > ctr)
                    break;
                ++ flg;
            }
            return true;
        }
        return false;
    }
};

*/

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
