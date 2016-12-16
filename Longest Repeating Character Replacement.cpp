/*
Given a string that consists of only uppercase English letters, you can replace any letter in the string with another letter at most k times. Find the length of a longest substring containing all repeating letters you can get after performing the above operations.

Note:
Both the string's length and k will not exceed 104.

Example 1:

Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.
Example 2:

Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        int b = 0, e = 0, maxCount = 0;
        int dict[26] = {0};
        for(;e < s.size(); ++ e){
            maxCount = max(maxCount, ++ dict[s[e] - 'A']);
            if(maxCount + k <= e - b){
                dict[s[b ++] - 'A'] --;
            }
        }
        return s.size() - b;
    }
};
