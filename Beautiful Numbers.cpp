/*
Problem

We consider a number to be beautiful if it consists only of the digit 1 repeated one or more times. Not all numbers are beautiful, but we can make any base 10 positive integer beautiful by writing it in another base.

Given an integer N, can you find a base B (with B > 1) to write it in such that all of its digits become 1? If there are multiple bases that satisfy this property, choose the one that maximizes the number of 1 digits.

Input

The first line of the input gives the number of test cases, T. T test cases follow. Each test case consists of one line with an integer N.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the base described in the problem statement.

Limits

1 ≤ T ≤ 100.
Small dataset

3 ≤ N ≤ 1000.
Large dataset

3 ≤ N ≤ 1018.
Sample


Input 
    
Output 
 
2
3
13

Case #1: 2
Case #2: 3

In case #1, the optimal solution is to write 3 as 11 in base 2.

In case #2, the optimal solution is to write 13 as 111 in base 3. Note that we could also write 13 as 11 in base 12, but neither of those representations has as many 1s.
*/
// N-1必定符合要求，剩下的只能靠遍历Check。但值得注意的是并不需要遍历1~N-2,数值越大满足条件的数值越稀疏，可以手动筛选。
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int T;
long long N, res;
bool check(long long N, long long i){
    while(N != 0){
        if(N % i != 1)
            return false;
        N /= i;
    }
    return true;
}
int main(){
    freopen("/Users/Apple/Downloads/B-large-practice.in.txt", "r", stdin);
    freopen("/Users/Apple/Downloads/A-large-practice.out.txt", "w", stdout);
    scanf("%d", &T);
    for(int k = 1;k <= T; ++ k){
        res = -1;
        scanf("%lld", &N);
        long long i = 2;
        for(; i <= (int)pow(N, 1.0/3); ++ i){
            if(check(N, i)){
                res = i;
                break;
            }
        }
        if(res == -1){
            i = (int)pow(N, 0.5);
            if(check(N, i))
                res = i;
            else res = N - 1;
        }

        printf("Case #%d: %lld\n", k, res);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}

// Leetcode 483 Smallest Good Base

class Solution {
public:
    bool check(long long n, long long &i){
        while(n){
            if(n % i != 1) return false;
            n /= i;
        }
        return true;
    }
    string smallestGoodBase(string n) {
        long long num = stol(n), cnt = 1, i = 0;
        while(++ cnt){
            i = (int)pow(num, 1.0/cnt);
            if(i == 1) return to_string(num - 1);
            if(check(num, i)) return to_string(i);
        }
    }
};
