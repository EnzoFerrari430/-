#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct node
{
    int data;

    struct node* next;
}Node;

typedef struct queue
{
    struct node* front;
    struct node* rear;
}Queue;


Queue* Queue_init()
{
    Queue* qhead = (Queue*)malloc(sizeof(Queue));
    assert( qhead != NULL );

    qhead->front = NULL;
    qhead->rear = NULL;

    return qhead;
}

int Queue_empty(Queue* qhead)
{
    if( qhead->front == NULL )
    {
        return 1;
    }
    return 0;  //0��ʾ�ǿ�
}

//������Կ
void Resetmiyao(Queue* qhead)
{
    Queue_clear(qhead);
    enQueue(qhead,8);
    enQueue(qhead,2);
    enQueue(qhead,5);
    enQueue(qhead,4);
}


//��Ӳ���
void enQueue( Queue* qhead ,int data)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    pnew->data = data;
    pnew->next = NULL;

    if( Queue_empty(qhead) == 1 )
    {
        qhead->front = pnew;
        qhead->rear = pnew;
    }
    else
    {
        qhead->rear->next = pnew;
        qhead->rear = pnew;
    }
}

//���Ӳ���
int dQueue( Queue* qhead )
{
    if( Queue_empty(qhead) == 1 )
    {
        return -1;
    }

    Node* p = qhead->front;

    //ֻ��1��Ԫ��
    if( qhead->front == qhead->rear )
    {
        qhead->front = NULL;
        qhead->rear = NULL;
    }
    else
    {
        qhead->front = p->next;
    }
    free(p);
    return 0;  //0��ʾ���ӳɹ�
}


//ȡ��ͷԪ��
int Queue_head_get(Queue* qhead)
{
    if( Queue_empty(qhead) == 1 )
    {
        return -1;  //��ʾʧ��
    }
    return qhead->front->data;
}

//��ն���
void Queue_clear(Queue* qhead)
{
    while( Queue_empty(qhead) != 1 )
    {
        dQueue(qhead);
    }
}

void Queue_destroy(Queue** qhead)
{
    Queue_clear(*qhead);
    free(*qhead);

    *qhead = NULL;
}

void Queue_display( Queue* qhead )
{
    if( Queue_empty(qhead) == 1 )
    {
        return ;
    }

    Node* p = qhead->front;
    while( p != NULL )
    {
        printf("%d\n",p->data);
        p = p->next;
    }
}

int main()
{
    Queue* qHead = Queue_init();
    Resetmiyao(qHead);

    char Buf[30] = {0};
    gets(Buf);



    //Queue_display(qHead);

    return 0;
}
