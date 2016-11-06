/*
Problem

Diwali is the festival of lights. To celebrate it, people decorate their houses with multi-color lights and burst crackers. Everyone loves Diwali, and so does Pari. Pari is very fond of lights, and has transfinite powers, so she buys an infinite number of red and blue light bulbs. As a programmer, she also loves patterns, so she arranges her lights by infinitely repeating a given finite pattern S.

For example, if S is BBRB, the infinite sequence Pari builds would be BBRBBBRBBBRB...

Blue is Pari's favorite color, so she wants to know the number of blue bulbs between the Ith bulb and Jth bulb, inclusive, in the infinite sequence she built (lights are numbered with consecutive integers starting from 1). In the sequence above, the indices would be numbered as follows:

B  B  R  B  B  B  R  B  B  B  R  B...
1  2  3  4  5  6  7  8  9  10 11 12
So, for example, there are 4 blue lights between the 4th and 8th positions, but only 2 between the 10th and 12th.

Since the sequence can be very long, she wrote a program to do the count for her. Can you do the same?

Input

The first line of the input gives the number of test cases, T. T test cases follow.
First line of each test case consists of a string S, denoting the initial finite pattern.
Second line of each test case consists of two space separated integers I and J, defined above.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is number of blue bulbs between the Ith bulb and Jth bulb of Pari's infinite sequence, inclusive.

Limits

1 ≤ T ≤ 100.
1 ≤ length of S ≤ 100.
Each character of S is either uppercase B or uppercase R.

Small dataset

1 ≤ I ≤ J ≤ 106.
Large dataset

1 ≤ I ≤ J ≤ 1018.
Sample


Input 
    
Output 
 
3
BBRB
4 8
BBRB
10 12
BR
1 1000000
Case #1: 4
Case #2: 2
Case #3: 500000
Cases #1 and #2 are explained above.

In Case #3, bulbs at odd indices are always blue, and bulbs at even indices are always red, so there are half a million blue bulbs between positions 1 and 106.
*/
#include <iostream>
#include <stdio.h>
using namespace std;
int t;
long long i, j, res;
string p;
long long count(string s, char c){
    long long res = 0;
    for(int i = 0;i < s.size(); ++ i)
        if(s[i] == c)
            ++ res;
    return res;
}
int main(){
    freopen("/Users/Apple/Downloads/A-large.in.txt", "r", stdin);
    freopen("/Users/Apple/Downloads/A-large-practice.out.txt", "w", stdout);
    scanf("%d", &t);
    for(int k = 1;k <= t; ++ k){
        res = 0;
        cin >> p;
        scanf("%lld%lld", &i, &j);
        -- i;
        -- j;
        long long plen = p.size();
        long long ix= i / plen, iy = i % plen;
        long long jx = j / plen, jy = j % plen;
        long long pcount = count(p, 'B');
        if(jx == ix)
            res = count(p.substr(iy, jy + 1), 'B');
        else{
            res = pcount * (jx - ix - 1) + count(p.substr(iy), 'B') + count(p.substr(0, jy + 1), 'B');
        }
        printf("Case #%d: %lld\n", k, res);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}