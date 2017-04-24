/*
描述
小Hi的学校总共有N名学生，编号1-N。学校刚刚进行了一场全校的古诗文水平测验。  

学校没有公布测验的成绩，所以小Hi只能得到一些小道消息，例如X号同学的分数比Y号同学的分数高S分。  

小Hi想知道利用这些消息，能不能判断出某两位同学之间的分数高低？

输入
第一行包含三个整数N, M和Q。N表示学生总数，M表示小Hi知道消息的总数，Q表示小Hi想询问的数量。  

以下M行每行三个整数，X, Y和S。表示X号同学的分数比Y号同学的分数高S分。  

以下Q行每行两个整数，X和Y。表示小Hi想知道X号同学的分数比Y号同学的分数高几分。  

对于50%的数据，1 <= N, M, Q <= 1000  

对于100%的数据，1 <= N, M, Q<= 100000 1 <= X, Y <= N -1000 <= S <= 1000

数据保证没有矛盾。

输出
对于每个询问，如果不能判断出X比Y高几分输出-1。否则输出X比Y高的分数。

样例输入
10 5 3  
1 2 10  
2 3 10  
4 5 -10  
5 6 -10  
2 5 10  
1 10  
1 5  
3 5
样例输出
-1  
20  
0
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> prt, rak; // rak表示此元素距本集合最小元素的距离

int Find(int x){
    if(x == prt[x]) return x;
    int tmp = prt[x];
    prt[x] = Find(prt[x]);
    rak[x] += rak[tmp];
    return prt[x];
}

int main(){
    int n, m, q, x, y, s, i, xx, yy;
    scanf("%d%d%d", &n, &m, &q);
    prt.resize(n + 1);
    rak.resize(n + 1, 0);
    for(i = 0;i <= n; ++ i) prt[i] = i;
    for(i = 0;i < m; ++ i){
        scanf("%d%d%d", &x, &y, &s);
        if(s < 0) swap(x, y), s = -s;
        xx = Find(x);
        yy = Find(y);
        if(xx == yy) continue;
        if(rak[x] - s > rak[y]){ // x所在集合的最小值小于y所在集合的最小值
            prt[yy] = xx;
            rak[yy] = rak[x] - s - rak[y];
        }
        else{
            prt[xx] = yy;
            rak[xx] = rak[y] - (rak[x] - s);
        }
    }

    for(i = 0;i < q; ++ i){
        scanf("%d%d", &x, &y);
        xx = Find(x);
        yy = Find(y);
        if(xx != yy) printf("-1\n");
        else printf("%d\n", rak[x] - rak[y]);
    }
    return 0;
}
