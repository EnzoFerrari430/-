/*
��һ��������ѡ��һϵ�����֣�ʹ�ú�������ֲ�������


״̬ת�Ʒ���:
dp[i] = max(dp[i - 1] , dp[i - 2] + v[i])
�߽�����
dp[0] = v[0]
dp[1] = max(v[0],v[1])

*/

#include <stdio.h>
#include <Windows.h>

#define N 100

int dp[N] = { 0 };
int v[N] = { 0 };
int get_max(int a, int b)
{
	if (a < b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

int max_value(int n)
{
	dp[0] = v[0];
	dp[1] = get_max(v[0], v[1]);
	if (1 == n)
	{
		return dp[0];
	}
	if (2 == n)
	{
		return dp[1];
	}
	for (int i = 2; i < n; ++i)
	{
		dp[i] = get_max(dp[i - 1], dp[i - 2] + v[i]);
	}
	return dp[n - 1];
}

int main()
{
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &v[i]);
	}
	int sum = max_value(n);
	printf("%d\n", dp[n - 1]);
	system("pause");
}