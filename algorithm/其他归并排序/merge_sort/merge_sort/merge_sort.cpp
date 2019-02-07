#include <stdio.h>
#include <Windows.h>
#include "MyFunctions.h"

//算法里的分治思想

void Swap(int *,int *);
void print(int [],int n);



//2个有序数组的合并
//参数1：数组头指针  参数2：第一个有序序列的起始位置  参数3：第一个有序序列的结束位置  参数4：第二个有序序列的终止位置
//猜想，能直接用插入排序
//提升：完成一个O(n)时间 O(1)空间的插入排序
void insert_sort(int a[],int start,int mid,int end)
{
	//第一个序列 [start,mid]
	//第二个序列 [mid+1,end]
	int j,temp;
	for( int i = mid + 1 ; i <= end ; ++i )
	{
		//第二个序列的每个元素往前插入
		temp = a[i];
		for( j = i - 1 ; j >= 0 ; --j )
		{
			if( a[j] <= temp)  //插到j这个位置的后面
			{
				break;
			}
			else  //temp < a[j]
			{
				a[j + 1] = a[j];
			}
		}
		a[j + 1] = temp;
	}
}

//归并  这种数组右移的方式实现了  时间复杂度O(n)  空间复杂度O(1)的要求
void merge(int a[],int begin,int mid,int end)
{
	int i,j,k;
	i = begin;
	j = mid + 1;
	while( i <= end && j <= end && i < j )
	{
		while( i <= end && a[i] < a[j] )
		{
			++i;
		}
		k = j;
		while( j <= end && a[j] < a[i] )
		{
			++j;
		}
		if(j > k)  //判断是否需要右移
		{
			PJDRotateRight(a,i,j-1,j-k);
		}
		i += (j-k+1);  //从移位位置的后一位开始
	}
}

//归并排序
void merge_sort(int a[],int start,int end)
{
	//int mid = (end + start) / 2;
	if( start < end )  //mid > 0
	{
		int mid = (end + start) / 2;
		//递归左半边
		merge_sort(a,start,mid);
		//递归右半边
		merge_sort(a,mid+1,end);
		//插入排序
		//insert_sort(a,start,mid,end);
		//数组右移的方式
		merge(a,start,mid,end);
	}
	//insert_sort(a,start,mid,end);  start == end就没必要进行插入排序了
}

void Swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print(int a[],int n)
{
	for(int i = 0 ; i < n ; ++i )
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}

int main()
{
	int a[10] = {1,3,5,7,9,0,2,4,6,8};
	insert_sort(a,0,4,9);
	PJDprint(a,10);
	int b[10] = {5,2,1,8,3,9,4,7,6,0};
	merge_sort(b,0,9);
	PJDprint(b,10);
	system("pause");
	return 0;
}