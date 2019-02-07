#include <stdio.h>
#include <Windows.h>
#include "MyFunctions.h"
/*
	数组a[n]
		1.初始时，a[0]自成一格有序区，无序区为a[1....n-1]  令i = 1
		将a[i]并入当前有序区a[0...i-1]中形成有序区间
		i++并重复第二步直到 i == n -1
*/



void insert_sort(int a[],int n)
{
	int i,j,k,temp;
	for( i = 1; i < n ; ++i )
	{
		for( j = i - 1 ; j >= 0 ; --j )
		{
			/*
			if( a[i] < a[j - 1] )
			{
				a[j] = a[j - 1];  //这里不能交换数据,因为a[i]的数据可能会被前面的数据覆盖
			}
			else
			{
				//a[j] = temp;
				break;
			}
			*/

			if( a[j] < a[i]  )
			{
				break;
			}
		}
		//判断j的位置是否是原来的位置，不是的话要将数据后移至j之后
		if( j != i - 1 )
		{
			temp = a[i];
			for( k = i - 1 ; k > j ; --k )
			{
				a[k + 1] = a[k];
			}
			a[k + 1] = temp;
		}
		//a[j] = temp;  上面 j == i的情况下a[j]会被赋值成上次的temp
		// j == i 就不用换
	}
}

//优化上面的插入排序
void insert_sort2(int a[],int n)
{
	int i,j,temp;
	for(int i = 1; i < n ; ++i )
	{
		if( a[i] < a[i - 1] )
		{
			temp = a[i];
			for(j = i - 1 ; j >= 0 && a[j] > temp ; --j)  //退出的情况 j < 0 || a[j] <= temp  所以不管哪种退出情况这个插入的位置都是j + 1
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = temp;
		}
	}
}

//优化insert_sort2，不用前一个数据覆盖后一个数据的方法，而是使用2个数据交换的方式
void insert_sort3(int a[],int n)
{
	for(int i = 1 ; i < n ; ++i )
	{
		if( a[i] < a[i - 1] )
		{
			//for( int j = i - 1 ; j >= 0 ; --j )
			//{
			//	if( a[j + 1] < a[j] )
			//	{
			//		Swap(&a[j + 1],&a[j]);  //如果前一个数比后一个数大就交换
			//	}
			//	else
			//	{
			//		break;  //如果没有交换就代表着这次插入排序已经完成
			//	}
			//}
			
			//优秀写法  与上面的逻辑一模一样
			for( int j = i - 1 ; j >= 0 && a[j + 1] < a[j] ; --j)
			{
				PJDSwap(&a[j + 1],&a[j]);
			}

		}
	}
}



int main()
{
	int a[10] = {5,3,7,0,9,4,1,8,2,6};
	insert_sort3(a,10);
	PJDprint(a,10);
	system("pause");
	return 0;
}