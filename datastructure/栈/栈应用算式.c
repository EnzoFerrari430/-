#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
/*
中缀表达式转后缀表达式
    对于数字：直接输出
    对于符号：
        左括号：进栈
        符号：与栈顶符号进行优先级比较
            栈顶符号优先级低：进栈
            栈顶符号优先级不低：将栈顶符号弹出并输出，之后进栈
        右括号：将栈顶符号弹出并输出，直到匹配左括号

    遍历结束：将栈中所有符号弹出并输出


遍历后缀表达式，得到结果
    对于数字：进栈
    对于符号：
        从栈中弹出右操作数
        从栈中弹出左操作数
        根据符号进行运算
        将结果压如栈中

    遍历结束，栈中的唯一数字就是计算结果

*/

typedef struct node
{
    int data;
    struct node* next;
}Node;

typedef struct stack
{
    Node* top;
}Stack;

Stack* stack_init()
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    assert(stack != NULL);

    stack->top = NULL;
    return stack;
}

int stack_empty(Stack* stack)
{
    if(stack->top == NULL)
    {
        return 1;
    }
    return 0;
}

void push(Stack* stack,int data)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL);

    pnew->data = data;


    pnew->next = stack->top;
    stack->top = pnew;
}

int get_top(Stack* stack)
{
    Node* p = stack->top;
    if( p == NULL )
    {
        return -99;
    }
    return p->data;
}

void pop(Stack* stack)
{
    if( stack_empty(stack) == 1 )
    {
        return ;
    }
    Node* p = stack->top;
    stack->top = p->next;
    free(p);
    return ;
}

void emptystack(Stack* stack)
{
    while(stack_empty(stack) != 1)
    {
        pop(stack);
    }
    return ;
}

void stack_destroy(Stack** stack)
{
    emptystack(*stack);
    free(*stack);
    *stack = NULL;
}

int isnumber(char ch)
{
    if( ch >='0' && ch <='9' )
    {
        return 1;
    }
    return 0;
}

int isYun(char ch)
{
    if( ch == '+' || ch == '-' || ch == '*' || ch == '/')
    {
        return 1;
    }
    return 0;
}

int isLeftK(char ch)
{
    if( ch == '(' || ch == '[' || ch == '{')
    {
        return 1;
    }
    return 0;
}

int isRightK(char ch)
{
    if(ch == ')' || ch == ']' || ch == '}')
    {
        return 1;
    }
    return 0;
}


//将运算符转化为int比较,运算符优先级
int yunswapint(char ch)
{
    if(ch == '*' || ch == '/')
    {
        return 3;
    }
    if(ch == '+' || ch == '-')
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

int compareYun(char ch1,char ch2)
{
    int p1 = yunswapint(ch1);
    int p2 = yunswapint(ch2);

    if( p1 >= p2)
    {
        return 1;
    }
    return 0;
}




void swapString(char* buf,char* src)
{
    char ch;
    Stack *stack = stack_init();
    //遍历字符串
    while( *buf != '0' )
    {
        if( isnumber(*buf) == 1 )  //数字
        {
            *src = *buf;
            src++;
            buf++;
        }
        else if(isLeftK(*buf) == 1)  //左括号
        {
            push(stack,*buf);
            buf++;
        }
        else if(isRightK(*buf) == 1)
        {
            ch = get_top(stack);  //取出栈顶元素
            while( isLeftK(ch) != 1 )
            {
                *src = ch;
                src++;
                pop(stack);
                ch = get_top(stack);
            }
            pop(stack);
            buf++;
        }
        else if(isYun(*buf) == 1)
        {
            ch = get_top(stack);
            if(compareYun(ch ,*buf) == 0)
            {
                //栈顶元素优先级比较低
                push(stack,*buf);
                buf++;
            }
            else if(compareYun(ch,*buf) == 1)
            {
                *src = ch;
                src++;
                pop(stack);
                push(stack,*buf);
                buf++;
            }
        }
        else
        {
            buf++;
        }
    }
    while( stack_empty(stack) != 1)
    {
        ch = get_top(stack);
        *src = ch;
        src++;
        pop(stack);
    }

    stack_destroy(&stack);
}

int JiSuan(int a,int b,char ch)
{
    if( ch == '+' )
    {
        return a + b;
    }
    else if(ch == '-' )
    {
        return a - b;
    }
    else if( ch == '*' )
    {
        return a * b;
    }
    else if( ch == '/' )
    {
        return a/ b;
    }
}


int fun(char* src)
{
    int a,b,c;
    Stack *stack = stack_init();
    while(*src != 0)
    {
        if(isnumber(*src) == 1)
        {
            push(stack,*src - '0');  //将数字进栈
            src++;
        }
        else if(isYun(*src) == 1)
        {
            b = get_top(stack);  //右操作数
            pop(stack);
            a = get_top(stack);  //左操作数
            pop(stack);
            c = JiSuan(a,b,*src);  //a是左操作数，b是右操作数 c是运算符
            push(stack,c);
            src++;
        }
    }
    int data = get_top(stack);
    stack_destroy(&stack);
    return data;
}


int main()
{
    char buf[30] = {0};
    char src[30] = {0};

    fgets(buf,30,stdin);  //输入一行字符串
    buf[strlen(buf) - 1] = 0;  //去除换行
    swapString(buf,src);  //将buf的中缀表达式转化为后缀表达式
    printf("%s\n",src);
    int data = fun(src);
    printf("%d\n",data);

    return 0;
}
