#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
using namespace std;

/*
题目描述:
	将整数n划分成k份，且每份不能为空，任意两种划分方案不能相同(不考虑顺序)
例:  n = 7 , k = 3 下面3种划分被认为是相同的
1 1 5
1 5 1
5 1 1

类似0-1背包问题
n(i,j)表示将整数i划分成j份的方案数量

递推关系

*/

#define MAX_NUM 100

class MyClass
{
public:
	MyClass() = default;
	~MyClass() = default;

private:
	int height;
	int width;
};

MyClass PjdCs;

int g_num;

int main()
{
	int n, k;
	int a[MAX_NUM] = { 0 };
	scanf("%d%d", &n, &k);
	system("pause");
	return 0;
}