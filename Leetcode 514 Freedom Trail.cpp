/*
In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring", and use the dial to spell a specific keyword in order to open the door.

Given a string ring, which represents the code engraved on the outer ring and another string key, which represents the keyword needs to be spelled. You need to find the minimum number of steps in order to spell all the characters in the keyword.

Initially, the first character of the ring is aligned at 12:00 direction. You need to spell all the characters in the string key one by one by rotating the ring clockwise or anticlockwise to make each character of the string key aligned at 12:00 direction and then by pressing the center button. 
At the stage of rotating the ring to spell the key character key[i]:
You can rotate the ring clockwise or anticlockwise one place, which counts as 1 step. The final purpose of the rotation is to align one of the string ring's characters at the 12:00 direction, where this character must equal to the character key[i].
If the character key[i] has been aligned at the 12:00 direction, you need to press the center button to spell, which also counts as 1 step. After the pressing, you could begin to spell the next character in the key (next stage), otherwise, you've finished all the spelling.
Example:


Input: ring = "godding", key = "gd"
Output: 4
Explanation:
 For the first key character 'g', since it is already in place, we just need 1 step to spell this character. 
 For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
 Also, we need 1 more step for spelling.
 So the final output is 4.
Note:
Length of both ring and key will be in range 1 to 100.
There are only lowercase letters in both strings and might be some duplcate characters in both strings.
It's guaranteed that string key could always be spelled by rotating the string ring.
*/

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        vector<int> p[26];
        int n = ring.size(), m = key.size(), pos = 0, p_pos = 0;
        vector<int> pre(n), cur(n), *p_pre = &pre, *p_cur = &cur;
        for(int i = 0;i < n; ++ i)
            p[ring[i] - 'a'].push_back(i);
        for(int i = 0;i < p[key[0] - 'a'].size(); ++ i){
            pos = p[key[0] - 'a'][i];
            pre[pos] = min(pos + 1, n - pos + 1);
        }
        for(int i = 1;i < m; ++ i){
            for(int j = 0;j < p[key[i] - 'a'].size(); ++ j){
                pos = p[key[i] - 'a'][j];
                (*p_cur)[pos] = INT_MAX;
                for(int k = 0;k < p[key[i - 1] - 'a'].size(); ++ k){
                    p_pos = p[key[i - 1] - 'a'][k];
                    (*p_cur)[pos] = min((*p_cur)[pos], (*p_pre)[p_pos] + 1 + min((pos - p_pos + n) % n, (p_pos - pos + n) % n));
                }
            }
            swap(p_cur, p_pre);
        }
        int res = INT_MAX;
        for(int i = 0;i < p[key[m - 1] - 'a'].size(); ++ i){
            pos = p[key[m - 1] - 'a'][i];
            res = min(res, (*p_pre)[pos]);
        }
        return res;
    }
};
