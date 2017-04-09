/*
描述
There are N queens in an infinite chessboard. We say two queens may attack each other if they are in the same vertical line, horizontal line or diagonal line even if there are other queens sitting between them.

Now given the positions of the queens, find out how many pairs may attack each other?

输入
The first line contains an integer N.

Then N lines follow. Each line contains 2 integers Ri and Ci indicating there is a queen in the Ri-th row and Ci-th column.  

No two queens share the same position.  

For 80% of the data, 1 <= N <= 1000

For 100% of the data, 1 <= N <= 100000, 0 <= Ri, Ci <= 1000000000

输出
One integer, the number of pairs may attack each other.

样例输入
5  
1 1  
2 2  
3 3   
1 3
3 1
样例输出
10
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
long long C(long long x){
    return x * (x - 1) / 2;
}
int main(){
    long long n, x, y, res;
    scanf("%lld", &n);
    unordered_map<long long, long long> row, col, pos, neg;
    while(n --){
        scanf("%lld%lld", &x, &y);
        row[x] += 1;
        col[y] += 1;
        pos[x + y] += 1;
        neg[x - y] += 1;
    }
    res = 0;
    for(auto p : row)
        res += C(p.second);
    for(auto p : col)
        res += C(p.second);
    for(auto p : pos)
        res += C(p.second);
    for(auto p : neg)
        res += C(p.second);
    printf("%lld\n", res);
    return 0;
}
