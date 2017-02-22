/*

描述
It is well known that a human gene can be considered as a sequence, consisting of four nucleotides, which are simply denoted by four letters, A, C, G, and T. Biologists have been interested in identifying human genes and determining their functions, because these can be used to diagnose human diseases and to design new drugs for them. 

A human gene can be identified through a series of time-consuming biological experiments, often with the help of computer programs. Once a sequence of a gene is obtained, the next job is to determine its function. 
One of the methods for biologists to use in determining the function of a new gene sequence that they have just identified is to search a database with the new gene as a query. The database to be searched stores many gene sequences and their functions – many researchers have been submitting their genes and functions to the database and the database is freely accessible through the Internet. 

A database search will return a list of gene sequences from the database that are similar to the query gene. 
Biologists assume that sequence similarity often implies functional similarity. So, the function of the new gene might be one of the functions that the genes from the list have. To exactly determine which one is the right one another series of biological experiments will be needed. 

Your job is to make a program that compares two genes and determines their similarity as explained below. Your program may be used as a part of the database search if you can provide an efficient one. 
Given two genes AGTGATG and GTTAG, how similar are they? One of the methods to measure the similarity 
of two genes is called alignment. In an alignment, spaces are inserted, if necessary, in appropriate positions of 
the genes to make them equally long and score the resulting genes according to a scoring matrix.

For example, one space is inserted into AGTGATG to result in AGTGAT-G, and three spaces are inserted into GTTAG to result in –GT--TAG. A space is denoted by a minus sign (-). The two genes are now of equal 
length. These two strings are aligned: 

AGTGAT-G 
-GT--TAG 

In this alignment, there are four matches, namely, G in the second position, T in the third, T in the sixth, and G in the eighth. Each pair of aligned characters is assigned a score according to the following scoring matrix. 

denotes that a space-space match is not allowed. The score of the alignment above is (-3)+5+5+(-2)+(-3)+5+(-3)+5=9. 

Of course, many other alignments are possible. One is shown below (a different number of spaces are inserted into different positions): 

AGTGATG 
-GTTA-G 

This alignment gives a score of (-3)+5+5+(-2)+5+(-1) +5=14. So, this one is better than the previous one. As a matter of fact, this one is optimal since no other alignment can have a higher score. So, it is said that the 
similarity of the two genes is 14.

输入
The input consists of T test cases. The number of test cases ) (T is given in the first line of the input file. Each test case consists of two lines: each line contains an integer, the length of a gene, followed by a gene sequence. The length of each gene sequence is at least one and does not exceed 100.
输出
The output should print the similarity of each test case, one per line.
样例输入
2 
7 AGTGATG 
5 GTTAG 
7 AGCTATT 
9 AGCTTTAAA 
样例输出
14
21 

*/
#include <stdio.h>
#define max(a,b) a>b?a:b
int Dict[100][100];
char s1[105],s2[105];
void init(){
    Dict['A']['A'] = Dict['C']['C'] = Dict['G']['G'] = Dict['T']['T'] = 5;
    Dict['A']['C'] = Dict['C']['A'] = Dict['A']['T'] = Dict['T']['A'] = -1;
    Dict['-']['T'] = Dict['T']['-'] = -1;
    Dict['A']['G'] = Dict['G']['A'] = Dict['C']['T'] = Dict['T']['C'] = -2;
    Dict['G']['T'] = Dict['T']['G'] = Dict['G']['-'] = Dict['-']['G'] = -2;
    Dict['A']['-'] = Dict['-']['A'] = Dict['C']['G'] = Dict['G']['C'] = -3;
    Dict['C']['-'] = Dict['-']['C'] = -4;
}
int main(){
    init();
    int N;
    scanf("%d",&N);
    while(N --){
        int a,b;
        scanf("%d %s%d %s",&a,s1,&b,s2);
        int res[105][105];
        res[0][0] = 0;
        for(int i = 1;i <= a; ++ i)
            res[i][0] = res[i - 1][0] + Dict[s1[i - 1]]['-'];
        for(int i = 1;i <= b; ++ i)
            res[0][i] = res[0][i - 1] + Dict['-'][s2[i - 1]];
        for(int i = 1;i <= a; ++ i)
            for(int j = 1;j <= b; ++ j){
                res[i][j] = max(res[i - 1][j] + Dict[s1[i - 1]]['-'], res[i][j - 1] + Dict['-'][s2[j - 1]]);
                res[i][j] = max(res[i][j],res[i - 1][j - 1] + Dict[s1[i - 1]][s2[j - 1]]);
            }
        printf("%d\n",res[a][b]);
    }
    return 0;
}
