/*

描述
小Hi的学校正面临着废校的大危机。面对学校的危机，小Hi同学们决定从ABC三个班中各挑出一名同学成为偶像。  

成为偶像团体的条件之一，就是3名团员之间的身高差越小越好。  

已知ABC三个班同学的身高分别是A1..AN, B1..BM 和 C1..CL。请你从中选出3名同学Ai, Bj, Ck使得D=|Ai-Bj|+|Bj-Ck|+|Ck-Ai|最小。

输入
第一行包含3个整数，N, M和L。  

第二行包含N个整数，A1, A2, ... AN。(1 <= Ai <= 100000000)

第三行包含M个整数，B1, B2, ... BM。(1 <= Bi <= 100000000)

第四行包含L个整数，C1, C2, ... CL。(1 <= Ci <= 100000000)

对于30%的数据, 1 <= N, M, L <= 100  

对于60%的数据，1 <= N, M, L <= 1000  

对于100%的数据，1 <= N, M, L <= 100000

输出
输出最小的D。

样例输入
3 3 3  
170 180 190  
195 185 175  
180 160 200
样例输出
10

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct num {
    int val, type;
    bool operator<(const num &a) const{
        return val != a.val ? val < a.val : type < a.type;
    };
};

int calc(vector<vector<num>::iterator> &vtr){
    if(*vtr[1] < *vtr[0]) swap(vtr[0], vtr[1]);
    if(*vtr[2] < *vtr[0]) swap(vtr[0], vtr[2]);
    if(*vtr[2] < *vtr[1]) swap(vtr[1], vtr[2]);
    return 2 * (vtr[2]->val - vtr[0]->val);
}

int main(){
    int i, j, r, tot[3];
    scanf("%d%d%d", &tot[0], &tot[1], &tot[2]);
    vector<vector<num>> nums(3, vector<num>(100005));
    for(i = 0;i < 3; ++ i)
        for(j = 0;j < tot[i]; ++ j){
            scanf("%d", &nums[i][j].val);
            nums[i][j].type = i;
        }
    for(i = 0;i < 3; ++ i)
        sort(nums[i].begin(), nums[i].begin() + tot[i]);
    
    r = -1 ^ (1 << 31);
    vector<vector<num>::iterator> vtr({nums[0].begin(), nums[1].begin(), nums[2].begin()});
    vector<int> counter(3, 0);
    
    while(true){
        r = min(r, calc(vtr));
        ++ vtr[0];
        if(++ counter[vtr[0]->type] >= tot[vtr[0]->type]) break;
    }
    
    printf("%d\n", r);
    return 0;
}
