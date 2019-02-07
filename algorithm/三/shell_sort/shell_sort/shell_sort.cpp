#include <stdio.h>
#include <Windows.h>


/*
	ϣ�������ʵ���Ƿ�����������ֳ���С��������

����˼�룺
	�Ƚ���������Ԫ�����зָ�����������У������ĳ������������Ԫ����ɣ��ֱ����ֱ�Ӳ�������Ȼ��������������������
	�����������е�Ԫ�ػ������������㹻С��ʱ���ٶ�ȫ��Ԫ�ؽ���һ�Σ�����ֱ�Ӳ���������Ϊֱ�Ӳ���������Ԫ�ػ�������������Ч���Ǻܸߵ�


ʵ�飺
	n = 10��һ������  49,38,65,97,26,13,27,49,55,4

��һ��gap = 10 / 2 = 5
49	38	65	97	26	13	27	49	55	4
1a					1b
	2a					2b
		3a					3b				ע��:������ͬΪͬһ�飬ͬһ������ĸ��ʾ�Ǹ���ĵڼ���Ԫ��
			4a					4b
				5a					5b
��һ���������֮��
13	27	49	55	4	49	38	65	97	26

�ڶ���gap = 5 / 2 = 2
13	27	49	55	4	49	38	65	97	26
1a		1b		1c		1d		1e
	2a		2b		2c		2d		2e
�ڶ����������֮��
4	26	13	27	38	49	49	55	97	65

������gap = 2 / 2 = 1
4	26	13	27	38	49	49	55	97	65
1a	1b	1c	1d	1e	1f	1g	1h	1i	1j
�������������֮��
4	13	26	27	38	49	49	55	65	97
*/

void Swap(int *,int *);

void shell_sort(int a[],int n)
{
	int gap,i,j,k,p,temp;
	for( gap = n / 2 ; gap > 0 ; gap /= 2 )
	{
		//ÿһ��gap����ֱ�Ӳ�������
		for( i = 0 ; i < gap ; ++i )
		{
			//ֱ�Ӳ�������
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

//�Ż��������̫�࣬�Ż�һ��
void shell_sort2(int a[],int n)
{
	int gap,i,j,temp;
	for( gap = n / 2 ; gap > 0 ; gap /= 2 )
	{
		//ÿһ��gap����ֱ�Ӳ�������
		for( i = 0 ; i < gap ; ++i )
		{
			//temp = a[i];
			for( j = i + gap ; j < n ; j += gap )
			{
				//����ֱ��2�����ڵ����ݽ���������˵����֮�󻹵ü����鿴���¸����ݵĶԱ����Ӧ��Ҫ�ø��ǵķ���
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
					//�Ȳ�������
					//temp = a[j - gap];
					//a[j - gap] = a[j];
					//��¼�������Сֵ,���ŵ����ʵ�λ��
					temp = a[j];
					int k = j - gap;
					while( k >= 0 && a[k] > temp)  //���k>=0 ���п��ܻᰲ�ŵ���ǰ�� k == 0 �����
					{
						//������  ��Ϊǰ��������Ѿ���������ˣ����Ƹ��Ǿ���
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