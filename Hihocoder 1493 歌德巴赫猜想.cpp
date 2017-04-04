/*
描述
哥德巴赫猜想认为“每一个大于2的偶数，都能表示成两个质数之和”。

给定一个大于2的偶数N，你能找到两个质数P和Q满足P<=Q并且P+Q=N吗？

输入
一个偶数N(4 <= N <= 1000000)

输出
输出P和Q。如果有多组解，输出P最小的一组。

样例输入
10
样例输出
3 7
*/

#include <iostream>
#include <math.h>
#include <memory.h>
using namespace std;

bool primes[1000005];

int main(){
    int N;
    cin >> N;
    memset(primes, 0, sizeof(primes));
    
    for(int i = 2; i <= sqrt(N - 1); ++ i){
        if(primes[i] == 1) continue;
        for(int j = i; i * j < N; ++ j)
            primes[i * j] = 1;
    }
    
    for(int i = 2; i <= N / 2; ++ i)
        if(!primes[i] && !primes[N - i]){
            cout << i << " " << N - i << endl;
            return 0;
        }
}
