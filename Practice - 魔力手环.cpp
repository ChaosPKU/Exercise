/*
小易拥有一个拥有魔力的手环上面有n个数字(构成一个环),当这个魔力手环每次使用魔力的时候就会发生一种奇特的变化：每个数字会变成自己跟后面一个数字的和(最后一个数字的后面一个数字是第一个),一旦某个位置的数字大于等于100就马上对100取模(比如某个位置变为103,就会自动变为3).现在给出这个魔力手环的构成，请你计算出使用k次魔力之后魔力手环的状态。 
输入描述:
输入数据包括两行：
第一行为两个整数n(2 ≤ n ≤ 50)和k(1 ≤ k ≤ 2000000000),以空格分隔
第二行为魔力手环初始的n个数，以空格分隔。范围都在0至99.


输出描述:
输出魔力手环使用k次之后的状态，以空格分隔，行末无空格。

输入例子:
3 2
1 2 3

输出例子:
8 9 7
*/

#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

//template <class T>
//vector<vector<T>> matrix_multiply(const vector<vector<T>> &num1, const vector<vector<T>> &num2){
//    int len1 = (int)num1.size(), len2 = (int)num2.size(), len3 = (int)num2[0].size();
//    if(num1.empty() || num2.empty())  throw "Empty Matrix!";
//    if(num1[0].size() != len2) throw "Matrix Format Error!";
//    vector<vector<T>> res(len1, vector<T>(len3, 0));
//    for(int i = 0;i < len1; ++ i)
//        for(int j = 0;j < len3; ++ j)
//            for(int k = 0;k < len2; ++ k)
//                res[i][j] += num1[i][k] * num2[k][j];
//    return res;
//}

template <class T>
vector<vector<T>> matrix_multiply(vector<vector<T>> num1, vector<vector<T>> num2){
    int len1 = (int)num1.size(), len2 = (int)num2.size(), len3 = (int)num2[0].size();
    if(num1.empty() || num2.empty())  throw "Empty Matrix!";
    if(num1[0].size() != len2) throw "Matrix Format Error!";
    vector<vector<T>> res(len1, vector<T>(len3, 0));
    for(int i = 0;i < len1; ++ i)
        for(int j = 0;j < len3; ++ j)
            for(int k = 0;k < len2; ++ k)
                res[i][j] = (res[i][j] + num1[i][k] * num2[k][j]) % 100;
    return res;
}

template <class T>
vector<vector<T>> matrix_power(vector<vector<T>> num, int n){
    if(num.empty()) throw "Empty Matrix!";
    int len1 = (int)num.size(), len2 = (int)num[0].size();
    if(len1 != len2) throw "Matrix Format Error!";
    vector<vector<T>> res(len1, vector<T>(len2, 0));
    for(int i = 0; i < len1; ++ i) res[i][i] = 1;
    while(n){
        if(n & 1) res = matrix_multiply(res, num);
        num = matrix_multiply(num, num);
        n >>= 1;
    }
    return res;
}


int main(){
    int n, k;
    cin >> n >> k;
    vector<vector<int>> vtr(n, vector<int>(1));
    for(int i = 0;i < n; ++ i) cin >> vtr[i][0];
    vector<vector<int>> Mat(n, vector<int>(n, 0));
    for(int i = 0;i < n; ++ i) Mat[i][i] = Mat[i][(i + 1) % n] = 1;
    vector<vector<int>> res = matrix_multiply(matrix_power(Mat, k), vtr);
    for(int i = 0;i < n - 1; ++ i)
        cout << res[i][0] << " ";
    cout << res[n - 1][0] << endl;
    return 0;
}
