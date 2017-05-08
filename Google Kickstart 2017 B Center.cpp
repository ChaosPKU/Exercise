/*
Problem

There are N weighted points in a plane. Point i is at (Xi, Yi) and has weight Wi.

In this problem, we need to find a special center of these points. The center is a point (X, Y) such that the sum of max(|X-Xi|, |Y-Yi|)*Wi is minimum.

Input

The input starts with one line containing exactly one integer T, which is the number of test cases. T test cases follow.

Each test case begins with one line containing one integer N. N lines follow. Each line contains three space-separated real numbers Xi, Yi, and Wi. Xi, Yi and Wi have exactly 2 digits after the decimal point.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the sum of max(|X-Xi|, |Y-Yi|)*Wi for center (X, Y).

y will be considered correct if it is within an absolute or relative error of 10-6 of the correct answer. See the FAQ for an explanation of what that means, and what formats of real numbers we accept.

Limits

1 ≤ T ≤ 10.
-1000.00 ≤ Xi ≤ 1000.00.
-1000.00 ≤ Yi ≤ 1000.00.
Small dataset

1 ≤ N ≤ 100;
Wi = 1.0, for all i.
Large dataset

1 ≤ N ≤ 10000;
1.0 ≤ Wi ≤ 1000.0, for all i.
Sample


Input 
 
3
2
0.00 0.00 1.00
1.00 0.00 1.00
4
1.00 1.00 1.00
1.00 -1.00 1.00
-1.00 1.00 1.00
-1.00 -1.00 1.00
2
0.00 0.00 1.00
1.00 0.00 2.00
 	
Output 

Case #1: 1.0
Case #2: 4.0
Case #3: 1.0
*/

// 曼哈顿距离   Manhattan = |x1 - x2| + |y1 - y2|;
// 切比雪夫距离 Chebyshev = max(|x1 - x2|, |y1 - y2|);
// 画出距离一个点的曼哈顿距离为1的等距线和切比雪夫距离为1的等距线,发现前者旋转45度后再放大sqrt(2)倍即为后者，所以可以对点进行旋转放缩变换，完成两个距离的等价变化。
// 一个点以坐标原点为中心逆时针旋转a度，得到的新点为 (x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
// 大数据需要求带权中位数,求法是 加上这个数的权后权值和恰不小于总权的一半，这个数就是带权中位数。

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

struct node{
    double x, y, w;
    node(){x = y = w = 0;}
    node(double _x, double _y, double _w){
        x = _x;
        y = _y;
        w = _w;
    }
    double operator-(const node &a) const{
        return fabs(x - a.x) + fabs(y - a.y);
    }
};

bool cmp_x(const node &a, const node &b){
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool cmp_y(const node &a, const node &b){
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}

inline void rotate(node &n){
    double tmp = n.x;
    n.x = (n.x - n.y) / 2;
    n.y = (tmp + n.y) / 2;
}

int main(){
    freopen("/Users/Apple/Downloads/B-large-practice.in.txt", "r", stdin);
    freopen("/Users/Apple/Downloads/C-large.out.txt", "w", stdout);
    
    int T, N, i, t;
    double sum, cnt, res;
    cin >> T;
    for(t = 1;t <= T; ++ t){
        cin >> N;
        res = sum = 0;
        
        vector<node> vtr(N);
        node center;
        for(i = 0;i < N; ++ i){
            cin >> vtr[i].x >> vtr[i].y >> vtr[i].w;
            rotate(vtr[i]);
            sum += vtr[i].w;
        }
        
        cnt = 0;
        sort(vtr.begin(), vtr.end(), cmp_x);
        for(i = 0;i < N; ++ i)
            if(cnt < sum / 2 && (cnt += vtr[i].w) >= sum / 2)
                break;
        center.x = vtr[i].x;
        
        cnt = 0;
        sort(vtr.begin(), vtr.end(), cmp_y);
        for(i = 0;i < N; ++ i)
            if(cnt < sum / 2 && (cnt += vtr[i].w) >= sum / 2)
                break;
        center.y = vtr[i].y;
        
        for(i = 0;i < N; ++ i)
            res += (vtr[i] - center) * vtr[i].w;
        cout << std::fixed << "Case #" << t << ": " << res << endl;
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
