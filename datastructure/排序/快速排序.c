#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include <time.h>

/*
    快速排序的中心思想:
    1.寻找一个中心元素（通常为第一个数）
    2.将小于中心点的元素移动至中心点之前，将大于中心点的元素移动至中心点之后
    3.对上步分成的2个无序数组段重复1 2 操作直至断长为1为止


    定义一个i和j  i在起始位置  j在末尾位置

*/

//形参是一个大小为n的整形数组
void array_init(int* a,int n )
{
    int i;
    for(i = 0 ;i < n ;++i)
    {
        a[i] = rand() % n;
    }
}

void swap(int *a,int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}




int getcenterpos(int* a,int i,int j)
{
    int key;
    key = a[i];
    for(;i < j;)
    {
        //一开始是从后面往前面--
        while( a[j] >= key && i != j )
        {
            --j;
        }
        swap( &a[i],&a[j] );
        //发生一次交换之后，从前面往后面++
        while( a[i] < key && i != j )
        {
            ++i;
        }
        swap(&a[i],&a[j]);
    }
    return i;  //返回中心元素的下标
}

void quick_sort(int* a,int i,int j)
{
    //只有一个元素的判断条件
    if( i >= j )
    {
        return ;
    }


    int mid = getcenterpos(a,i,j);
    //左半部分
    quick_sort( a,i,mid-1);
    //右半部分
    quick_sort( a,mid+1,j);


}

void Display(int* a,int n)
{
    int i;
    for( i = 0 ; i < n ;++i )
    {
        printf("%d ",a[i]);
    }
}

int main()
{
    srand(time(0));
    int a[100000];
    array_init(a,100000);
    quick_sort(a,0,99999);
    //Display(a,10);
    printf("over\n");
    return 0;
}
