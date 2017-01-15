/*

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

*/

class Solution {
public:
    string simplifyPath(string path) {
        stack<string> stk;
        path = path.substr(1, path.size() - 1);
        int i = path.find('/');
        while(i != -1){
            string tmp = path.substr(0, i);
            if(tmp == ".."){
                if(!stk.empty())    
                    stk.pop();
            }
            else if(tmp.size() && tmp != "."){
                stk.push(tmp);
            }
            path = path.substr(i + 1, path.size() - i - 1);
            i = path.find('/');
        }
        if(path == ".."){
            if(!stk.empty())    
                stk.pop();
        }
        else if(path.size() && path != "."){
            stk.push(path);
        }
        string res = "";
        while(!stk.empty()){
            res = "/" + stk.top() + res;
            stk.pop();
        }
        return res == "" ? "/" : res;
    }
};
