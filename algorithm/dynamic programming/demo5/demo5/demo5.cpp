/*
给定一个序列，求解它的最长 递增 子序列 的长度。比如： arr[] = {3,1,4,5,9,2,6,5}   的最长递增子序列长度为4。即为：1,4,5,9


dp(i):表示前i个数据的最大递增子序列大小  start表示子序列的起始位置，end表示子序列的末尾位置
状态转移方程：
dp(i) = dp(i - 1) + 1	( end == i-1 && data[i-1] < data[i] ) || ( end - start ) < (dp[i]为末尾位置往前回溯找长度)
dp(i) = dp(i - 1)		end != i-1 || data[i-1] >= data[i]
边界条件：dp(0) = 1;
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define N 100

int main()
{
	int dp[N] = { 0 };
	int suq[N] = { 0 };
	int n, start = 0, end = 0, length = 0;
	int curlen;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &suq[i]);
	}
	dp[0] = 1;
	for (int i = 1; i < n; ++i)
	{
		if (suq[i - 1] < suq[i])
		{
			if (end == i - 1)
			{
				dp[i] = dp[i - 1] + 1;
				end = i;
				continue;
			}
			curlen = 1;
			while (suq[i - curlen] < suq[i-curlen + 1] && curlen <= i)  //往前搜寻有没有可能会更长
			{
				++curlen;
			}
			if (curlen > (end - start + 1))
			{
				dp[i] = dp[i - 1] + 1;
				end = i;
				start = end - curlen + 1;
			}
		}
		else if (suq[i - 1] >= suq[i])
		{
			if (end == i - 1)
			{
				dp[i] = dp[i - 1];
				continue;
			}
		}
	}
	printf("start: %d,end: %d,length: %d\n", start, end, end - start + 1);
	system("pause");
	return 0;
}