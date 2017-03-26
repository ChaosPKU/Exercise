/*
描述
如果一个字符串恰好包含2个'h'、1个'i'和1个'o'，我们就称这个字符串是hiho字符串。  

例如"oihateher"、"hugeinputhugeoutput"都是hiho字符串。

现在给定一个只包含小写字母的字符串S，小Hi想知道S的所有子串中，最短的hiho字符串是哪个。

输入
字符串S  

对于80%的数据，S的长度不超过1000  

对于100%的数据，S的长度不超过100000

输出
找到S的所有子串中，最短的hiho字符串是哪个，输出该子串的长度。如果S的子串中没有hiho字符串，输出-1。

样例输入
happyhahaiohell
样例输出
5
*/

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

char str[100005];
int Hash[4] = {0};

int main(){
    scanf("%s", str);
    int b = 0, n = (int)strlen(str), res = n + 1;
    for(int i = 0;i < n; ++ i){
        if(str[i] == 'h') ++ Hash[0];
        else if(str[i] == 'i') ++ Hash[1];
        else if(str[i] == 'o') ++ Hash[2];
        while(Hash[0] >= 2 && Hash[1] >= 1 && Hash[2] >= 1){
        	if(Hash[0] == 2 && Hash[1] == 1 && Hash[2] == 1)
            	res = min(res, i - b + 1);
            if(str[b] == 'h') -- Hash[0];
            else if(str[b] == 'i') -- Hash[1];
            else if(str[b] == 'o') -- Hash[2];
            ++ b;
        }
    }
    printf("%d\n", res == n + 1 ? -1 : res);
    return 0;
}
