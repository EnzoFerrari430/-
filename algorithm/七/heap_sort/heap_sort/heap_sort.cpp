#include <stdio.h>
#include <Windows.h>
/*
���������ȫ�����������ǽ��Ƶ���ȫ������
����������2�����ԣ�
	1.���ڵ�ļ�ֵ���Ǵ��ڵ��ڣ�����С�ڵ��ڣ��κ�һ���ӽڵ�ļ�ֵ
	2.ÿ���ڵ��������������������һ�������
�����ڵ�ļ�ֵ���Ǵ��ڵ����κ�һ���ӽڵ�ļ�ֵʱΪ���ѣ���֮Ϊ��С�ѡ�
��һ�㶼����������ʾ��i�ڵ�ĸ��ڵ���±����(i - 1) / 2��
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


//  �¼���i�ڵ㣬�丸�ڵ�Ϊ(i-1)/2
void MinHeapFixup(int a[] ,int i)
{
	int j,temp;
	temp = a[i];
	j = (i - 1) / 2;  //���ڵ�
	while( j >= 0 && i != 0 )
	{
		if(j >= 0 && i != 0)
		{
			break;
		}
		a[i] = temp;
		i = j;  //�򸸽ڵ�ݹ�,��ǰ���i��ʾ���ڵ� 
		j = (i - 1) / 2;
	}
	a[i] = temp;
}

//�ѵĲ���
void MinHeapAddNumber(int a[],int n,int nNum)
{
	a[n] = nNum;
	MinHeapFixup(a,n);
}

//������
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

//����С����ɾ����
void MinHeapDeleteNumber( int a[],int n )
{
	Swap( &a[0] ,&a[n - 1] );
	MinHeapFixdown(a,0,n - 1);
	Print(a,n);
}

//������С��
void MakeMinHeap(int a[],int n)
{
	//Ҷ�ӽڵ㲻����
	for( int i = n / 2 - 1 ; i >= 0 ; --i)
	{
		MinHeapFixdown(a,i,n);
		printf("�³��Ľڵ�%d. ",i);
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