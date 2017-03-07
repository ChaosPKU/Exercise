/*

时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Ho在一条笔直的街道上散步。街道上铺着长度为L的石板，所以每隔L距离就有一条石板连接的缝隙，如下图所示。

小Ho在散步的时候有奇怪的强迫症，他不希望脚踩在石板的缝隙上。（如果小Ho一只脚的脚尖和脚跟分别处于一条缝隙的两侧，我们就认为他踩在了缝隙上。如果只有脚尖或脚跟接触缝隙，不算做踩在缝隙上）  

现在我们已知小Ho两只脚的长度F以及每一步步伐的长度D。如果小Ho可以任意选择起始位置，请你判断小Ho能否保持不踩缝隙散步至无穷远处？

输入
第一行是一个整数T，表示测试数据的组数。

每组测试数据包含3和整数L, F和D，含义如上文所述。

对于30%的数据： L <= 1000  

对于60%的数据： L <= 100000

对于100%的数据： L <= 100000000, F <= 100000000, D <= 100000000, T <= 20

输出
对于每组数据输出一行YES或者NO，表示小Ho是否能走到无穷远处。

样例输入
2  
60 26 60  
30 26 75 
样例输出
YES  
NO

*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <bitset>
using namespace std;

int gcd(int a, int b)
{
    return a == 0 ? b : gcd(b % a, a);
}


int main(){
    int N, F, D, L;
    cin >> N;
    for(int i = 0;i < N; ++ i){
        cin >> L >> F >> D;
        if(gcd(L, D) >= F)
            cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
