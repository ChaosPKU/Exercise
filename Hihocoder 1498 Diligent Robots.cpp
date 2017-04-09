/*
描述
There are N jobs to be finished. It takes a robot 1 hour to finish one job.

At the beginning you have only one robot. Luckily a robot may build more robots identical to itself. It takes a robot Q hours to build another robot.  

So what is the minimum number of hours to finish N jobs?

Note two or more robots working on the same job or building the same robot won't accelerate the progress.

输入
The first line contains 2 integers, N and Q.  

For 70% of the data, 1 <= N <= 1000000  

For 100% of the data, 1 <= N <= 1000000000000, 1 <= Q <= 1000

输出
The minimum number of hours.

样例输入
10 1
样例输出
5
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
using namespace std;
int main(){
    long long n, q, res;
    scanf("%lld%lld", &n, &q);
    int x = max((int)log2(n / q), 0);
    res = x * q + ceil(n / pow(2., x));
    printf("%lld\n", res);
    return 0;
}
