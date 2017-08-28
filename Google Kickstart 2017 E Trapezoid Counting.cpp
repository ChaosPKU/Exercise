/*
Problem

In this problem, we will consider a trapezoid to be a convex quadrilateral with exactly one pair of parallel sides. If the lengths of the two non-parallel sides are equal, we say the trapezoid is isosceles.

You have some wooden sticks of various lengths, and you need to pick exactly four of them to form the four sides of an isosceles trapezoid. How many different sets of four sticks will allow this? Even if two sticks have the same length, they are considered to be different sticks. Sticks could not be bended and broke into parts.

Input

The first line of the input gives the number of test cases, T. T test cases follow; each consists of two lines. The first line consists of one integer N, the number of sticks. The second line consists of N integers; the i-th of these, Li, represents the length of the i-th stick.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1), and y is the number of different sets of four sticks that can form an isosceles trapezoid, as described above.

Limits

1 ≤ T ≤ 100.
1 ≤ Li ≤ 109.
Small dataset

1 ≤ N ≤ 50.
Large dataset

1 ≤ N ≤ 5000.
Sample


Input 
 	
Output 
 
5
5
2 3 3 4 3
4
1 5 3 1
4
2 2 3 3
4
999999998 999999999 999999999 1000000000
9
3 4 1 4 2 5 3 1 3
Case #1: 5
Case #2: 0
Case #3: 0
Case #4: 1
Case #5: 73

In Sample Case #1, there are five ways to choose four out of the five given sticks, and any one of those five sets of four sticks can be used to form an isosceles trapezoid. 
In Sample Case #2, note that the set {1, 1, 3, 5} cannot form an isosceles trapezoid, even though two of its sticks are of equal length.
In Sample Case #3, note that the set {2, 2, 3, 3} can form a rectangle, but in this problem, a rectangle is not considered to be an isosceles trapezoid.
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <math.h>
#include <queue>
#include <math.h>
#include <map>
using namespace std;

typedef long long LL;

// 能构成等腰梯形的条件
bool check(LL a, LL b, LL c, LL d){
    return a == b && c != d && a + b > llabs(d - c);
}

int main(){
    freopen("/Users/Apple/Downloads/B-large.in", "r", stdin);
    freopen("/Users/Apple/Downloads/B-large.out", "w", stdout);
    
    int T, t, n, tmp, i;
    LL res = 0, cnt = 0;
    cin >> T;
    for(t = 1;t <= T; ++ t){
        cin >> n;
        res = 0;
        map<int, int> udi;
        map<int, int> udp;
        for(i = 0;i < n; ++ i){
            cin >> tmp;
            udi[tmp] ++;
        }
        
        auto it = udi.end(); -- it;
        tmp = it->first;
        udp[tmp] = it->second * (it->second - 1) / 2;
        while(true){
            if(it == udi.begin()) break;
            -- it;
            udp[it->first] = udi[it->first] * (udi[it->first] - 1) / 2 + udp[tmp];
            tmp = it->first;
        }
        
        for(it = udi.begin(); it != udi.end(); ++ it){
            auto jt = it;
            ++ jt;
            for(; jt != udi.end(); ++ jt){
                auto tt = udp.upper_bound((jt->first - it->first) / 2);
                tmp = cnt = 0;
                if(tt->first <= it->first){
                    res += (LL)it->second * jt->second * (tt->second - udi[it->first] * (udi[it->first] - 1) / 2 - udi[jt->first] * (udi[jt->first] - 1) / 2);
                    if(udi[it->first] > 2)
                        res += (LL)jt->second * udi[it->first] * (udi[it->first] - 1) * (udi[it->first] - 2) / 6;
                    if(udi[jt->first] > 2)
                        res += (LL)it->second * udi[jt->first] * (udi[jt->first] - 1) * (udi[jt->first] - 2) / 6;
                }
                else if(tt->first <= jt->first){
                    res += (LL)it->second * jt->second * (tt->second - udi[jt->first] * (udi[jt->first] - 1) / 2);
                    if(udi[jt->first] > 2)
                        res += (LL)it->second * udi[jt->first] * (udi[jt->first] - 1) * (udi[jt->first] - 2) / 6;
                }
                else{
                    res += (LL)it->second * jt->second * tt->second;
                }
            }
        }
        cout << std::fixed << "Case #" << t << ": " << res << endl;
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
