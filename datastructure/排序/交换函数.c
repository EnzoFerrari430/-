#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


void swap(int* a,int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int c = 3,d = 4;
    swap(&c,&d);  //按值传递，传的是cd的一份拷贝，与cd没什么关系，要改变cd要传cd的地址进去。
    printf("%d,%d",c,d);



    return 0;
}
