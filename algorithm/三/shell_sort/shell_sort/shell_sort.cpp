#include <stdio.h>
#include <Windows.h>


/*
	希尔排序的实质是分组插入排序，又称缩小增量排序。

基本思想：
	先将整个待排元素序列分割成若干子序列（由相隔某个“增量”的元素组成）分别进行直接插入排序，然后依次缩减增量再排序
	待整个序列中的元素基本有序（增量足够小）时，再对全体元素进行一次！！！直接插入排序。因为直接插入排序在元素基本有序的情况下效率是很高的


实验：
	n = 10的一个数组  49,38,65,97,26,13,27,49,55,4

第一次gap = 10 / 2 = 5
49	38	65	97	26	13	27	49	55	4
1a					1b
	2a					2b
		3a					3b				注解:数字相同为同一组，同一组用字母表示是该组的第几个元素
			4a					4b
				5a					5b
第一次排序完成之后
13	27	49	55	4	49	38	65	97	26

第二次gap = 5 / 2 = 2
13	27	49	55	4	49	38	65	97	26
1a		1b		1c		1d		1e
	2a		2b		2c		2d		2e
第二次排序完成之后
4	26	13	27	38	49	49	55	97	65

第三次gap = 2 / 2 = 1
4	26	13	27	38	49	49	55	97	65
1a	1b	1c	1d	1e	1f	1g	1h	1i	1j
第三次排序完成之后
4	13	26	27	38	49	49	55	65	97
*/

void Swap(int *,int *);

void shell_sort(int a[],int n)
{
	int gap,i,j,k,p,temp;
	for( gap = n / 2 ; gap > 0 ; gap /= 2 )
	{
		//每一次gap都是直接插入排序
		for( i = 0 ; i < gap ; ++i )
		{
			//直接插入排序
			for( j = i + gap ; j < n ; j += gap )
			{
				for( k = j - gap ; k >= 0 ; k -= gap)
				{
					if( a[k] < a[j] )
					{
						break;
					}
				}
				if( k != j - gap )
				{
					temp = a[j];
					for( p = j - gap ; p > k ; p -= gap)
					{
						a[p + gap] = a[p];
					}
					a[p + gap] = temp;
				}
			}
		}
	}
}

//优化上面变量太多，优化一下
void shell_sort2(int a[],int n)
{
	int gap,i,j,temp;
	for( gap = n / 2 ; gap > 0 ; gap /= 2 )
	{
		//每一次gap都是直接插入排序
		for( i = 0 ; i < gap ; ++i )
		{
			//temp = a[i];
			for( j = i + gap ; j < n ; j += gap )
			{
				//不能直接2个相邻的数据交换，或者说交换之后还得继续查看与下个数据的对比情况应该要用覆盖的方法
				//if( a[j] < a[j - gap] )
				//{
				//	Swap( &a[j],&a[j-gap] );
				//}
				//else
				//{
				//	break;
				//}
				if( a[j] < a[j - gap] )
				{	
					//先不换数据
					//temp = a[j - gap];
					//a[j - gap] = a[j];
					//记录下这个较小值,安排到合适的位置
					temp = a[j];
					int k = j - gap;
					while( k >= 0 && a[k] > temp)  //这个k>=0 很有可能会安排到最前面 k == 0 的情况
					{
						//往后移  因为前面的数据已经是有序的了，后移覆盖就行
						a[k + gap] = a[k];
						k -= gap;
					}
					a[k + gap] = temp;
				}
			}
		}
	}
}

void Swap(int *a , int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void print(int a[],int n)
{
	int i;
	for( i = 0 ; i < n ; ++i )
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}

int main()
{
	int a[10] = {49,38,65,97,26,13,27,49,55,4};
	shell_sort2(a,10);
	print(a,10);
	system("pause");
	return 0;
}