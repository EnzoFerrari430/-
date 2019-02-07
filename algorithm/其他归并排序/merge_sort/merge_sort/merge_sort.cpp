#include <stdio.h>
#include <Windows.h>
#include "MyFunctions.h"

//�㷨��ķ���˼��

void Swap(int *,int *);
void print(int [],int n);



//2����������ĺϲ�
//����1������ͷָ��  ����2����һ���������е���ʼλ��  ����3����һ���������еĽ���λ��  ����4���ڶ����������е���ֹλ��
//���룬��ֱ���ò�������
//���������һ��O(n)ʱ�� O(1)�ռ�Ĳ�������
void insert_sort(int a[],int start,int mid,int end)
{
	//��һ������ [start,mid]
	//�ڶ������� [mid+1,end]
	int j,temp;
	for( int i = mid + 1 ; i <= end ; ++i )
	{
		//�ڶ������е�ÿ��Ԫ����ǰ����
		temp = a[i];
		for( j = i - 1 ; j >= 0 ; --j )
		{
			if( a[j] <= temp)  //�嵽j���λ�õĺ���
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

//�鲢  �����������Ƶķ�ʽʵ����  ʱ�临�Ӷ�O(n)  �ռ临�Ӷ�O(1)��Ҫ��
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
		if(j > k)  //�ж��Ƿ���Ҫ����
		{
			PJDRotateRight(a,i,j-1,j-k);
		}
		i += (j-k+1);  //����λλ�õĺ�һλ��ʼ
	}
}

//�鲢����
void merge_sort(int a[],int start,int end)
{
	//int mid = (end + start) / 2;
	if( start < end )  //mid > 0
	{
		int mid = (end + start) / 2;
		//�ݹ�����
		merge_sort(a,start,mid);
		//�ݹ��Ұ��
		merge_sort(a,mid+1,end);
		//��������
		//insert_sort(a,start,mid,end);
		//�������Ƶķ�ʽ
		merge(a,start,mid,end);
	}
	//insert_sort(a,start,mid,end);  start == end��û��Ҫ���в���������
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