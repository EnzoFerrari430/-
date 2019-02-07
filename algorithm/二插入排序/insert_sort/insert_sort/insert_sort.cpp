#include <stdio.h>
#include <Windows.h>
#include "MyFunctions.h"
/*
	����a[n]
		1.��ʼʱ��a[0]�Գ�һ����������������Ϊa[1....n-1]  ��i = 1
		��a[i]���뵱ǰ������a[0...i-1]���γ���������
		i++���ظ��ڶ���ֱ�� i == n -1
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
				a[j] = a[j - 1];  //���ﲻ�ܽ�������,��Ϊa[i]�����ݿ��ܻᱻǰ������ݸ���
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
		//�ж�j��λ���Ƿ���ԭ����λ�ã����ǵĻ�Ҫ�����ݺ�����j֮��
		if( j != i - 1 )
		{
			temp = a[i];
			for( k = i - 1 ; k > j ; --k )
			{
				a[k + 1] = a[k];
			}
			a[k + 1] = temp;
		}
		//a[j] = temp;  ���� j == i�������a[j]�ᱻ��ֵ���ϴε�temp
		// j == i �Ͳ��û�
	}
}

//�Ż�����Ĳ�������
void insert_sort2(int a[],int n)
{
	int i,j,temp;
	for(int i = 1; i < n ; ++i )
	{
		if( a[i] < a[i - 1] )
		{
			temp = a[i];
			for(j = i - 1 ; j >= 0 && a[j] > temp ; --j)  //�˳������ j < 0 || a[j] <= temp  ���Բ��������˳������������λ�ö���j + 1
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = temp;
		}
	}
}

//�Ż�insert_sort2������ǰһ�����ݸ��Ǻ�һ�����ݵķ���������ʹ��2�����ݽ����ķ�ʽ
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
			//		Swap(&a[j + 1],&a[j]);  //���ǰһ�����Ⱥ�һ������ͽ���
			//	}
			//	else
			//	{
			//		break;  //���û�н����ʹ�������β��������Ѿ����
			//	}
			//}
			
			//����д��  ��������߼�һģһ��
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