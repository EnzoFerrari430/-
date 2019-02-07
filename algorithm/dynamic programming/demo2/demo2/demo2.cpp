#include <stdio.h>
#include <Windows.h>
/*
0-1背包问题
一个贼在偷窃一家商店时发现了n件物品，其中第i件值vi元，重wi磅。
他希望偷走的东西总和越值钱越好，但是他的背包只能放下W磅。
请求解如何放能偷走最大价值的物品，这里vi、wi、W都是整数。
*/
/*
V(i,j)表示将前i个物品装入容量为j(1<= j <= C)的背包获取的最大价值
重叠子问题

最优子结构

状态转移方程
V(i,j) = V(i-1,j)  j < wi
V(i,j) = max( V(i-1,j),V(i-1,j-wi) + vi )  j >= wi
退出条件
V(0,j) = 0;
V(i,0) = 0;
背包的具体物品
xi = 0  V(i,j) = V(i-1,j)  如果V(i,j) = V(i-1,j),则表示xi没有被装入背包
xi = 1,j = j-wi  V(i,j) > V(i-1,j)  如果V(i,j) > V(i-1,j),则表示xi有被装入背包,同时j = j - wi
要构造出这个V(i,j)的表格
*/
//本题背包容量不超过100，物品数量不超过100
int V[100] = { 0 };
int W[100] = { 0 };
int X[100] = { 0 };  //选择情况

int max_dp(int a1, int a2)
{
	if (a1 < a2)
		return a2;
	else
		return a1;
}

//n1容量  n2物品数量,v物品价值,w物品重量
int getMaxValue(int n1,int n2)
{
	//构造出V(i,j)
	int Vp[101][101];
	for (int i = 0; i < 101; ++i)
	{
		Vp[i][0] = 0;//V(i,0) = 0;
	}
	for (int i = 0; i < 101; ++i)
	{
		Vp[0][i] = 0;//V(0,j) = 0;
	}
	
	//i是容量,j是物品种类
	for (int i = 1; i <= n1 ; ++i)
	{
		for (int j = 1; j <= n2; ++j)
		{
			if (i < W[j - 1])  //V(i,j) = V(i-1,j)  j < wi
			{
				Vp[i][j] = Vp[i][j - 1];  //不选当前的物品
			}
			else
			{
				Vp[i][j] = max_dp(Vp[i][j - 1], Vp[i - W[j - 1]][j - 1] + V[j - 1]);  //不选当前物品的最大值和选当前物品的最大值的比较
			}
		}
	}
	//背包的具体物品
	//xi = 0  V(i, j) = V(i - 1, j)  如果V(i, j) = V(i - 1, j), 则表示xi没有被装入背包
	//xi = 1, j = j - wi  V(i, j) > V(i - 1, j)  如果V(i, j) > V(i - 1, j), 则表示xi有被装入背包, 同时j = j - wi
	int c1 = n1;
	int c2 = n2;
	while (c2 > 0)
	{
		if (Vp[c1][c2] > Vp[c1][c2 - 1])
		{
			X[--c2] = 1;
			c1 -= W[c2];
		}
		else
		{
			X[--c2] = 0;
		}
	}
	return Vp[n1][n2];
}
int main()
{
	int n,c;  //物品数量,背包容量
	scanf("%d%d",&n,&c);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&V[i]);
	}
	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&W[i]);
	}
	int max_num = getMaxValue(c, n);
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", X[i]);
	}
	printf("\n%d\n",max_num);
	system("pause");
	return 0;
}