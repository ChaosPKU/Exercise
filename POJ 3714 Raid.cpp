/*
Description

After successive failures in the battles against the Union, the Empire retreated to its last stronghold. Depending on its powerful defense system, the Empire repelled the six waves of Union's attack. After several sleepless nights of thinking, Arthur, General of the Union, noticed that the only weakness of the defense system was its energy supply. The system was charged by N nuclear power stations and breaking down any of them would disable the system.

The general soon started a raid to the stations by N special agents who were paradroped into the stronghold. Unfortunately they failed to land at the expected positions due to the attack by the Empire Air Force. As an experienced general, Arthur soon realized that he needed to rearrange the plan. The first thing he wants to know now is that which agent is the nearest to any power station. Could you, the chief officer, help the general to calculate the minimum distance between an agent and a station?

Input

The first line is a integer T representing the number of test cases.
Each test case begins with an integer N (1 ≤ N ≤ 100000).
The next N lines describe the positions of the stations. Each line consists of two integers X (0 ≤ X ≤ 1000000000) and Y (0 ≤ Y ≤ 1000000000) indicating the positions of the station.
The next following N lines describe the positions of the agents. Each line consists of two integers X (0 ≤ X ≤ 1000000000) and Y (0 ≤ Y ≤ 1000000000) indicating the positions of the agent. 　

Output

For each test case output the minimum distance with precision of three decimal placed in a separate line.

Sample Input

2
4
0 0
0 1
1 0
1 1
2 2
2 3
3 2
3 3
4
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
Sample Output

1.414
0.000
*/

//分治
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

int T, N;
const double maxdis = 1e11;

struct Point{
    double x, y;
    bool flag;
}p[200010], t[100010];

double getDistance(const Point &a, const Point &b){
    if(a.flag == b.flag) return maxdis;
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

bool compare(const Point &a, const Point &b){
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool compare_y(const Point &a, const Point &b){
    return a.y < b.y;
}

double solve(Point *points, int b, int e){
    if(b == e) return maxdis;
    if(b + 1 == e) return getDistance(points[b], points[e]);
    int m = b + (e - b) / 2;
    double res = min(solve(points, b, m), solve(points, m + 1, e));
    
    int tc = 0;
    for(int i = b;i <= e; ++ i)
        if(fabs(points[m].x - points[i].x) < res)
            t[tc ++] = points[i];
    
    sort(t, t + tc, compare_y);
    for(int i = 0;i < tc - 1; ++ i)
        for(int j = i + 1;j < tc && t[j].y - t[i].y < res; ++ j)
            res = min(res, getDistance(t[i], t[j]));
    return res;
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &N);
        for(int i = 0;i < N; ++ i){
            scanf("%lf%lf", &p[i].x, &p[i].y);
            p[i].flag = 0;
        }
        for(int i = N;i < 2 * N; ++ i){
            scanf("%lf%lf", &p[i].x, &p[i].y);
            p[i].flag = 1;
        }
        
        sort(p, p + 2 * N, compare);
        printf("%.3f\n", solve(p, 0, 2 * N - 1));
    }
    return 0;
}

//这个应该不对 但居然也能过
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

int T, N;
const double maxdis = 1e11;

struct Point{
    double x, y;
    bool flag;
}p[200010];

double getDistance(const Point &a, const Point &b){
    if(a.flag == b.flag) return maxdis;
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

bool compare(const Point &a, const Point &b){
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

double solve(Point *points, int b, int e){
    if(b == e) return 0;
    if(b + 1 == e) return getDistance(points[b], points[e]);
    int m = b + (e - b) / 2;
    double res = min(solve(points, b, m), solve(points, m, e));
    for(int i = m - 1;i >= b && points[m].x - points[i].x < res; -- i)
        for(int j = m + 1; j <= e && points[j].x - points[m].x < res && fabs(points[i].y - points[j].y) < res; ++ j)
            res = min(res, getDistance(points[i], points[j]));
    return res;
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &N);
        for(int i = 0;i < N; ++ i){
            scanf("%lf%lf", &p[i].x, &p[i].y);
            p[i].flag = 0;
        }
        for(int i = N;i < 2 * N; ++ i){
            scanf("%lf%lf", &p[i].x, &p[i].y);
            p[i].flag = 1;
        }
        
        sort(p, p + 2 * N, compare);
        printf("%.3f\n", solve(p, 0, 2 * N - 1));
    }
    return 0;
}

//略暴力的做法
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

int T, N;

struct Point{
    double x, y;
}p[2][100010];

double getDistance(const Point &a, const Point &b){
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

bool compare(const Point &a, const Point &b){
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

int main(){
    scanf("%d", &T);
    while(T --){
        double res = 1e11;
        scanf("%d", &N);
        for(int i = 0;i < N; ++ i)
            scanf("%lf%lf", &p[0][i].x, &p[0][i].y);
        for(int i = 0;i < N; ++ i)
            scanf("%lf%lf", &p[1][i].x, &p[1][i].y);
        
        sort(p[0], p[0] + N, compare);
        sort(p[1], p[1] + N, compare);
        
        int t = (int)(lower_bound(p[1], p[1] + N + 1, p[0][0], compare) - p[1]);
        for(int i = 0;i < N; ++ i){
            while(t < N && compare(p[1][t + 1], p[0][i])) ++ t;
            for(int j = t; j < N; ++ j){
                if(fabs(p[0][i].x - p[1][j].x) > res) break;
                res = min(res, getDistance(p[0][i], p[1][j]));
            }
            for(int j = t - 1; j >= 0; -- j){
                if(fabs(p[0][i].x - p[1][j].x) > res) break;
                res = min(res, getDistance(p[0][i], p[1][j]));
            }
        }
        printf("%.3f\n", res);
    }
    return 0;
}
