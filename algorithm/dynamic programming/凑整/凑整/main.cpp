/*
arr数组中凑出s的数
arr[] = {3,34,4,12,5,2}
s = 9
4,5能凑出9

n(i,j)表示用前i个数字凑出数字j  成功是true  失败是false

状态转移方程
n(i,j) = n(i-1,j) = true 用前i-1个数字就能凑出来
n(i,j) = n(i-1,j-v[i])  如果前i-1个数字不能凑出来，则前i-1个数字必能凑出j-v[i]，凑不出来就是false，凑出来就是true

边界条件
n(0,j) = v[i] == j ? true : false;		//前0个数字凑出j,能凑出是true，凑不出是false
n(i,0) = true;		//前i个数字凑出0是true

*/

#include <stdio.h>
#include <Windows.h>

#define N 100

bool dp[N][N] = { 0 };
int v[N] = { 0 };

//非递归
bool isOK(int a[],int n,int target)
{
	for (int i = 0; i < n; ++i)
	{
		for(int j = 0; j <= target; ++j)
		{
			if (j == 0)
			{
				dp[i][j] = true;
			}
			else if(i == 0)
			{
				dp[i][j] = v[0] == j ? true : false;
			}
			else if (dp[i - 1][j] == true)  //如果前i-1个数字能凑出j来，则前i个数字也能凑出j来
			{
				dp[i][j] = true;
			}
			else if (dp[i - 1][j] == false)  //如果前i-1个数字凑不出j来
			{
				if (v[i] <= j)
				{
					dp[i][j] = dp[i - 1][j - v[i]];  //则前i-1个数字必定能凑出j-v[i],否则为false
				}
				else  //v[i] > j，这个数字就不选
				{
					dp[i][j] = false;  //如果v[i]还大于j,则dp[i][j]必为false
				}
			}
		}
	}
	return dp[n - 1][target];
}

//递归
bool R_isOK(int a[], int n, int target)
{
	if (target == 0)
	{
		return true;
	}
	else if (n == 0)
	{
		return a[0] == target;
	}
	else if (a[n - 1] > target)
	{
		return R_isOK(a, n - 1, target);
	}
	else
	{
		bool bOK1 = R_isOK(a, n - 1, target - a[n - 1]);  //选这个数字
		bool bOK2 = R_isOK(a, n - 1, target);  //不选这个数字
		return bOK1 | bOK2;
	}
}

int main()
{
	int target,n;
	scanf("%d%d",&target,&n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &v[i]);
	}
	int flag = isOK(v, n, target);
	flag == 1 ? printf("true\n") : printf("false\n");
	int flag2 = R_isOK(v, n, target);
	flag2 == 1 ? printf("true\n") : printf("false\n");
	system("pause");
	return 0;
}