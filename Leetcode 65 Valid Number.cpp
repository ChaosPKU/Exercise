/*
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.
*/

class Solution {
public:
    bool isNumber(string s) 
    {
        int i = 0;
        for(; s[i] == ' '; i++) {}
        if(s[i] == '+' || s[i] == '-') i++; 
    
        int n_pt, n_nm;
        for(n_pt=0, n_nm = 0; (s[i]<='9' && s[i]>='0') || s[i]=='.'; i++)
            s[i] == '.'  ? n_pt++ : n_nm++;       
        if(n_pt>1 || n_nm < 1) 
            return false;
    
        if(s[i] == 'e') {
            i++;
            if(s[i] == '+' || s[i] == '-') i++; 
        
            int n_nm = 0;
            for(; s[i]>='0' && s[i]<='9'; i++, n_nm++) {}
                if(n_nm<1)
                    return false;
        }
    
        for(; s[i] == ' '; i++) {}
        return s[i]==0;
    }
};
