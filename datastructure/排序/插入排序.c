#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#define MAXSIZE 100

/*
ֱ�Ӳ�������(Direct Insertion Sort)�Ļ���˼���ǣ�
��n���������Ԫ�ؿ���Ϊһ��������һ�������
��ʼʱ�������ֻ����1��Ԫ�أ�������а�����n-1��Ԫ�أ�
���������ÿ�δ��������ȡ����һ��Ԫ�أ��������뵽������е��ʵ�λ�ã�ʹ֮��Ϊ�µ�������ظ�n-1�ο����������̡�
*/

void Display(int* a,int n)
{
    int i;
    for( i = 0 ; i < n ;++i)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}

//����1�������׵�ַ ����2��Ҫ�����Ԫ�ص��±�  ����3��Ԫ�ص�ֵ
void insert(int* a,int n,int val)  //�������
{
    int pos = 0,i;
    while( pos < n && a[pos] <= val )  //�ҵ�����λ��
    {
        ++pos;
    }
    //�˳�ѭ����ʱ��pos����Ҫ�����λ��
    for( i = n - 1 ; i >= pos ; --i )  //Ԫ�������ƶ�  ��ǰһ��Ԫ�ظ��Ǻ�һ��Ԫ��
    {
        a[i+1] = a[i];
    }
    a[pos] = val;  //�����λ�õ�ֵ����val
}


void insert_sort(int* a,int n)
{
    int i;
    for( i = 1 ; i < n ; ++i)
    {
        insert(a,i,a[i]);
    }
}

int main()
{
    int a[10] = {1,3,0,1,0,5,0,2,2,4};
    Display(a,10);
    insert_sort(a,10);
    Display(a,10);

    return 0;
}
