#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define MAXSIZE 100


/*

实现接口：
    1.2个有序数组的合并


算法复杂度:O(1) < O(logn) < O(n) < O(nlogn) < O(n^2) < O(n^3) < O(2^n) < O(n!) < O(n^n)

快速排序和归并排序时间复杂度都是O(nlogn)

*/

//形参是一个大小为n的整形数组
void array_init(int* a,int n )
{
    int i;
    for(i = 0 ;i < n ;++i)
    {
        a[i] = rand() % (2*n);
    }
}

//2个有序数组的合并,参数1：数组首地址 参数2： 第一个有序数组的起始下标  参数3：第一个有序数组的末尾下标  参数4：第二个有序数组的末尾下标
void merge( int* a,int start,int mid,int end )
{
    int Astart = start;
    int Bstart = mid+1;

    //int p[end-start+1];  p是数组名字不能进行自增运算
    //int* pp = p;  这样之后可以对pp进行自增
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

    memcpy( a+start,q,4*(end-start+1) );  //要传入q不能是p  因为p的位置被改动过
    free(q);
}

void merge_sort(int* a,int start,int end)
{
    int middle = (start + end )/2;

    if( start >= end )
    {
        return ;  //递归的出口
    }
    merge_sort(a,start,middle);  //递归出左半部分  递归到最后只有2个元素
    merge_sort(a,middle+1,end);  //递归出右半部分
    merge(a,start,middle,end);   //归并排序
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
