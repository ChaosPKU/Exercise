/*
在一个N*N的数组中寻找所有横，竖，左上到右下，右上到左下，四种方向的直线连续D个数字的和里面最大的值 
输入描述:
每个测试输入包含1个测试用例，第一行包括两个整数 N 和 D :
3 <= N <= 100
1 <= D <= N
接下来有N行，每行N个数字d:
0 <= d <= 100


输出描述:
输出一个整数，表示找到的和的最大值

输入例子:
4 2
87 98 79 61
10 27 95 70
20 64 73 29
71 65 15 0

输出例子:
193
*/

#include <iostream>
#include <vector>
using namespace std;
void solve(const vector<int> &vtr, const int &d, int &res){
    int tot = 0;
    for(int i = 0;i < d; ++ i)
        tot += vtr[i];
    res = max(res, tot);
    for(int i = d;i < vtr.size(); ++ i){
        tot = tot - vtr[i - d] + vtr[i];
        res = max(res, tot);
    }
}
int main(){
    int n, d, res = 0;
    cin >> n >> d;
    vector<vector<int>> grid(n, vector<int>(n));
    for(int i = 0;i < n; ++ i)
        for(int j = 0;j < n; ++ j)
            cin >> grid[i][j];
    for(int i = 0;i < n; ++ i)
        solve(grid[i], d, res);
    
    for(int i = 0;i < n; ++ i){
        vector<int> vtr(n);
        for(int j = 0;j < n; ++ j)
            vtr[j] = grid[j][i];
        solve(vtr, d, res);
    }
    
    for(int i = 0; i + d <= n; ++ i){
        vector<int> vtr(n - i);
        for(int j = 0;j < n - i; ++ j)
            vtr[j] = grid[i + j][j];
        solve(vtr, d, res);
    }
    for(int i = 1; i + d <= n; ++ i){
        vector<int> vtr(n - i);
        for(int j = 0;j < n - i; ++ j)
            vtr[j] = grid[j][i + j];
        solve(vtr, d, res);
    }
    
    for(int i = d - 1; i < n; ++ i){
        vector<int> vtr(i + 1);
        for(int j = 0;j <= i; ++ j)
            vtr[j] = grid[i - j][j];
        solve(vtr, d, res);
    }
    for(int i = d - 1; i < n - 1; ++ i){
        vector<int> vtr(i + 1);
        for(int j = 0;j <= i; ++ j)
            vtr[j] = grid[n - 1 - j][n - 1 - i + j];
        solve(vtr, d, res);
    }
    
    cout << res << endl;
    return 0;
}
