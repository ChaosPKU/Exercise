/*

描述
有一群旅行爱好者，有一天，他们带回了n只蝴蝶回来。他们相信每一只都属于两个不同种类中的一种，为了讨论方便，我们称它们为A与B。他们想把n只标本分成两组——一些属于A且一些属于B——但是直接标记任何一个标本对于他们是非常困难，因此他们决定采用下面的方法。

对每对标本i和j，他们细心地把它们放到一起研究。如果他们以自己的判断足以确信，那么他们把这对蝴蝶标记为“相同”（这意味着他们相信这两只来自同一类）或者是“不同”（这意味着他们相信这两只来自不同的类）。他们也可以对某些标本判断不出来而弃权，在这种情况下，我们称这对标本是不明确的。

现在他们有n只标本的集合，还有对那些没有弃权的标本对的m个判断的集合（“相同”或者“不同”）。他们想知道这个数据与每只蝴蝶来自A和B中的一个类的想法是否一致。更具体地说，如果对每对蝴蝶按照下述方式标记A或B是可能的，即对每个标为“相同”的（i，j）对，就是i与j有相同标记的情况；对每个标为“不同”的（i，j）对，就是i与j有不同标记的情况。那么我们可以说这m个判断是一致的。他们正在冥思苦想自己的判断是否是一致的。请你帮他们设计合理的算法解决该问题。


输入
输入包含多组数据，以文件结束符为终止。

每组数据第一行为两个整数，分别是n和m：
n为蝴蝶的数量，编号从0到n-1
m为关系的数量

接下来是m组关系数据，每组数据占一行，为三个整数，前两个整数表示蝴蝶的编号，第三个整数为关系的种类（相同或者不同）：
0为相同，1为不同

1 < n <= 1000
1 < m <= 100000
输出
合理就输出YES
不合理就输出NO
样例输入
3 3
0 1 0
1 2 1
0 2 1
3 3
0 1 0
1 2 1
0 2 0
样例输出
YES
NO

*/

#include <iostream>
#include <stack>
using namespace std;
int prt[1005],rak[1005];
int myFind(int i) {
    if (prt[i] == i)
        return i;
    int p = prt[i];
    prt[i] = myFind(prt[i]);
    rak[i] ^= rak[p];
    return prt[i];
}
bool myUnion(int x, int y, int type) {
    int xx = myFind(x);
    int yy = myFind(y);
    if (xx == yy){
        if((type + rak[x] + rak[y]) % 2)
            return false;
        else return true;
    }
    prt[xx] = yy;
    rak[xx] = (type + rak[x] + rak[y]) % 2;
    return true;
}
void init(int m){
    for(int i = 0; i < m; ++ i){
        prt[i] = i;
        rak[i] = 0;
    }
}
int main() {
    int m, n;
    while (scanf("%d%d", &m, &n) != EOF) {
        init(m);
        bool flag = true;
        while(n --){
            int x,y,t;
            scanf("%d%d%d",&x,&y,&t);
            if(flag && !myUnion(x, y, t)){
                flag = false;
            }
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
