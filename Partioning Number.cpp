/*
Problem

Shekhu has N balls. She wants to distribute them among one or more buckets in a way that satisfies all of these constraints:

The numbers of balls in the buckets must be in non-decreasing order when read from left to right.
The leftmost bucket must be non-empty and the number of balls in the leftmost bucket must be divisible by D.
The difference (in number of balls) between any two buckets (not just any two adjacent buckets) must be less than or equal to 2.
How many different ways are there for Shekhu to do this? Two ways are considered different if the lists of numbers of balls in buckets, reading left to right, are different.

Input

The first line of the input gives the number of test cases, T.
T test cases follow. Each test case consists of one line with two integers N and D, as described above.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the answer, as described above.

Limits

1 ≤ T ≤ 100.
1 ≤ D ≤ 100.
Small dataset

1 ≤ N ≤ 2000.
Large dataset

1 ≤ N ≤ 105.
Sample


Input 
    
Output 
 
3
7 1
7 2
2 4
Case #1: 10
Case #2: 1
Case #3: 0
In sample case #1, the possible distributions are:

1 1 1 1 1 1 1
1 1 1 1 1 2
1 1 1 1 3
1 1 1 2 2
1 2 2 2
1 1 2 3
1 3 3
2 2 3
3 4
7
Note that 1 2 4 is not a valid distribution, since the difference between 1 and 4 is more than 2.

In sample case #2, the possible distributions are:

2 2 3
3 4 is not possible, since the first term is not divisible by 2.

In sample case #3, no possible arrangement exists.
*/
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int main() {
    freopen("/Users/Apple/Downloads/C-large.in.txt", "r", stdin);
    freopen("/Users/Apple/Downloads/C-large.out.txt", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long int n;
        int dd, ans = 0;
        cin >> n >> dd;
        for (int d = dd; d <= n; d += dd) {
            for (int k = ceil((n + 2)/(d + 2)); k <= ceil(n/d); k++) {
                long long int r = n - k * d;
                int kk = k - 1;
                if (r > kk * 2) continue;
                if (r <= kk) kk = r;
                ans += (kk - ceil(double(r) / 2) + 1);
            }
        }
        cout << "Case #" << tt << ": " << ans << endl;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}

/*
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
int T, D;
long long N, res;
void backtracking(long long tot, long long pre, long long fir, long long &res){
    if(tot < pre * 2){
        if(tot >= pre && tot - fir <= 2){
//            tmp.push_back(tot);
//            ans.push_back(tmp);
//            tmp.pop_back();
            ++ res;
        }
        return;
    }
    long long i = pre;
    for(; i - fir <= 2 && i * 2 <= tot; ++ i){
//        tmp.push_back(i);
        backtracking(tot - i, i, fir, res);
//        tmp.pop_back();
    }
    if(tot - fir <= 2 && tot >= pre){
//        tmp.push_back(tot);
//        ans.push_back(tmp);
//        tmp.pop_back();
        ++ res;
    }
}

int main(){
    freopen("/Users/Apple/Downloads/C-small-attempt0.in.txt", "r", stdin);
    freopen("/Users/Apple/Downloads/A-large-practice.out.txt", "w", stdout);
    scanf("%d", &T);
    for(int k = 1;k <= T; ++ k){
        res = 0;
        scanf("%lld%d", &N, &D);
//        vector<long long> tmp;
//        vector<vector<long long>> ans;
        if(D > N){
            printf("Case #%d: %lld\n", k, 0ll);
            continue;
        }
        for(int i = D;i <= N; i += D){
//            tmp.push_back(i);
            backtracking(N - i, i, i, res);
//            tmp.clear();
        }
        if(N % D == 0)
            ++ res;
//        for(int i = 0;i < ans.size(); ++ i){
//            for(int j = 0;j < ans[i].size(); ++ j)
//                cout << ans[i][j] << " " ;
//            cout << endl;
//        }
        
        printf("Case #%d: %lld\n", k, res);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
*/
