#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include <time.h>

//形参是一个大小为n的整形数组
void array_init(int* a,int n )
{
    int i;
    for(i = 0 ;i < n ;++i)
    {
        a[i] = rand() % n;
    }
}

void swap(int* a,int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int* a,int n)
{
    int i,j;
    for(i = 0 ;i < n - 1; ++i)
    {
        for(j = 0; j< n - i - 1 ;++j)
        {
            if( a[j+1] < a[j] )
            {
                swap( &a[j],&a[j+1] );
            }
        }
    }
}

int trans(int i)
{
    i += 10;
    return i;


}

void Display(int* a,int n)
{
    int i;
    for( i = 0 ; i < n ; ++i )
    {
        printf("%d\n",a[i]);
    }
}

int main()
{
    srand(time(0));
    int a[100000];
    array_init(a,100000);
    sort(a,100000);
    //Display(a,1000);

    printf("over\n");

    return 0;
}
