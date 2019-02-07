#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
/*
��׺���ʽת��׺���ʽ
    �������֣�ֱ�����
    ���ڷ��ţ�
        �����ţ���ջ
        ���ţ���ջ�����Ž������ȼ��Ƚ�
            ջ���������ȼ��ͣ���ջ
            ջ���������ȼ����ͣ���ջ�����ŵ����������֮���ջ
        �����ţ���ջ�����ŵ����������ֱ��ƥ��������

    ������������ջ�����з��ŵ��������


������׺���ʽ���õ����
    �������֣���ջ
    ���ڷ��ţ�
        ��ջ�е����Ҳ�����
        ��ջ�е����������
        ���ݷ��Ž�������
        �����ѹ��ջ��

    ����������ջ�е�Ψһ���־��Ǽ�����

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


//�������ת��Ϊint�Ƚ�,��������ȼ�
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
    //�����ַ���
    while( *buf != '0' )
    {
        if( isnumber(*buf) == 1 )  //����
        {
            *src = *buf;
            src++;
            buf++;
        }
        else if(isLeftK(*buf) == 1)  //������
        {
            push(stack,*buf);
            buf++;
        }
        else if(isRightK(*buf) == 1)
        {
            ch = get_top(stack);  //ȡ��ջ��Ԫ��
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
                //ջ��Ԫ�����ȼ��Ƚϵ�
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
            push(stack,*src - '0');  //�����ֽ�ջ
            src++;
        }
        else if(isYun(*src) == 1)
        {
            b = get_top(stack);  //�Ҳ�����
            pop(stack);
            a = get_top(stack);  //�������
            pop(stack);
            c = JiSuan(a,b,*src);  //a�����������b���Ҳ����� c�������
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

    fgets(buf,30,stdin);  //����һ���ַ���
    buf[strlen(buf) - 1] = 0;  //ȥ������
    swapString(buf,src);  //��buf����׺���ʽת��Ϊ��׺���ʽ
    printf("%s\n",src);
    int data = fun(src);
    printf("%d\n",data);

    return 0;
}
