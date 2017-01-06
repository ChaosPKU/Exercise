/*
Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.

Note:

A word cannot be split into two lines.
The order of words in the sentence must remain unchanged.
Two consecutive words in a line must be separated by a single space.
Total words in the sentence won't exceed 100.
Length of each word is greater than 0 and won't exceed 10.
1 ≤ rows, cols ≤ 20,000.
Example 1:

Input:
rows = 2, cols = 8, sentence = ["hello", "world"]

Output: 
1

Explanation:
hello---
world---

The character '-' signifies an empty space on the screen.
Example 2:

Input:
rows = 3, cols = 6, sentence = ["a", "bcd", "e"]

Output: 
2

Explanation:
a-bcd- 
e-a---
bcd-e-

The character '-' signifies an empty space on the screen.
Example 3:

Input:
rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]

Output: 
1

Explanation:
I-had
apple
pie-I
had--

The character '-' signifies an empty space on the screen.
*/

class Solution {
public:
    int calc(vector<string>& sentence, int i, int cols, int res){
        int n = sentence.size();
        while((cols -= sentence[(++ i) %  n].size()) >= 0){
            res += 1;
            cols -= 1;
        }
        return res;
    }
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        unordered_map<int, int> udmp;
        int n = sentence.size(), rptr = 0, ptr = 0, tot = -1, start = 0;
        for(string s : sentence){
            tot += 1 + s.size();
            if(s.size() > cols) return 0;
        }
        int len = ((cols + 1) / (tot + 1));
        cols = cols - tot * len - len;
        len *= n;
        while(rptr < rows){
            start = ptr % n;
            if(start == 0 && ptr != 0){
                int tmp = rows / rptr;
                ptr *= tmp;
                rptr *= tmp;
                if(rptr >= rows) break;
            }
            if(udmp[start] == 0)
                udmp[start] = calc(sentence, start, cols, len); //记忆化搜索
            ptr = ptr + udmp[start];
            ++ rptr;
        }
        return ptr / n;
    }
};
