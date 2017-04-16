/*
描述
主宰尤涅若拥有一招非常厉害的招式——剑刃风暴，“无论是战士还是法师，都害怕尤涅若的武士刀剑技”。

现在战场上有N名敌对英雄，他们的位置分别为(Xi, Yi)，而剑刃风暴的伤害范围是一个半径为R的圆形，尤涅若可以选择一个坐标作为剑刃风暴的中心，所有处于这个圆形范围内的英雄都会受到剑刃风暴的伤害。

现在尤涅若想要知道，他的剑刃风暴最多可以同时伤害到多少敌对英雄。

输入
第一行为两个整数N和R，分别敌对英雄的数量以及剑刃风暴的半径。

接下来的N行，每行两个整数Xi和Yi，描述一个英雄的坐标。

对于30%的数据，满足1<=N<=10

对于60%的数据，满足1<=N<=100

对于100%的数据，满足1<=N<=2000, 0<=Xi, Yi<=108, 1<=R<=108，可能有两名英雄的坐标是相同的。

输出
输出一行Ans，表示尤涅若的剑刃风暴最多能够伤害到的英雄数量。

样例输入
10 2
0 10
0 10
9 10
1 2
4 5
8 8
8 4
4 2
7 7
0 7
样例输出
3
*/

// O(n^3)做法:注意到覆盖点数最多的圆必定经过两个点(如果不经过可以移动使之经过且不影响结果),所以可以O(n^2)遍历这两个点,O(n)验证其他点是否在这两个点所确定的圆内。
// O(n^2logn)做法:根据上述所讲优化而来,固定一个点，则遍历另一点时候可以确定这两点所定的圆心的区间，用类似扫描线的方法进行统计。

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

const double eps = 1e-8;

struct Point {
    double x, y;
    Point(){x = y = 0;};
    double operator/(const Point &a) const{return sqrt((x - a.x) * (x - a.x) + (y - a.y)*(y - a.y));};
};

struct Angle {
    double angle;
    bool in;
    Angle(){angle = 0; in = false;};
    Angle(double _a, bool _i){angle = _a; in = _i;};
    bool operator<(const Angle &a) const {return angle == a.angle ? in > a.in : angle < a.angle;};
};

int max_circle_cover(const vector<Point> &pts, const double &r){
    int ans = 0, cnt = 0;
    double dist = 0, angle = 0, phi = 0;
    vector<Angle> arg;
    for(int i = 0;i < pts.size(); ++ i){
        arg.clear();
        for(int j = 0;j < pts.size(); ++ j){
            if(i == j) continue;
            dist = pts[i] / pts[j];
            if(dist > 2 * r) continue;
            if(fabs(dist) < eps) {cnt ++; continue;};
            angle = atan2(pts[j].y - pts[i].y, pts[j].x - pts[i].x);
            phi = acos(dist * 0.5 / r);
            arg.emplace_back(angle - phi, 1);
            arg.emplace_back(angle + phi, 0);
        }
        sort(arg.begin(), arg.end());
        cnt = 1;
        for(int i = 0;i < arg.size(); ++ i){
            if(arg[i].in) ++ cnt;
            else -- cnt;
            ans = max(ans, cnt);
        }
    }
    return ans;
}

int main(){
    int n, r;
    cin >> n >> r;
    vector<Point> pts(n);
    for(int i = 0;i < n; ++ i)
        cin >> pts[i].x >> pts[i].y;
    cout << max_circle_cover(pts, r) << endl;
    return 0;
}
