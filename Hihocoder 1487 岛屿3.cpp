/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
H国正在进行一项持续N周的填海造岛工程。整片工程海域可以被看作是1000x1000的网格。

每周都有一块1x1的单位方格海域被填成陆地。如果我们将连成一片的陆地（一块单位方格与它上下左右4个单位方格是相连的）视为岛屿，H国想监测每周末整片海域中一共存在有多少个岛屿，以及这些岛屿的总面积和总周长各是多少。

假设工程持续三周，第一周被填的海域坐标是(0, 0)，那么第一周结束后有1座岛屿、总面积是1、总周长是4:

#..
...
...
第二周被填的海域坐标是(1, 1)，那么第二周结束后有2座岛屿、总面积是2、总周长是8:

#..
.#.
...
第三周被填的海域坐标是(1, 0)，那么第三周结束后有1座岛屿、总面积是3、总周长是8:

#..
##.
...
你能完成这项任务么？

输入
第一行包含一个整数N，表示工程持续的周数。(1 <= N <= 100000)  

以下N行每行包含两个整数x和y，表示当周被填的海域坐标。(0 <= x, y < 1000)

输出
输出N行，每行包含3个整数，依次是当周末岛屿的数量、总面积和总周长。

样例输入
3  
0 0   
1 1   
1 0
样例输出
1 1 4  
2 2 8  
1 3 8 
*/

#include <iostream>
#include <vector>

using namespace std;
const int tot = 1000;

int trans(int x, int y){  //慎用DEFINE!
    return x * tot + y;
}

vector<vector<bool>> grid(tot, vector<bool>(tot, 0));
vector<int> prt(trans(tot, tot), -1);

int Find(int x){
    return ~prt[x] ? prt[x] = Find(prt[x]) : x;
}

bool Union(int x, int y){
    int xx = Find(x), yy = Find(y);
    if(xx == yy) return false;
    prt[yy] = xx;
    return true;
}

bool check(int x, int y)
{
    return x >= 0 && y >= 0 && x < tot && y < tot && grid[x][y];
}

int main(){
    int N, x, y, i, j, n = 0, l = 0, xx, yy;
    scanf("%d", &N);
    int dir[5] = {0, 1, 0, -1, 0};
    for(i = 1;i <= N; ++ i){
        scanf("%d%d", &x, &y);
        ++ n;
        for(j = 0;j < 4; ++ j){
            xx = x + dir[j];
            yy = y + dir[j + 1];
            if(check(xx, yy)){
                n -= Union(trans(x, y), trans(xx, yy));
                -- l;
            }
            else ++ l;
        }
        grid[x][y] = 1;
        printf("%d %d %d\n", n, i, l);
    }
    return 0;
}
