#include <stdio.h>
#include <stdlib.h>


typedef struct A
{
    char* p;
}CA;

void fun1(char* p)
{
    p = 0x11111111;
}

void fun2(CA *pp)
{
    pp->p = 0x11111111;
}

int main()
{
    char *p = 0x12345678;

    printf("%p\n",p);
    fun1(p);
    printf("%p\n",p);

    CA *pp = (CA*)malloc(sizeof(CA));
    pp->p = 0x12345678;
    fun1(pp->p);
    printf("%p\n",pp->p);

    fun2(pp);
    printf("%p\n",pp->p);


    return 0;
}
