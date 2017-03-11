/*
描述
Given a set of constraints like 0<N<=M<=100 and values for all the variables, write a checker program to determine if the constraints are satisfied.

More precisely, the format of constraints is:

token op token op ... op token

where each token is either a constant integer or a variable represented by a capital letter and each op is either less-than ( < ) or less-than-or-equal-to ( <= ). 

输入
The first line contains an integer N, the number of constraints. (1 ≤ N ≤ 20)

Each of the following N lines contains a constraint in the previous mentioned format.

Then follows an integer T, the number of assignments to check. (1 ≤ T ≤ 50)

Each assignment occupies K lines where K is the number of variables in the constraints.

Each line contains a capital letter and an integer, representing a variable and its value.

It is guaranteed that:

1. Every token in the constraints is either an integer from 0 to 1000000 or an variable represented by a capital letter from 'A' to 'Z'.

2. There is no space in the constraints.

3. In each assignment every variable appears exactly once and its value is from 0 to 1000000. 

输出
For each assignment output Yes or No indicating if the constraints are satisfied.

样例输入
2
A<B<=E
3<=E<5
2
A 1
B 2
E 3
A 3
B 5
E 10
样例输出
Yes
No 
*/


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string trans(const string &s, unordered_map<int, int> &udmp){
    if(s.size() == 1 && s[0] >= 'A' && s[0] <= 'Z')
        udmp[s[0]] ++ ;
    return s;
}

void split(const string &raw, vector<vector<string> > &token, vector<vector<int> > &opr, unordered_map<int, int> &udmp){
    vector<string> tk;
    vector<int> op;
    int idx = 0, tidx = 0, tmp = 0;
    while((tidx = (int)raw.find("<", idx)) != string::npos){
        tk.push_back(trans(raw.substr(idx, tidx - idx), udmp));
        tmp = raw[tidx + 1] == '=';
        idx = tidx + 1 + tmp;
        op.push_back(tmp);
    }
    if(idx != raw.size())
        tk.push_back(trans(raw.substr(idx, raw.size() - idx), udmp));
    token.push_back(tk);
    opr.push_back(op);
}

bool check(string &astr, string &bstr, int &op, unordered_map<int, int> &udmp){
    int a, b;
    if(astr.size() == 1 && astr[0] >= 'A' && astr[0] <= 'Z')
        a = udmp[astr[0]];
    else a = atoi(astr.c_str());
    
    if(bstr.size() == 1 && bstr[0] >= 'A' && bstr[0] <= 'Z')
        b = udmp[bstr[0]];
    else b = atoi(bstr.c_str());
    
    if(op == 0)
        return a < b;
    else return a <= b;
}

int main(){
    int N, M, V, R;
    char K;
    string str;
    vector<vector<string> > token;
    vector<vector<int> > opr;
    unordered_map<int, int> udmp;
    cin >> N;
    for(int i = 0;i < N; ++ i){
        cin >> str;
        split(str, token, opr, udmp);
    }
    cin >> M;
    for(int i = 0;i < M; ++ i){
        for(int j = 0;j < udmp.size(); ++ j){
            cin >> K >> V;
            udmp[K] = V;
        }
        R = 1;
        for(int n = 0;n < N; ++ n){
            for(int k = 0;k < opr[n].size(); ++ k)
                if(!check(token[n][k], token[n][k + 1], opr[n][k], udmp)) {
                    R = 0;
                    break;
                }
            if(!R) break;
        }
        if(R) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    
    return 0;
}
