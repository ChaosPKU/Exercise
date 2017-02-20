/*
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.

You may assume that the given expression is always valid.

Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5
Note: Do not use the eval built-in library function.
*/

class Solution {
  private:
    int calc(const int &a, const char &c, const int &b){
      int res = 0;
      switch (c) {
      	case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
        default : res = -1;
      }
      return res;
    }
  public:
    int calculate(const string &s) {
      stack<char> opt;
      stack<int> num;
      for(int i = 0;i < s.size();){
        switch(s[i]){
          case '(':
          case '+':
          case '-':
          case '*':
          case '/':
            opt.push(s[i ++]);
            break;
          case ')':
            while(!opt.empty() && !num.empty() && opt.top() != '('){
              int n = num.top();
              char op = opt.top();
              num.pop();
              opt.pop();
              op = opt.empty() || opt.top() != '-' ? op : (op == '+' ? '-' : '+');
              n = calc(num.top(), op, n);
              num.pop();
              num.push(n);
            }
            if(opt.top() == '('){
              opt.pop();
              if(!opt.empty() && !num.empty() && (opt.top() == '*' || opt.top() == '/')){
                int n = num.top();
                num.pop();
                n = calc(num.top(), opt.top(), n);
                num.pop();
                opt.pop();
                num.push(n);
              }
            }
            ++ i;
            break;
          default:
            if(isdigit(s[i])){
              int cnt = 0;
              while(++ cnt + i < s.size() && isdigit(s[cnt + i]));
              int n = stoi(s.substr(i, cnt));
              if(!opt.empty() && !num.empty() && (opt.top() == '*' || opt.top() == '/')){
                n = calc(num.top(), opt.top(), n);
                opt.pop();
                num.pop();
              }
              num.push(n);
              i += cnt;
            }
            else ++ i;
        }
      }
      while(!opt.empty() && !num.empty() && opt.top() != '('){
        int n = num.top();
        char op = opt.top();
        num.pop();
        opt.pop();
        op = opt.empty() || opt.top() != '-' ? op : (op == '+' ? '-' : '+');
        n = calc(num.top(), op, n);
        num.pop();
        num.push(n);
      }
      return num.top();
    }
  };

