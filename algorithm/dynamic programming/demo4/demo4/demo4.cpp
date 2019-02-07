#include <stdio.h>
#include <Windows.h>
/*
硬币问题
我们有面值为1元3元5元的硬币若干枚，如何用最少的硬币凑够11元?

重叠子问题

最优子结构

状态转移方程
f(n) = min{f(n-vi)+1}  //f(n)表示凑出n元的最少数目,vi表示当前这枚金币的价值
边界条件
	f(0) = 0;
*/

int a[3] = { 0 };
int value[3] = { 1,3,5 };
int dp[100];
int fun(int n)
{
	dp[0] = 0;
	if (0 == n)
	{
		return 0;
	}
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (value[j] <= i)
			{
				if (dp[i - value[j]] + 1 < dp[i])
				{
					dp[i] = dp[i - value[j]] + 1;
				}
			}
		}
	}
	return dp[n];
}

int main()
{
	for (int i = 0; i < 100; ++i)
	{
		dp[i] = 9999;
	}
	int price;
	scanf("%d",&price);

	int count = fun(price);
	printf("%d\n", count);
	system("pause");
	return 0;
}