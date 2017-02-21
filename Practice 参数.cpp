#include "MyHeader.h"

/*
 题目描述：
 有一个API，要生成一系列的测试用的requests。给定允许的参数名，以及它可能的值，这个值是否是必须的（用1表示是必须的，0表示非必须），是否可以传多个值（1 表示可以，0表示不行，如果可以，各个值之间用逗号分隔，并且各个值的顺序需按字典序排序），允许的值是否可以有负号前缀（同一个值带负号前缀和不带负号前缀最多只可以传1个）。各个参数之间用&分隔。请生成所有可能的requests。requests按字典序排序，同一个requests里的参数按字典序进行排序
 输入
 第一行为参数的个数N。
 然后是N*2行。每两行表示一个参数的信息。
 每两行的第一行会有1个只含字母和下划线的字符串，表示参数名，以及3个1或者0的数字，分别表示这个参数是否是必须的，这个参数是否可以传多个值，传入的值是否可以带负号前缀。
 每两行的第二行是用逗号分隔的值，每个值只可能含有字母或者数字。每一个参数可能的值不超过5个。
 假设至少存在一个必须的参数。
 数据范围:
 1 <= N <= 5
 对于20%的数据，参数都只用传一个且都不带负号前缀。
 对于30%的数据，存在传多个值的参数，但都不带负号前缀。
 对于50%的数据，都存在。
 输出
 根据指定的顺序输出所有的request的参数列表，每一个占一行。
 
 样例输入
 2
 required_multi_param 1 1 0
 1,2
 optional_with_negative 0 0 1
 own1,own2
 样例输出
 optional_with_negative=-own1&required_multi_param=1
 optional_with_negative=-own1&required_multi_param=1,2
 optional_with_negative=-own1&required_multi_param=2
 optional_with_negative=-own2&required_multi_param=1
 optional_with_negative=-own2&required_multi_param=1,2
 optional_with_negative=-own2&required_multi_param=2
 optional_with_negative=own1&required_multi_param=1
 optional_with_negative=own1&required_multi_param=1,2
 optional_with_negative=own1&required_multi_param=2
 optional_with_negative=own2&required_multi_param=1
 optional_with_negative=own2&required_multi_param=1,2
 optional_with_negative=own2&required_multi_param=2
 required_multi_param=1
 required_multi_param=1,2
 required_multi_param=2
*/

void join(map<string, vector<string>>::iterator &miter, vector<string> &res, string &s, const map<string, vector<string>> &mymap){
    if(miter == mymap.end()){
        if(s.size() != 0 && s[0] == '&')
            s = s.substr(1);
        res.push_back(s);
        return;
    }
    vector<string> vec = miter->second;
    for(int i = 0; i < vec.size(); ++ i){
        map<string, vector<string>>::iterator iter = miter;
        if(vec[i] == "") {
            join(++ miter, res, s, mymap);
        }
        else{
            string tmp = s;
            s += "&" + miter->first + "=" + vec[i];
            join(++ miter, res, s, mymap);
            s = tmp;
        }
        miter = iter;
    }
}
void backtracking(vector<string> &res, const vector<string> &raw_values, string &vals, int b, const bool &isneg){
    if(b == raw_values.size()){
        if(vals.size() != 0)
            vals = vals.substr(1);
        res.push_back(vals);
        return ;
    }
    if(vals.size() != 0){
        res.push_back(vals.substr(1));
    }
    for(int i = b;i < raw_values.size(); ++ i){
        string tmp = vals;
        if(isneg){
            vals += (",-" + raw_values[i]);
            backtracking(res, raw_values, vals, i + 1, isneg);
            vals = tmp;
        }
        tmp = vals;
        vals += ("," + raw_values[i]);
        backtracking(res, raw_values, vals, i + 1, isneg);
        vals = tmp;
    }
    return ;
}
int main(){
    int n;
    cin >> n;
    vector<vector<string>> params;
    string param_name, raw_value;
    bool isnec = 0, ismul = 0, isneg = 0;
    map<string, vector<string>> mymap;
    while(n --){
        vector<string> raw_values,values;
        cin >> param_name >> isnec >> ismul >> isneg >> raw_value;
        raw_values = split(raw_value, ",");
        sort(raw_values.begin(), raw_values.end());
        if(!ismul)
            for(string s : raw_values){
                values.push_back(s);
                if(isneg) values.push_back("-" + s);
            }
        else{
            vector<string> res;
            string vals = "";
            backtracking(res, raw_values, vals, 0, isneg);
            values.insert(values.end(), res.begin(), res.end());
        }
        //sort(values.begin(), values.end());
        if(!isnec) values.push_back("");
        //sort(values.begin(), values.end());
        mymap[param_name] = values;
    }
    vector<string> res;
    string s = "";
    map<string, vector<string>>::iterator miter = mymap.begin();
    join(miter, res, s, mymap);
    sort(res.begin(), res.end()); //由于参数可能为空的情况的存在，而且其性质非常特殊，暂时没有想出不对最终结果排序的办法
    for(int i = 0;i < res.size(); ++ i)
        cout << res[i] << endl;
    return 0;
}
