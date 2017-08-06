/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
Little Ho has a string S consisting of only lowercase letters.

All letters in S are distinct except for 'm', 's', 'f' and 't'. Which means the four magical letters 'm', 's', 'f' and 't' can show up at most twice, while other letters can show up at most once.

Now little Ho wants to change S into T by swapping a pair of letters in S.

He wants to know the minimum amounts of such swaps he needs to do so.

输入
The first line contains an integer N, indicating the number of test cases.

Each test case contains two lines. The first contains the string S and the second contains the string T.

It is guaranteed that changing S into T is possible.

For 30% of the data, 1 ≤ length(S) == length(T) ≤ 10.

For 100% of the data, 1 ≤ N ≤ 10, 1 ≤ length(S) == length(T) ≤ 30.

输出
For each test case output the minimum amounts of swaps needed to turn S into T on a separate line.

样例输入
2
msra
asmr
fsmambfcs
mfsmbfcsa
样例输出
2
6
*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

void calc(vector<int> &vtr, int &ret){
    int n = (int)vtr.size(), res = 0;
    vector<bool> flags(n, 0);
    for(int i = 0;i < n; ++ i){
        if(flags[i]) continue;
        int cnt = 0, t = vtr[i];
        flags[i] = 1;
        while(!flags[t]){
            flags[t] = 1;
            t = vtr[t];
            ++ cnt;
        }
        res += cnt;
    }
    ret = min(ret, res);
}

int main()
{
    int N, res;
    string s, t;
    cin >> N;
    for(int n = 0;n < N; ++ n){
        res = 99999;
        cin >> s >> t;
        unordered_map<int, set<int>> udmp;
        for(int i = 0; i < t.size(); ++ i)
            udmp[t[i]].insert(i);
        vector<int> nums(s.size());
        for(int i = 0;i < s.size(); ++ i){
            nums[i] = *udmp[s[i]].begin();
            udmp[s[i]].erase(udmp[s[i]].begin());
        }
        vector<vector<int>> vtr(4);
        for(int i = 0;i < s.size(); ++ i){
            if(s[i] == 'm') vtr[0].push_back(i);
            if(s[i] == 's') vtr[1].push_back(i);
            if(s[i] == 'f') vtr[2].push_back(i);
            if(s[i] == 't') vtr[3].push_back(i);
        }
        for(int i = 1; i < 16; ++ i){ //这边可以再优化，暂时来不及写了
            bool flag = false;
            vector<int> tmp(nums.begin(), nums.end());
            for(int j = 0;j < 4; ++ j){
                if(((i >> j) & 1) && vtr[j].size() == 2){
                    swap(tmp[vtr[j][0]], tmp[vtr[j][1]]);
                    flag = true;
                }
            }
            if(flag)
                calc(tmp, res);
        }
        calc(nums, res);
        cout << res << endl;
    }
}
