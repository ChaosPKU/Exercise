/*
描述
给定一个NxM的矩阵A和一个整数K，小Hi希望你能求出其中最大（元素数目最多）的子矩阵，并且该子矩阵中所有元素的和不超过K。

输入
第一行包含三个整数N、M和K。

以下N行每行包含M个整数，表示A。

对于40%的数据，1 <= N, M <= 10  

对于100%的数据，1 <= N, M <= 250 1 <= K <= 2147483647 1 <= Aij <= 10000

输出
满足条件最大的子矩阵所包含的元素数目。如果没有子矩阵满足条件，输出-1。

样例输入
3 3 9
1 2 3  
2 3 4  
3 4 5
样例输出
4
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int grid[255][255], sum[255][255];
long long vtr[255], rsum[255];

int main(){
    int n, m, k, t, b, e, r = -1;
    cin >> n >> m >> k;
    for(int i = 1;i <= n; ++ i){
        for(int j = 1;j <= m; ++ j){
            cin >> grid[i][j];
            sum[i][j] = sum[i][j - 1] + grid[i][j];
        }
    }
    
    for(int d = m - 1; d >= 0; -- d){
        for(int j = 1;j + d <= m; ++ j){
            t = j + d;
            for(int i = 1;i <= n; ++ i)
                rsum[i] = rsum[i - 1] + sum[i][t] - sum[i][j - 1];
            b = e = 1;
            t = 0;
            while(e <= n){
                if(rsum[e] - rsum[b - 1] <= k){
                    t = max(t, e - b + 1);
                    ++ e;
                }
                else ++ b;
            }
            if(t)
            r = max(r, t * (d + 1));
        }
    }
    cout << r << endl;
    return 0;
}
