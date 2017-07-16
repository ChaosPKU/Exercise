/*
Problem

When you travel, you like to spend time sightseeing in as many cities as possible, but sometimes you might not be able to because you need to catch the bus to the next city. To maximize your travel enjoyment, you decide to write a program to optimize your schedule.

You begin at city 1 at time 0 and plan to travel to cities 2 to N in ascending order, visiting every city. There is a bus service from every city i to the next city i + 1. The i-th bus service runs on a schedule that is specified by 3 integers: Si, Fi and Di, the start time, frequency and ride duration. Formally, this means that there is a bus leaving from city i at all times Si + xFi, where x is an integer and x ≥ 0, and the bus takes Di time to reach city i + 1.

At each city between 1 and N - 1, inclusive, you can decide to spend Ts time sightseeing before waiting for the next bus, or you can immediately wait for the next bus. You cannot go sightseeing multiple times in the same city. You may assume that boarding and leaving buses takes no time. You must arrive at city N by time Tf at the latest. (Note that you cannot go sightseeing in city N, even if you arrive early. There's nothing to see there!)

What is the maximum number of cities you can go sightseeing in?

Input

The input starts with one line containing one integer T, which is the number of test cases. T test cases follow.

Each test case begins with a line containing 3 integers, N, Ts and Tf, representing the number of cities, the time taken for sightseeing in any city, and the latest time you can arrive in city N.

This is followed by N - 1 lines. On the i-th line, there are 3 integers, Si, Fi and Di, indicating the start time, frequency, and duration of buses travelling from city i to city i + 1.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum number of cities you can go sightseeing in such that you can still arrive at city N by time Tf at the latest. If it is impossible to arrive at city N by time Tf, output Case #x: IMPOSSIBLE.

Limits

1 ≤ T ≤ 100.
Small dataset

2 ≤ N ≤ 16.
1 ≤ Si ≤ 5000.
1 ≤ Fi ≤ 5000.
1 ≤ Di ≤ 5000.
1 ≤ Ts ≤ 5000.
1 ≤ Tf ≤ 5000.
Large dataset

2 ≤ N ≤ 2000.
1 ≤ Si ≤ 109.
1 ≤ Fi ≤ 109.
1 ≤ Di ≤ 109.
1 ≤ Ts ≤ 109.
1 ≤ Tf ≤ 109.
Sample


Input 
 	
Output 
 
4
4 3 12
3 2 1
6 2 2
1 3 2
3 2 30
1 2 27
3 2 1
4 1 11
2 1 2
4 1 5
8 2 2
5 10 5000
14 27 31
27 11 44
30 8 20
2000 4000 3

Case #1: 2
Case #2: 0
Case #3: IMPOSSIBLE
Case #4: 4


In the first test case, you can go sightseeing in city 1, catching the bus leaving at time 3 and arriving at time 4. You can go sightseeing in city 2, leaving on the bus at time 8. When you arrive in city 3 at time 10 you immediately board the next bus and arrive in city 4 just in time at time 12.
*/

// DP[i][j]表示离开城市i时已经观光了j个城市的最小可行时间

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

typedef long long LL;

int main(){
    freopen("/Users/Apple/Downloads/A-large.in", "r", stdin);
    freopen("/Users/Apple/Downloads/A-large.out", "w", stdout);
    
    LL T, N, i, j, t, res, Ts, Tf, time, x, time1, time2;
    cin >> T;
    for(t = 1;t <= T; ++ t){
        cin >> N >> Ts >> Tf;
        vector<vector<LL>> vtr(N - 1, vector<LL>(3, 0));
        vector<vector<LL>> DP(N - 1, vector<LL>(N, 0));
        time = 0;
        for(i = 0; i < N - 1; ++ i){
            cin >> vtr[i][0] >> vtr[i][1] >> vtr[i][2];
            x = 0;
            if(time > vtr[i][0]) x = (LL)(ceil(((double)time - vtr[i][0]) / vtr[i][1]));
            time = vtr[i][0] + x * vtr[i][1];
            DP[i][0] = time;
            time += vtr[i][2];
        }
        if(Tf < time){
            cout << std::fixed << "Case #" << t << ": IMPOSSIBLE" << endl;
            continue;
        }
        
        res = 0;
        
        time = Ts;
        x = 0;
        if(time > vtr[0][0]) x = (LL)(ceil(((double)time - vtr[0][0]) / vtr[0][1]));
        DP[0][1] = vtr[0][0] + x * vtr[0][1];
        
        for(i = 1; i < N - 1; ++ i)
            for(j = 1; j <= i + 1; ++ j){
                time1 = DP[i - 1][j - 1] + Ts + vtr[i - 1][2];
                x = 0;
                if(time1 > vtr[i][0]) x = (LL)(ceil(((double)time1 - vtr[i][0]) / vtr[i][1]));
                time1 = vtr[i][0] + x * vtr[i][1];
                if(j == i + 1){
                    DP[i][j] = time1;
                    continue;
                }
                
                time2 = DP[i - 1][j] + vtr[i - 1][2];
                x = 0;
                if(time2 > vtr[i][0]) x = (LL)(ceil(((double)time2 - vtr[i][0]) / vtr[i][1]));
                time2 = vtr[i][0] + x * vtr[i][1];
                DP[i][j] = min(time1, time2);
            }
        
        for(j = 0; j < N; ++ j){
            if(DP[N - 2][j] + vtr[N - 2][2] <= Tf)
                res = j;
        }
        
        cout << std::fixed << "Case #" << t << ": " << res << endl;
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
