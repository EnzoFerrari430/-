#include <stdio.h>
#include <string.h>

int main()
{
    char *p = "hello world";
    printf("%s\n",p);
    printf("%d\n",strlen(p));


    char *str = p + 4;
    printf("%s\n",str);
    printf("%d\n",strlen(str));





    return 0;
}
