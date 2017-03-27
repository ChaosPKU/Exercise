/*
描述
A tug of war is to be arranged at the local office picnic. For the tug of war, the picnickers must be divided into two teams. Each person must be on one team or the other; the number of people on the two teams must not differ by more than 1; the total weight of the people on each team should be as nearly equal as possible.
输入
The first line of input contains n the number of people at the picnic. n lines follow. The first line gives the weight of person 1; the second the weight of person 2; and so on. Each weight is an integer between 1 and 450. There are at most 100 people at the picnic.
输出
Your output will be a single line containing 2 numbers: the total weight of the people on one team, and the total weight of the people on the other team. If these numbers differ, give the lesser first.
样例输入
3
100
90
200
样例输出
190 200

*/

#include <stdio.h>
#include <iostream>
using namespace std;
#define min(a,b) (a<b?a:b)
bool Mat[52][45005] = {0};
int W[105] = {0}, sum[105] = {0};
int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 1; i <= N; ++ i){
		scanf("%d", &W[i]);
		sum[i] = sum[i - 1] + W[i];
	}
	Mat[0][0] = 1;
	for (int i = 1; i <= N; ++ i) 
		for (int j = min((N + 1) / 2, i); j > 0; -- j)
			for (int w = sum[N] / 2; w >= W[i]; -- w)
				Mat[j][w] = Mat[j][w] || Mat[j - 1][w - W[i]];
	int ans = 0;
	for (int w = sum[N] / 2; w > 0; --w){
		if(Mat[N/2][w] || Mat[(N+1)/2][w]){
			ans = w;
			break;
		}
	}
	printf("%d %d\n", ans, sum[N] - ans);
	return 0;
}
