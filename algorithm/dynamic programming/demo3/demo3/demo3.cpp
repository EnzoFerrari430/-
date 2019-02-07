#include <stdio.h>
#include <Windows.h>
/*
剪绳子问题
给你一根长度为N的绳子，请把绳子剪成M段（m,n都是整数），每段绳子的
长度记为k[0],k[1],k[2]…. 请问如何剪绳子使得k[0],k[1],k[2]
的乘积最大
例如 绳子长度8 最大乘积18 = 2*3*3
*/
/*
这个M段表示剪成任意长度,没有特别指定要剪成几段。

重叠子问题：
	
状态转移方程：
	f(n) = max{f(i)*f(n-i)}
	f(n)代表长度为n的绳子剪成若干段的最大乘积
	求f(n)的最优解就是求f(i)和f(n-i)的最优解
*/

int dp[100] = { 0 };

int fun(int n)
{
	if (1 == n)
	{
		return 0;
	}
	else if (2 == n)
	{
		return 1;
	}
	else if (3 == n)
	{
		return 2;
	}

	//0-3因为不切割当成一个乘数的价值会比切割后因子乘积的价值高。
	//例如3这个数字直接当因子是3，但是切割后最大值只能到2(1*2)
	//从4开始切割后的价值会>=本身的价值
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 3;

	for (int i = 4; i <= n; ++i)
	{
		for (int j = 1; j <= i / 2; ++j)
		{
			if (dp[i] < (dp[j] * dp[i - j]))
			{
				dp[i] = dp[j] * dp[i - j];
			}
		}
	}
	return dp[n];
}

int main()
{
	int length;
	scanf("%d", &length);
	int max_num = fun(length);
	printf("%d\n", max_num);
	system("pause");
	return 0;
}