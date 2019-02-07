#include <stdio.h>
#include <Windows.h>
/*
二叉堆是完全二叉树或者是近似的完全二叉树
二叉树满足2个特性：
	1.父节点的键值总是大于等于（或者小于等于）任何一个子节点的键值
	2.每个节点的左子树和右子树都是一个二叉堆
当父节点的键值总是大于等于任何一个子节点的键值时为最大堆，反之为最小堆。
堆一般都用数组来表示，i节点的父节点的下表就是(i - 1) / 2。
*/

void Swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Print(int a[],int n)
{
	for( int i = 0 ; i < n ; ++i )
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}


//  新加入i节点，其父节点为(i-1)/2
void MinHeapFixup(int a[] ,int i)
{
	int j,temp;
	temp = a[i];
	j = (i - 1) / 2;  //父节点
	while( j >= 0 && i != 0 )
	{
		if(j >= 0 && i != 0)
		{
			break;
		}
		a[i] = temp;
		i = j;  //向父节点递归,当前这个i表示父节点 
		j = (i - 1) / 2;
	}
	a[i] = temp;
}

//堆的插入
void MinHeapAddNumber(int a[],int n,int nNum)
{
	a[n] = nNum;
	MinHeapFixup(a,n);
}

//调整堆
void MinHeapFixdown(int a[],int i,int n)
{
	int j,temp;
	temp = a[i];
	j = 2 * i + 1;
	while( j < n )
	{
		if( j + 1 < n && a[j + 1] < a[j] )
		{
			++j;
		}
		if( a[j] >= temp )
		{
			break;
		}
		a[i] = a[j];
		i = j;
		j = 2 * i + 1;
	}
	a[i] = temp;
}

//在最小堆中删除数
void MinHeapDeleteNumber( int a[],int n )
{
	Swap( &a[0] ,&a[n - 1] );
	MinHeapFixdown(a,0,n - 1);
	Print(a,n);
}

//建立最小堆
void MakeMinHeap(int a[],int n)
{
	//叶子节点不用排
	for( int i = n / 2 - 1 ; i >= 0 ; --i)
	{
		MinHeapFixdown(a,i,n);
		printf("下沉的节点%d. ",i);
		Print(a,n);
	}
}

void MinheapsortTodescendarray(int a[],int n)
{
	MakeMinHeap(a,n);
	for( int i = n ; i >= 1 ; --i )
	{
		MinHeapDeleteNumber(a,i);
	}
}

int main()
{
	int a[10] = {9,12,17,30,50,20,60,65,4,49};
	MinheapsortTodescendarray(a,10);
	for( int i = 0 ; i < 10 ; ++i )
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}