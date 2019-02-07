#include <stdio.h>
#include <Windows.h>

/*
	鸡尾酒排序就是双向冒泡排序
	先找到最小的数字，把他放到第一位，然后找到最大的数字，放到最后一位。
	然后再找第二小的数字放到第二位，再找第二大的数字放到倒数第二位，以此类推，直到完成排序
*/

void Swap(int *,int *);
void print(int[],int);

void cocktail_sort(int a[],int n)
{
	int bottom = 0,top = n -1;  //元素下标
	int swapped = 1;
	int bound = 0;  //优化循环次数,记录已经排序的边界，减少循环次数
	while(swapped)
	{
		swapped = false;  //进来就设置成false，如果一遍一下都没有交换就证明已经排序完全
		//从前往后找
		for( int i = bottom; i < top ; ++i )
		{
			if( a[i + 1] < a[i] )
			{
				Swap(&a[i + 1],&a[i]);  //如果前一个数比后一个数大，就交换2个元素
				swapped = true;
				bound = i;
			}
		}
		top = bound;
		//从后往前找
		for(int i = top ; i > bottom ; --i)
		{
			if( a[i] < a[i - 1] )  //如果前一个数比后一个数大，就交换2个元素
			{
				Swap(&a[i],&a[i - 1]);
				swapped = true;
				bound = i;
			}
		}
		bottom = bound;
	}
}

void Swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print(int a[],int n)
{
	for(int i = 0 ; i < n ; ++i)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}

int main()
{
	int a[10] = {9,8,7,6,5,4,3,2,1,0};
	cocktail_sort(a,10);
	print(a,10);

	system("pause");
	return 0;
}