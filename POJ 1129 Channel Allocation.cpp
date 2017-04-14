/*
Description

When a radio station is broadcasting over a very large area, repeaters are used to retransmit the signal so that every receiver has a strong signal. However, the channels used by each repeater must be carefully chosen so that nearby repeaters do not interfere with one another. This condition is satisfied if adjacent repeaters use different channels. 

Since the radio frequency spectrum is a precious resource, the number of channels required by a given network of repeaters should be minimised. You have to write a program that reads in a description of a repeater network and determines the minimum number of channels required.
Input

The input consists of a number of maps of repeater networks. Each map begins with a line containing the number of repeaters. This is between 1 and 26, and the repeaters are referred to by consecutive upper-case letters of the alphabet starting with A. For example, ten repeaters would have the names A,B,C,...,I and J. A network with zero repeaters indicates the end of input. 

Following the number of repeaters is a list of adjacency relationships. Each line has the form: 

A:BCDH 

which indicates that the repeaters B, C, D and H are adjacent to the repeater A. The first line describes those adjacent to repeater A, the second those adjacent to B, and so on for all of the repeaters. If a repeater is not adjacent to any other, its line has the form 

A: 

The repeaters are listed in alphabetical order. 

Note that the adjacency is a symmetric relationship; if A is adjacent to B, then B is necessarily adjacent to A. Also, since the repeaters lie in a plane, the graph formed by connecting adjacent repeaters does not have any line segments that cross. 
Output

For each map (except the final one with no repeaters), print a line containing the minumum number of channels needed so that no adjacent channels interfere. The sample output shows the format of this line. Take care that channels is in the singular form when only one channel is required.
Sample Input

2
A:
B:
4
A:BC
B:ACD
C:ABD
D:BC
4
A:BCD
B:ACD
C:ABD
D:ABC
0
Sample Output

1 channel needed.
3 channels needed.
4 channels needed. 
Source

Southern African 2001
*/

#include <iostream>
#include <vector>
using namespace std;
void DFS(vector<vector<int> > &lnklst, vector<int> &colors, int &res, int &counter, int n){
    if(n == lnklst.size()){
        res = min(res, counter + 1);
        return;
    }
    int choices[4] = {0, 1, 2, 3};  // 相邻点染过的色从选择中去掉;
    for(int i = 0;i < lnklst[n].size(); ++ i){
        if(colors[lnklst[n][i]] != -1)
            choices[colors[lnklst[n][i]]] = -1;
    }
    int tmp = counter;
    for(int i = 0;i < res; ++ i){   // 剪枝, 不会选择超过已经算出的res(已知最多合法颜色种类)的颜色
        if(choices[i] != -1){
            colors[n] = i;
            counter = max(counter, i);
            DFS(lnklst, colors, res, counter, n + 1);
        }
    }
    colors[n] = -1;
    counter = tmp;
}
int main(){
    int n, counter, res;
    string s = "";
    while(cin >> n){
        if(!n) break ;
        vector<vector<int> > lnklst(n);
        vector<int> colors(n, -1);
        for(int i = 0;i < n; ++ i){
            cin >> s;
            for(int j = 2;j < s.size(); ++ j)
                lnklst[s[0] - 'A'].push_back(s[j] - 'A');
        }
        res = 4; // 四色定理
        counter = 0;
        DFS(lnklst, colors, res, counter, 0);
        cout << res << " channel" << (res == 1 ? "" : "s") << " needed." << endl;
    }
    return 0;
}
