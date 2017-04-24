/*
描述
给定一个长度为 n 的非负整数序列 a[1..n]

你需要求有多少个非负整数 S 满足以下两个条件：

(1).0 ≤ S < 260

(2).对于所有 1 ≤ i < n ，有 (a[i] xor S) ≤ (a[i+1] xor S)

输入
第一行一个正整数 n

第二行 n 个非负整数表示序列 a[1..n]

1 ≤ n ≤ 50

0 ≤ a[i] < 260

输出
一个非负正数，表示答案

样例输入
3
1 2 3
样例输出
288230376151711744
*/

#include <iostream>
using namespace std;
typedef long long LL;
#define bits(x) __buildin_popcount(x)
const LL INF = (1LL << 61) - 1LL;

LL highest_one_bit(LL n){ // 取最高位1
    n |= (n >> 1);
    n |= (n >> 2);
    n |= (n >> 4);
    n |= (n >> 8);
    n |= (n >> 16);
    n |= (n >> 32);
    return n ^ (n >> 1);
}

LL count_bits(LL x){
    x = (x & 0x5555555555555555) + ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x & 0x0F0F0F0F0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F0F0F0F0F);
    x = (x & 0x00FF00FF00FF00FF) + ((x >> 8) & 0x00FF00FF00FF00FF);
    x = (x & 0x0000FFFF0000FFFF) + ((x >> 16) & 0x0000FFFF0000FFFF);
    x = (x & 0x00000000FFFFFFFF) + ((x >> 32) & 0x00000000FFFFFFFF);
    return x;
}

int main(){
    int n;
    cin >> n;
    LL prev = 0, next = 0, hob = 0, flag = 0, res = 0; // flag表示这一位是1是0, res表示总共有哪些位考虑了。
    cin >> prev;
    for(int i = 1;i < n; ++ i){
        cin >> next;
        hob = highest_one_bit(prev ^ next);
        if(!hob) continue;
        if((res & hob) && (((flag & hob) == 0) ^ (next > prev))){ // 这一位之前就需要考虑并且与当前考虑相悖
            cout << 0 << "\n";
            return 0;
        }
        res |= hob;
        if(next > prev) flag &= (hob ^ INF);
        else flag |= hob;
        prev = next;
    }
    cout << (1LL << (60LL - count_bits(res))) << "\n";
    return 0;
}
