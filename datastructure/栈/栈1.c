#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <windows.h>

/*
    栈的定义：
        一个可以实现“先进后出”的存储结构

        这里实现一个底部自带一个头结点的栈结构

    栈的分类：
            静态栈：
                数组的形式

            动态栈：
                链表的形式

    栈的操作：
        初始化栈
        进栈操作
        出栈操作
        判断栈是否为空  //Stack->top == Stack.bottom;
        清空栈
        销毁栈
*/




typedef struct node
{
    int data;

    struct node* next;
} Node;

typedef struct stack
{
    struct node* top;
    struct node* bottom;
} Stack;

//初始化栈
void Stack_init(Stack* pstack)
{
    //先构造一个底部的结点
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    pnew->next = NULL;
    pstack->top = pstack->bottom = pnew;

}

void Stack_push(Stack* pstack,int data)
{
    //创建结点
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    //赋值
    pnew->data = data;


    //连接
    pnew->next = pstack->top;
    pstack->top = pnew;


}


void Stack_display(Stack* pstack)
{
    Node* p = pstack->top;
    while( p != pstack->bottom )
    {
        printf("%d\n",p->data);
        p = p->next;
    }
    printf("\n");
}

//出栈操作,并保存出栈元素
int Stack_pop(Stack* pstack,int* val)
{


    if( !Stack_empty(pstack) )
    {
        return -1;
    }
    Node* p = pstack->top;
    *val = p->data;

    pstack->top = pstack->top->next;
    free(p);
    return 0;

}

int Stack_empty(Stack* pstack)
{
    if( pstack->top == pstack->bottom )
    {
        return 0;  //0表示栈为空
    }
    return 1;  //1表示非空


}

//清空栈
void Stack_clear(Stack* pstack)
{
    Node* p;
    while( pstack->top != pstack->bottom )
    {
        p = pstack->top;
        pstack->top = pstack->top->next;
        free(p);
    }
}

//销毁栈
void Stack_destroy(Stack* pstack)
{

}

int main()
{
    Stack S;
    int val;
    Stack_init(&S);
    Stack_push(&S,1);
    Stack_push(&S,2);
    Stack_display(&S);

    if( Stack_pop(&S,&val) != -1 )
    {
        Stack_display(&S);
        printf("出栈元素为: %d\n",val);
    }
    else
    {
        printf("栈已经为空\n");
    }

    if( Stack_pop(&S,&val) != -1 )
    {
        Stack_display(&S);
        printf("出栈元素为: %d\n",val);
    }
    else
    {
        printf("栈已经为空\n");
    }

    if( Stack_pop(&S,&val) != -1 )
    {
        Stack_display(&S);
        printf("出栈元素为: %d\n",val);
    }
    else
    {
        printf("栈已经为空\n");
    }

    Stack_push(&S,1);
    Stack_push(&S,2);
    Stack_push(&S,3);
    Stack_push(&S,4);
    Stack_push(&S,5);

    Stack_display(&S);

    Stack_clear(&S);

    Stack_display(&S);



    return 0;
}
