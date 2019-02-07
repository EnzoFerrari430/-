#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include <time.h>

/*
    �������������˼��:
    1.Ѱ��һ������Ԫ�أ�ͨ��Ϊ��һ������
    2.��С�����ĵ��Ԫ���ƶ������ĵ�֮ǰ�����������ĵ��Ԫ���ƶ������ĵ�֮��
    3.���ϲ��ֳɵ�2������������ظ�1 2 ����ֱ���ϳ�Ϊ1Ϊֹ


    ����һ��i��j  i����ʼλ��  j��ĩβλ��

*/

//�β���һ����СΪn����������
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
        //һ��ʼ�ǴӺ�����ǰ��--
        while( a[j] >= key && i != j )
        {
            --j;
        }
        swap( &a[i],&a[j] );
        //����һ�ν���֮�󣬴�ǰ��������++
        while( a[i] < key && i != j )
        {
            ++i;
        }
        swap(&a[i],&a[j]);
    }
    return i;  //��������Ԫ�ص��±�
}

void quick_sort(int* a,int i,int j)
{
    //ֻ��һ��Ԫ�ص��ж�����
    if( i >= j )
    {
        return ;
    }


    int mid = getcenterpos(a,i,j);
    //��벿��
    quick_sort( a,i,mid-1);
    //�Ұ벿��
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
