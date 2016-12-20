/*
Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0. 
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.
*/
class Solution {
public:
    unordered_map<string, int> udmp;
    vector<int> prt;
    vector<double> rak;
    vector<vector<double>> matrix;
    int n = 0;
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        int n = 0;
        vector<double> res;
        for(pair<string, string> p : equations){
            if(udmp.find(p.first) == udmp.end()) udmp[p.first] = n ++;
            if(udmp.find(p.second) == udmp.end()) udmp[p.second] = n ++;
        }
        prt.resize(n);
        rak.resize(n);
        matrix.resize(n, vector<double>(n, -1));
        
        for(int i = 0;i < n; ++ i){
            prt[i] = i;
            rak[i] = 1;
            matrix[i][i] = 1;
        }
        
        for(int i = 0;i < equations.size(); ++ i){
            matrix[udmp[equations[i].first]][udmp[equations[i].second]] = values[i];
            matrix[udmp[equations[i].second]][udmp[equations[i].first]] = 1 / values[i];
        }
        
        for(int i = 0;i < equations.size(); ++ i)
            myUnion(udmp[equations[i].first], udmp[equations[i].second]);
        
        for(pair<string, string> q : queries){
            if(udmp.find(q.first) == udmp.end() || udmp.find(q.second) == udmp.end()){
                res.push_back(-1);
                continue;
            }
            int xx = myFind(udmp[q.first]), yy = myFind(udmp[q.second]);
            if(xx != yy)
                res.push_back(-1);
            else
                res.push_back(rak[udmp[q.second]] / rak[udmp[q.first]]);
        }
        return res;
    }
    int myFind(int x){
        if(prt[x] == x) return x;
        int tmp = myFind(prt[x]);
        matrix[tmp][x] = rak[x] = rak[prt[x]] * matrix[prt[x]][x];
        matrix[x][tmp] = 1 / matrix[tmp][x];
        return prt[x] = tmp;
    }
    void myUnion(int x, int y){
        int xx = myFind(x), yy = myFind(y);
        if(xx != x)
            prt[y] = x;
        else
            prt[x] = y;
    }
};
