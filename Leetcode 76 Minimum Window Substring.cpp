/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
*/

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> map(128, 0);
        int counter = t.size();
        int begin = 0, end = 0, d = INT_MAX, head = 0;
        for(auto i : t) ++ map[i];
        for(int i = 0;i < s.size(); ++ i){
            if(map[s[end ++]] -- > 0) counter --;
            while(counter == 0){
                if(d > end - begin) d = end - (head = begin);
                if(map[s[begin ++]] ++ == 0) counter ++;
            }
        }
        return d == INT_MAX ? "" : s.substr(head, d);
    }
};
