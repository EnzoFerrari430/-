#include <stdio.h>
#include <Windows.h>
#include "MyFunctions.h"

/*
	快速排序采用了一种分治的策略。
	基本思想
		1.先从数列中取出一个数作为基准数
		2.分区过程，将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边
		3.再对左右区间重复第二步，直到各区间只有一个数
	简单来说：挖坑填数 + 分治法


例子：
	0	1	2	3	4	5	6	7	8	9
	72	6	57	88	60	42	83	73	48	85
初始时，i = 0; j = 9 ; X = a[i] = 72
由于将a[0]中的数据保存到X中，可以理解成在数组a[0]上挖了个坑，可以将数据填充到这里来
从j开始向前找一个 <= X的数。当j = 8，符合条件，将a[8]挖出再填到上一个坑a[0]中。a[0] = a[8];  ++i;
这样从i开始向后找一个大于X的数，当i = 3，符合条件，将a[3]挖出再填到上一个坑中a[8] = a[3];  --j;

数组变为
	0	1	2	3	4	5	6	7	8	9
	48	6	57	88	60	42	83	73	88	85
i = 3; j = 7; X = 72;
重复上面步骤  先从后往前找，再从前往后找
从j开始往前找，当j = 5时，符合条件，将a[5]挖出填到上一个坑中，a[3] = a[5]; ++i;
从i开始往后找，当i = 5时，由于i==j退出。
最后将X填入a[5]中。
*/
int divide(int a[],int start,int end)
{
	int i = start,j = end,temp;
	temp = a[i];
	while( i < j )
	{
		while(i < j && temp < a[j])
		{
			--j;
		}
		if( i < j)
		{
			a[i] = a[j];  //把a[i]的坑用a[j]填上，现在a[j]是一个坑
			++i;
		}
		while(i < j && temp >= a[i])
		{
			++i;
		}
		if( i < j )
		{
			a[j] = a[i];
			--j;
		}
	}
	a[i] = temp;
	printf("起始位置%d  中间位置%d  末尾位置%d  ",start,i,end);
	PJDprint(a,10);
	return i;
}

void quick_sort(int a[],int start,int end)
{
	if(start < end)
	{
		int mid = divide(a,start,end);
		quick_sort(a,start,mid-1);
		quick_sort(a,mid+1,end);
	}
}



int main()
{
	int a[10] = {72,6,57,88,60,42,83,73,48,85};
	PJDprint(a,10);
	quick_sort(a,0,9);
	system("pause");
	return 0;
}