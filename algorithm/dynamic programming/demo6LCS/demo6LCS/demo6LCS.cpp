#include <stdio.h>
#include <Windows.h>
#include <string.h>
/*

问题描述：字符序列的子序列是指从给定字符序列中随意地（不一定连续）去掉若干个字符（可能一个也不去掉）后所形成的字符序列。
	令给定的字符序列X=“x0，x1，…，xm-1”，序列Y=“y0，y1，…，yk-1”是X的子序列，存在X的一个严格递增下标序列<i0，i1，…，ik-1>，使得对所有的j=0，1，…，k-1，有xij=yj。
	例如，X=“ABCBDAB”，Y=“BCDB”是X的一个子序列。

例：对于序列S和T，求它们的最长公共子序列。例如X={A,B,C,B,D,A,B}，Y={B,D,C,A,B,A}则它们的lcs是{B,C,B,A}和{B,D,A,B}。求出一个即可。

递推关系分析：
设A = a[0],a[1],...a[m-1]	B = b[0],b[1],...b[n-1]		AB的LCS为Z = z[0],z[1],...z[k-1]
1.if(a[m-1] == b[n-1])  =>  z[k-1] = a[m-1] = b[n-1]  =>  "a[0],a[1],...a[m-2]"和"b[0],b[1],...b[n-2]"的LCS为"z[0],z[1],...z[k-2]"
2.if(a[m-1] != b[n-1])  =>  if(z[k-1] != a[m-1])  =>  "a[0],a[1],...a[m-2]"和"b[0],b[1],...b[n-1]"的LCS为"z[0],z[1],...z[k-1]"
3.if(a[m-1] != b[n-1])  =>  if(z[k-1] != b[n-1])  =>  "a[0],a[1],...a[m-1]"和"b[0],b[1],...b[n-2]"的LCS为"z[0],z[1],...z[k-1]"

c[i][j]记录X[i]与Y[j]的LCS

边界条件
c[i][j] = 0					if(i == 0 || j == 0)
c[i][j] = c[i-1][j-1] + 1	if(X[i] == Y[j] && i > 0 && j > 0)
c[i][j] = max(c[i][j-1],c[i-1][j])		if(X[i] != Y[j-1] && i > 0 && j > 0)
*/

#define MAXLEN 100

void LCSLength(char* x, char* y, int m, int n, int c[][MAXLEN], int b[][MAXLEN])
{
	int i, j;
	for (i = 0; i <= m; ++i)
	{
		c[i][0] = 0;
	}
	for (j = 0; j < n; ++j)
	{
		c[0][j] = 0;
	}

	for (i = 1; i <= m; ++i)
	{
		for (j = 1; j <= n; ++j)
		{
			if (x[i - 1] == y[j - 1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 0;
			}
			//不等的情况下
			else if (c[i - 1][j] >= c[i][j - 1])  //对应Z[k-1] != a[m-1]
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 1;
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = -1;
			}
		}
	}
}

void PrintLCS(int b[][MAXLEN], char* x, int i, int j)
{
	if (0 == i || 0 == j)
	{
		return;
	}
	if (0 == b[i][j])
	{
		PrintLCS(b, x, i - 1, j - 1);
		printf("%c ",x[i-1]);
	}
	else if (1 == b[i][j])
	{
		//往上走
		PrintLCS(b, x, i - 1, j);
	}
	else
	{
		//往左走
		PrintLCS(b, x, i, j - 1);
	}
}

int main()
{
	char x[MAXLEN] = { "ABCBDAB" };
	char y[MAXLEN] = { "BDCABA" };
	int b[MAXLEN][MAXLEN];  //用来记录搜寻方向
	int c[MAXLEN][MAXLEN];  //用来记录X[i]与Y[j]的LCS长度
	int m, n;
	m = strlen(x);
	n = strlen(y);

	LCSLength(x, y, m, n, c, b);
	PrintLCS(b, x, m, n);
	printf("\n");

	system("pause");
	return 0;
}