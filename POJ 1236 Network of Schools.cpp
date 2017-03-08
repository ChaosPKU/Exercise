/*
Description

A number of schools are connected to a computer network. Agreements have been developed among those schools: each school maintains a list of schools to which it distributes software (the “receiving schools”). Note that if B is in the distribution list of school A, then A does not necessarily appear in the list of school B 
You are to write a program that computes the minimal number of schools that must receive a copy of the new software in order for the software to reach all schools in the network according to the agreement (Subtask A). As a further task, we want to ensure that by sending the copy of new software to an arbitrary school, this software will reach all schools in the network. To achieve this goal we may have to extend the lists of receivers by new members. Compute the minimal number of extensions that have to be made so that whatever school we send the new software to, it will reach all other schools (Subtask B). One extension means introducing one new member into the list of receivers of one school. 
Input

The first line contains an integer N: the number of schools in the network (2 <= N <= 100). The schools are identified by the first N positive integers. Each of the next N lines describes a list of receivers. The line i+1 contains the identifiers of the receivers of school i. Each list ends with a 0. An empty list contains a 0 alone in the line.
Output

Your program should write two lines to the standard output. The first line should contain one positive integer: the solution of subtask A. The second line should contain the solution of subtask B.
Sample Input

5
2 4 3 0
4 5 0
0
0
1 0
Sample Output

1
2

*/

/*
 tarjan算法的基础是DFS。我们准备两个数组low和dfn。low数组是一个标记数组，记录该点所在的强连通子图所在搜索子树的根节点的dfn值，dfn数组记录搜索到该点的时间，也就是第几个搜索这个点的。根据以下几条规则，经过搜索遍历该图（无需回溯）和对栈的操作，我们就可以得到该有向图的强连通分量。
 数组的初始化：当首次搜索到点p时，dfn与low数组的值都为到该点的时间。
 堆栈：每搜索到一个点，将它压入栈顶。
 当点p有与点p’相连时，如果此时（时间为dfn[p]时）p’不在栈中，p的low值为两点的low值中较小的一个。
 当点p有与点p’相连时，如果此时（时间为dfn[p]时）p’在栈中，p的low值为p的low值和p’的dfn值中较小的一个。
 每当搜索到一个点经过以上操作后（也就是子树已经全部遍历）的low值等于dfn值，则将它以及在它之上的元素弹出栈。这些出栈的元素组成一个强连通分量。
 继续搜索（或许会更换搜索的起点，因为整个有向图可能分为两个不连通的部分），直到所有点被遍历。
 由于每个顶点只访问过一次，每条边也只访问过一次，我们就可以在O（n+m）的时间内求出有向图的强连通分量。
 
 Tarjan算法的操作原理如下：
 Tarjan算法基于定理：在任何深度优先搜索中，同一强连通分量内的所有顶点均在同一棵深度优先搜索树中。也就是说，强连通分量一定是有向图的某个深搜树子树。
 可以证明，当一个点既是强连通子图Ⅰ中的点，又是强连通子图Ⅱ中的点，则它是强连通子图Ⅰ∪Ⅱ中的点。
 这样，我们用low值记录该点所在强连通子图对应的搜索子树的根节点的dfn值。注意，该子树中的元素在栈中一定是相邻的，且根节点在栈中一定位于所有子树元素的最下方。
 强连通分量是由若干个环组成的。所以，当有环形成时（也就是搜索的下一个点已在栈中），我们将这一条路径的low值统一，即这条路径上的点属于同一个强连通分量。
 如果遍历完整个搜索树后某个点的dfn值等于low值，则它是该搜索子树的根。这时，它以上（包括它自己）一直到栈顶的所有元素组成一个强连通分量。
 
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define MAX_N 105

vector<vector<int> > linklist(MAX_N);
int dfn[MAX_N], low[MAX_N], stack[MAX_N];
// dfn 第一次访问的步数, low 标记数组，记录该点所在的强连通子图所在搜索子树的根节点的dfn值, stack 模拟栈
bool instack[MAX_N];
int in[MAX_N], out[MAX_N], prt[MAX_N];
int cnt, head, idx; // cnt 连通分量的个数 idx 时间戳 head 栈头元素位置
vector<int> vertex; // 存储每个强连通子图所在搜索子树的根节点

int Find(int x){
    if(x == prt[x]) return x;
    return prt[x] = Find(prt[x]);
}

void Union(int p, int x){
    if(dfn[p] >= dfn[x]) swap(p, x);
    prt[x] = Find(p);
}

void Tarjan(int x){
    int p;
    low[x] = dfn[x] = idx ++; // 刚搜到一个节点时low = dfn
    stack[head ++ ] = x; // 将该节点入栈
    instack[x] = 1; // 将入栈标记设置为1
    for(int t = 0; t < linklist[x].size(); ++ t){ // 遍历入栈节点的边
        int i = linklist[x][t];
        if(dfn[i] == -1){  //如果新搜索到的节点是从未被搜索过
            Tarjan(i);
            low[x] = min(low[x], low[i]); // 回溯的时候改变当前节点的low值
        }
        else if(instack[i]) // 如果新搜索到的节点已经被搜索过而且现在在栈中
            low[x] = min(low[x], dfn[i]); // 更新当前节点的low值，这里的意思是两个节点之间有一条可达边，而前面节点已经在栈中，那么后面的节点就可能和前面的节点在一个联通分量中
    }
    
    if(low[x] == dfn[x]){  // 最终退回来的时候 low == dfn ， 没有节点能将根节点更新，那low == dfn 的节点必然就是根节点
        while(true){ // 一直出栈到此节点， 这些元素是一个强联通分量
            p = stack[-- head];
            Union(p, x);
            instack[p] = 0;
            if(p == x) break;
        }
        vertex.push_back(Find(x));
        ++ cnt;
    }
}

int main() {
    int n, t, r1, r2;
    
    scanf("%d", &n);
    for(int i = 0;i < n; ++ i){
        while(scanf("%d", &t) && t)
            linklist[i].push_back(t - 1);
        prt[i] = i;
    }
    
    memset(dfn, -1, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(instack, 0, sizeof(instack));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    idx = cnt = head = 0;
    for(int i = 0;i < n; ++ i){
        if(dfn[i] == -1)
            Tarjan(i);
    }
    
    for(int i = 0;i < n; ++ i)
        for(int t = 0; t < linklist[i].size(); ++ t){ // 遍历每条边，找到缩点之后的边
            int j = linklist[i][t];
            if(Find(i) != Find(j)){  // 两点之间有边，但不是属于一个强联通分量的边
                ++ out[prt[i]]; // 缩点后的点出度+1
                ++ in[prt[j]];  // 缩点后的点入度+1
            }
        }
    
    r1 = r2 = 0;
    for(int i = 0;i < vertex.size(); ++ i){
        if(!in[vertex[i]]) r1 ++;
        if(!out[vertex[i]]) r2 ++;
    }
    
    if(cnt == 1) printf("1\n0\n");
    else printf("%d\n%d\n", r1, max(r1, r2));
    return 0;
}


