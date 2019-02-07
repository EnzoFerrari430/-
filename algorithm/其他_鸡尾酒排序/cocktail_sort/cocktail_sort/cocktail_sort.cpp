#include <stdio.h>
#include <Windows.h>

/*
	��β���������˫��ð������
	���ҵ���С�����֣������ŵ���һλ��Ȼ���ҵ��������֣��ŵ����һλ��
	Ȼ�����ҵڶ�С�����ַŵ��ڶ�λ�����ҵڶ�������ַŵ������ڶ�λ���Դ����ƣ�ֱ���������
*/

void Swap(int *,int *);
void print(int[],int);

void cocktail_sort(int a[],int n)
{
	int bottom = 0,top = n -1;  //Ԫ���±�
	int swapped = 1;
	int bound = 0;  //�Ż�ѭ������,��¼�Ѿ�����ı߽磬����ѭ������
	while(swapped)
	{
		swapped = false;  //���������ó�false�����һ��һ�¶�û�н�����֤���Ѿ�������ȫ
		//��ǰ������
		for( int i = bottom; i < top ; ++i )
		{
			if( a[i + 1] < a[i] )
			{
				Swap(&a[i + 1],&a[i]);  //���ǰһ�����Ⱥ�һ�����󣬾ͽ���2��Ԫ��
				swapped = true;
				bound = i;
			}
		}
		top = bound;
		//�Ӻ���ǰ��
		for(int i = top ; i > bottom ; --i)
		{
			if( a[i] < a[i - 1] )  //���ǰһ�����Ⱥ�һ�����󣬾ͽ���2��Ԫ��
			{
				Swap(&a[i],&a[i - 1]);
				swapped = true;
				bound = i;
			}
		}
		bottom = bound;
	}
}

void Swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
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
	int a[10] = {9,8,7,6,5,4,3,2,1,0};
	cocktail_sort(a,10);
	print(a,10);

	system("pause");
	return 0;
}