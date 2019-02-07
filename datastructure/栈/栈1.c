#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <windows.h>

/*
    ջ�Ķ��壺
        һ������ʵ�֡��Ƚ�������Ĵ洢�ṹ

        ����ʵ��һ���ײ��Դ�һ��ͷ����ջ�ṹ

    ջ�ķ��ࣺ
            ��̬ջ��
                �������ʽ

            ��̬ջ��
                �������ʽ

    ջ�Ĳ�����
        ��ʼ��ջ
        ��ջ����
        ��ջ����
        �ж�ջ�Ƿ�Ϊ��  //Stack->top == Stack.bottom;
        ���ջ
        ����ջ
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

//��ʼ��ջ
void Stack_init(Stack* pstack)
{
    //�ȹ���һ���ײ��Ľ��
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    pnew->next = NULL;
    pstack->top = pstack->bottom = pnew;

}

void Stack_push(Stack* pstack,int data)
{
    //�������
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    //��ֵ
    pnew->data = data;


    //����
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

//��ջ����,�������ջԪ��
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
        return 0;  //0��ʾջΪ��
    }
    return 1;  //1��ʾ�ǿ�


}

//���ջ
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

//����ջ
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
        printf("��ջԪ��Ϊ: %d\n",val);
    }
    else
    {
        printf("ջ�Ѿ�Ϊ��\n");
    }

    if( Stack_pop(&S,&val) != -1 )
    {
        Stack_display(&S);
        printf("��ջԪ��Ϊ: %d\n",val);
    }
    else
    {
        printf("ջ�Ѿ�Ϊ��\n");
    }

    if( Stack_pop(&S,&val) != -1 )
    {
        Stack_display(&S);
        printf("��ջԪ��Ϊ: %d\n",val);
    }
    else
    {
        printf("ջ�Ѿ�Ϊ��\n");
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
