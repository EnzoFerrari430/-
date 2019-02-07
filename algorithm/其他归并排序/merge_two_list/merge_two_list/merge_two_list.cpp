#include <stdio.h>
#include <Windows.h>

void print(int a[],int n);

void Swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}



//a[start,mid]是一个有序序列  a[mid + 1,end]是第二个有序序列
//要求:合并2个序列成为新的有序序列，O(n)的时间复杂度  O(1)的空间复杂度
void merge_two_list(int a[],int start,int mid,int end)
{
	
}

//指定对半分
void func(int a[],int n)
{
	int i,j;
	if( n <= 0 )
	{
		return ;
	}
	i = 0 ; 
	j = n / 2;
	while(j < n && i < j)
	{
		if( a[j] < a[i] )  //j要放到i这个位置的前面
		{
			Swap(&a[j],&a[i]);
			for(int k = j - 1; k > i ; --k)
			{
				Swap(&a[k+1],&a[k]);
			}
			++i;
			++j;
		}
		else  //a[i] < a[j]
		{
			++i;
		}
	}
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
	int a[10] = {1,3,5,7,9,0,2,4,6,8};
	func(a,10);
	print(a,10);
	system("pause");
	return 0;
}