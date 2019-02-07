#include <stdio.h>
#include <Windows.h>

void print(int a[],int n);

void Swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}



//a[start,mid]��һ����������  a[mid + 1,end]�ǵڶ�����������
//Ҫ��:�ϲ�2�����г�Ϊ�µ��������У�O(n)��ʱ�临�Ӷ�  O(1)�Ŀռ临�Ӷ�
void merge_two_list(int a[],int start,int mid,int end)
{
	
}

//ָ���԰��
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
		if( a[j] < a[i] )  //jҪ�ŵ�i���λ�õ�ǰ��
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