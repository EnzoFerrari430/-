#include <stdio.h>
#include <Windows.h>
#include <time.h>

/*
��̬�滮2�����ԣ�
1.�ص�������
2.�����ӽṹ

���ֽ����������������Խ��������ֽ�����������⣬����������⣬Ȼ���������Ľ�õ�ԭ����Ľ�
Fib�����;��������ص������������
Fib��7�� = Fib(6) + Fib(5) = Fib(5) + Fib(4) + Fib(5)����Fib(5)�����ص�������
*/

int gCnt1 = 0;
int gCnt2 = 0;

int Fib(int n)
{
	++gCnt1;
	if (n == 1 || n == 2)
	{
		return  1;
	}
	else
	{
		return Fib(n - 1) + Fib(n - 2);
	}
}

int a[100] = { 0 };
int Fib2(int n)
{
	if (a[n] != 0)
	{
		return a[n];
	}
	else
	{
		++gCnt2;
		if (n == 1 || n == 2)
		{
			a[n] = 1;
			return 1;
		}
		else if (a[n - 1] != 0)
		{
			if (a[n - 2] != 0)
			{
				a[n] = a[n - 1] + a[n - 2];
				return a[n - 1] + a[n - 2];
			}
			else
			{
				return a[n - 1] + Fib2(n - 2);
			}
		}
		else if (a[n - 2] != 0)
		{
			return Fib2(n - 1) + a[n - 2];
		}
		else
		{
			return Fib2(n - 1) + Fib2(n - 2);
		}
	}

}

//1 1 2 3 5 8 13 21 34 55
int main()
{
	time_t start, end;
	int n = 40;
	start = clock();
	printf("%d ",Fib(n));
	end = clock();
	printf("%d %f\n", gCnt1, difftime(end, start));


	start = clock();
	printf("%d ", Fib2(n));
	end = clock();
	printf("%d %f\n", gCnt2, difftime(end, start));


	system("pause");
	return 0;
}