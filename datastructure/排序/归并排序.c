#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define MAXSIZE 100


/*

ʵ�ֽӿڣ�
    1.2����������ĺϲ�


�㷨���Ӷ�:O(1) < O(logn) < O(n) < O(nlogn) < O(n^2) < O(n^3) < O(2^n) < O(n!) < O(n^n)

��������͹鲢����ʱ�临�Ӷȶ���O(nlogn)

*/

//�β���һ����СΪn����������
void array_init(int* a,int n )
{
    int i;
    for(i = 0 ;i < n ;++i)
    {
        a[i] = rand() % (2*n);
    }
}

//2����������ĺϲ�,����1�������׵�ַ ����2�� ��һ�������������ʼ�±�  ����3����һ�����������ĩβ�±�  ����4���ڶ������������ĩβ�±�
void merge( int* a,int start,int mid,int end )
{
    int Astart = start;
    int Bstart = mid+1;

    //int p[end-start+1];  p���������ֲ��ܽ�����������
    //int* pp = p;  ����֮����Զ�pp��������
    int* p = (int*)malloc(4*(end-start+1));
    assert( p != NULL );
    int* q = p;
    while( Astart <= mid && Bstart <= end )
    {
        if( a[Astart] < a[Bstart] )
        {
            *p = a[Astart];
            ++p;
            ++Astart;
        }
        else
        {
            *p = a[Bstart];
            ++p;
            ++Bstart;
        }
    }

    while( Astart <= mid )
    {
        *p = a[Astart];
        ++p;
        ++Astart;
    }

    while( Bstart <= end )
    {
        *p = a[Bstart];
        ++p;
        ++Bstart;
    }

    memcpy( a+start,q,4*(end-start+1) );  //Ҫ����q������p  ��Ϊp��λ�ñ��Ķ���
    free(q);
}

void merge_sort(int* a,int start,int end)
{
    int middle = (start + end )/2;

    if( start >= end )
    {
        return ;  //�ݹ�ĳ���
    }
    merge_sort(a,start,middle);  //�ݹ����벿��  �ݹ鵽���ֻ��2��Ԫ��
    merge_sort(a,middle+1,end);  //�ݹ���Ұ벿��
    merge(a,start,middle,end);   //�鲢����
}

void Display(int* a,int n)
{
    int i;
    for( i = 0 ; i < n ;++i )
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(0));
    int a[MAXSIZE];
    array_init(a,MAXSIZE);
    merge_sort(a,0,MAXSIZE-1);
    Display(a,MAXSIZE);

    return 0;
}
