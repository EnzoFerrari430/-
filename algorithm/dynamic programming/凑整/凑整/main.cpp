/*
arr�����дճ�s����
arr[] = {3,34,4,12,5,2}
s = 9
4,5�ܴճ�9

n(i,j)��ʾ��ǰi�����ִճ�����j  �ɹ���true  ʧ����false

״̬ת�Ʒ���
n(i,j) = n(i-1,j) = true ��ǰi-1�����־��ܴճ���
n(i,j) = n(i-1,j-v[i])  ���ǰi-1�����ֲ��ܴճ�������ǰi-1�����ֱ��ܴճ�j-v[i]���ղ���������false���ճ�������true

�߽�����
n(0,j) = v[i] == j ? true : false;		//ǰ0�����ִճ�j,�ܴճ���true���ղ�����false
n(i,0) = true;		//ǰi�����ִճ�0��true

*/

#include <stdio.h>
#include <Windows.h>

#define N 100

bool dp[N][N] = { 0 };
int v[N] = { 0 };

//�ǵݹ�
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
			else if (dp[i - 1][j] == true)  //���ǰi-1�������ܴճ�j������ǰi������Ҳ�ܴճ�j��
			{
				dp[i][j] = true;
			}
			else if (dp[i - 1][j] == false)  //���ǰi-1�����ִղ���j��
			{
				if (v[i] <= j)
				{
					dp[i][j] = dp[i - 1][j - v[i]];  //��ǰi-1�����ֱض��ܴճ�j-v[i],����Ϊfalse
				}
				else  //v[i] > j��������־Ͳ�ѡ
				{
					dp[i][j] = false;  //���v[i]������j,��dp[i][j]��Ϊfalse
				}
			}
		}
	}
	return dp[n - 1][target];
}

//�ݹ�
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
		bool bOK1 = R_isOK(a, n - 1, target - a[n - 1]);  //ѡ�������
		bool bOK2 = R_isOK(a, n - 1, target);  //��ѡ�������
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