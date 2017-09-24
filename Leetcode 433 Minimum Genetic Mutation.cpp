/*
A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to "end"), where ONE mutation is defined as ONE single character changed in the gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations. A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the minimum number of mutations needed to mutate from "start" to "end". If there is no such a mutation, return -1.

Note:

Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be valid.
You may assume start and end string is not the same.
Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1
Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2
Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3
*/

class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        queue<string> q;
        unordered_set<string> udst(bank.begin(), bank.end());
        int dist = 0, n = 0;
        if(udst.count(end) == 0) return -1;
        q.push(start);
        while(!q.empty()){
            n = q.size();
            for(int i = 0;i < n; ++ i){
                string str = q.front();
                q.pop();
                if(str == end) return dist;
                for(int i = 0;i < str.size(); ++ i){
                    char tmp = str[i];
                    for(char c : "ACGT"){
                        if(str[i] == c) continue;
                        str[i] = c;
                        if(udst.count(str)){
                            q.push(str);
                            udst.erase(str);
                        }
                    }
                    str[i] = tmp;
                }
            }
            dist ++;
        }
        return -1;
    }
};
