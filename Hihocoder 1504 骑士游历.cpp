/*

描述
在8x8的国际象棋棋盘上给定一只骑士（俗称“马”）棋子的位置(R, C)，小Hi想知道从(R, C)开始移动N步一共有多少种不同的走法。  

输入
第一行包含三个整数，N，R和C。

对于40%的数据， 1 <= N <= 1000000

对于100%的数据， 1 <= N <= 1000000000 1 <= R, C <= 8

输出
从(R, C)开始走N步有多少种不同的走法。由于答案可能非常大，你只需要输出答案模1000000007的余数。

样例输入
2 1 1
样例输出
12

*/

#include <iostream>
#include <vector>
using namespace std;

const int mod = 1e9 + 7;
vector<vector<int>> grid(8, vector<int>(8, 0));
vector<vector<long long>> matrix(64, vector<long long>(64, 0));
int dir[9] = {1, 2, -1, -2, 1, -2, -1, 2, 1};

template <class T>
vector<vector<T>> matrix_multiply(vector<vector<T>> num1, vector<vector<T>> num2){
    int len1 = (int)num1.size(), len2 = (int)num2.size(), len3 = (int)num2[0].size();
    if(num1.empty() || num2.empty())  throw "Empty Matrix!";
    if(num1[0].size() != len2) throw "Matrix Format Error!";
    vector<vector<T>> res(len1, vector<T>(len3, 0));
    for(int i = 0;i < len1; ++ i)
        for(int j = 0;j < len3; ++ j)
            for(int k = 0;k < len2; ++ k)
                res[i][j] = (res[i][j] + num1[i][k] * num2[k][j]) % mod;
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
    int N, R, C, x, y;
    cin >> N >> R >> C;
    for(int i = 0;i < 8; ++ i)
        for(int j = 0;j < 8; ++ j){
            for(int k = 0;k < 8; ++ k){
                x = i + dir[k];
                y = j + dir[k + 1];
                if(x >= 0 && y >= 0 && x < 8 && y < 8)
                    matrix[i * 8 + j][x * 8 + y] = 1;
            }
        }
    vector<vector<long long>> res = matrix_power(matrix, N);
    long long ans = 0;
    int position = (R - 1) * 8 + C - 1;
    for(int i = 0;i < 64; ++ i)
        ans = (ans + res[position][i]) % mod;
    cout << ans << endl;
    return 0;
}
