/*
描述
H国的身份证号码是一个N位的正整数(首位不能是0)。此外，由于防伪需要，一个N位正整数是合法的身份证号码当且仅当每位数字都小于等于K，并且任意相邻两位数字的乘积也小于等于K。

例如对于K=5, 101、211、210等都是合法的号码，而106、123、421等都是非法的号码。

给定一个正整数N以及K，H国总统想知道一共有多少个合法的号码可用。

输入
两个整数N和K。

对于30%的数据，1 ≤ N ≤ 10  

对于50%的数据，1 ≤ N ≤ 1000000

对于100%的数据，1 ≤ N ≤ 1012，1 ≤ K ≤ 81。

输出
合法号码的总数。由于答案可能非常大，你只需要输出答案对109+7取模的结果。

样例输入
2 4
样例输出
12
*/

// F[i][j]表示最后一位为j的合法i位数有多少个
// F[1][1...9] = 1, F[i][j <= k] = sum{F[i - 1][l], j * l <= k, l <= k}
// 求快速幂

#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
const int mod = 1e9 + 7;

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
vector<vector<T>> matrix_power(vector<vector<T>> num, LL n){
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

int main() {
    LL n;
    int k, m;
    cin >> n >> k;
    m = min(k, 9) + 1;
    vector<vector<LL>> mat(m, vector<LL>(m, 0)), mul(m, vector<LL>(m, 0));
    for(int i = 0;i < m; ++ i){
        mat[0][i] = 1;
        for(int j = 0; j < m; ++ j){
            if(i * j <= k)
                mul[i][j] = 1;
        }
    }
    mat[0][0] = 0;
    
    mat = matrix_multiply(mat, matrix_power(mul, n - 1));
    LL res = 0;
    for(int i = 0;i < m; ++ i)
        res = (res + mat[0][i]) % mod;
    cout << res << endl;
    return 0;
}
