/*
继MIU8推出手机分身功能之后，MIU9计划推出一个电话号码分身的功能：首先将电话号码中的每个数字加上8取个位，然后使用对应的大写字母代替("ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"), 然后随机打乱这些字母，所生成的字符串即为电话号码对应的分身。
输入:第一行是一个整数T,表示测试样例数；接下来T行，每行给定一个分身后的电话号码的分身(长度在3到10000之间)。
输出:T行，分别对应输入中每行字符串对应的分身前的最小电话号码(允许有前导0)。
思路:简单题，找每个数字的独立字符集即可。
*/
#include <iostream>
#include <unordered_map>
using namespace std;
int main(){
    string strs[10] = {"EIGHT", "ZERO", "TWO", "FOUR", "SIX", "FIVE", "SEVEN", "THREE", "ONE", "NINE"};
    char uniq[10] = {'G', 'Z', 'W', 'U', 'X', 'F', 'S', 'T', 'O', 'I'};
    char ctr[10] = {'0', '2', '4', '6', '8', '7', '9', '5', '3', '1'};
    int n;
    cin >> n;
    string s = "", res = "";
    unordered_map<char, int> um;
    while(n --){
        um.clear();
        cin >> s;
        res = "";
        for(char c : s)
            ++ um[c];
        for(int i = 0;i < 10; ++ i){
            res += *new string(um[uniq[i]], ctr[i]);
            int feq = um[uniq[i]];
            for(int j = 0;j < strs[i].size(); ++ j)
                um[strs[i][j]] -= feq;
        }
        sort(res.begin(), res.end());
        cout << res << endl;
    }
    return 0;
}
