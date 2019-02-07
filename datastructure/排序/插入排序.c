#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#define MAXSIZE 100

/*
直接插入排序(Direct Insertion Sort)的基本思想是：
把n个待排序的元素看成为一个有序表和一个无序表。
开始时有序表中只包含1个元素，无序表中包含有n-1个元素，
排序过程中每次从无序表中取出第一个元素，将它插入到有序表中的适当位置，使之成为新的有序表，重复n-1次可完成排序过程。
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

//参数1：数组首地址 参数2：要插入的元素的下标  参数3：元素的值
void insert(int* a,int n,int val)  //插入操作
{
    int pos = 0,i;
    while( pos < n && a[pos] <= val )  //找到插入位置
    {
        ++pos;
    }
    //退出循环的时候pos就是要插入的位置
    for( i = n - 1 ; i >= pos ; --i )  //元素往后移动  用前一个元素覆盖后一个元素
    {
        a[i+1] = a[i];
    }
    a[pos] = val;  //将这个位置的值附成val
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
