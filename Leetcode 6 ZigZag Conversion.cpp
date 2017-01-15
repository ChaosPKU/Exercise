/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
*/

class Solution {
public:
    string convert(string s, int numRows) {
        int slen = s.size();
        if(slen < 3 || numRows < 2) return s;
        string res = "";
        int l = 2 * (numRows - 1), i = 0;
        while(i < slen){
            res += s[i];
            i += l;
        }
        for(i = 1;i < numRows - 1; ++ i){
            int k = i;
            while(k < slen){
                res += s[k];
                if(k + l - 2 * i < slen)
                    res += s[k + l - 2 * i];
                k += l;
            }
        }
        while(i < slen){
            res += s[i];
            i += l;
        }
        return res;
    }
};
