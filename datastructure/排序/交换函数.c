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
    swap(&c,&d);  //��ֵ���ݣ�������cd��һ�ݿ�������cdûʲô��ϵ��Ҫ�ı�cdҪ��cd�ĵ�ַ��ȥ��
    printf("%d,%d",c,d);



    return 0;
}
