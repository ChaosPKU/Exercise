/*
描述
小Hi有一块由NxM个单位正方形组成的矩形。现在小Ho在某些单位正方形上画了一道分割线，这条分割线或者是单位正方形的主对角线（用'\'表示），或者是副对角线（用'/'表示）。  

现在小Hi想知道这些分割线把NxM的矩形分割成了多少块区域。

例如

/\
\/
就把2x2的矩形分成了5个区域。

/\/\
\  /
 \/\
把3x4的矩形分成了7个区域。

输入
第一包含两个整数N和M。(1 <= N, M <= 100)  

以下N行每行包含M个字符。每个字符只可能是/\或者空格。

输出
分割成的区域数目。

样例输入
3 4    
/\/\  
\  /  
 \/\
样例输出
7
*/

#include <iostream>
#include<unordered_set>
using namespace std;

int prt[4 * 10005];

int Find(int x){
    return x == prt[x] ? x : prt[x] = Find(prt[x]);
}

void Union(int x, int y){
    prt[Find(x)] = Find(y);
}

int main(){
    int N, M;
    char C;
    scanf("%d%d", &N, &M);
    for(int i = 0;i < 4 * N * M; ++ i) prt[i] = i;
    for(int i = 0;i < N; ++ i){
        scanf("%c", &C);
        for(int j = 0;j < M; ++ j){
            scanf("%c", &C);
            if(C == '\\'){
                Union(4 * (M * i + j) + 0, 4 * (M * i + j) + 1);
                Union(4 * (M * i + j) + 2, 4 * (M * i + j) + 3);
            }
            else if(C == '/'){
                Union(4 * (M * i + j) + 0, 4 * (M * i + j) + 3);
                Union(4 * (M * i + j) + 1, 4 * (M * i + j) + 2);
            }
            else{
                Union(4 * (M * i + j) + 0, 4 * (M * i + j) + 1);
                Union(4 * (M * i + j) + 0, 4 * (M * i + j) + 2);
                Union(4 * (M * i + j) + 0, 4 * (M * i + j) + 3);
            }
            if(i > 0) Union(4 * (M * i + j) + 0, 4 * (M * i - M + j) + 2);
            if(j > 0) Union(4 * (M * i + j) + 3, 4 * (M * i + j - 1) + 1);
//            if(i + 1 < N) Union(4 * (M * i + j) + 2, 4 * (M * i + M + j) + 0);
//            if(j + 1 < M) Union(4 * (M * i + j) + 1, 4 * (M * i + j + 1) + 3);
        }
    }
    unordered_set<int> udst;
    for(int i = 0;i < 4 * N * M; ++ i)  udst.insert(Find(i));
    printf("%d\n", (int)udst.size());
    return 0;
}
