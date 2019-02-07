/*
    �޶������Ա��޶��Ա�ʾ���Ա�Ĳ����ɾ�������޶���,����ֻ�ܲ��ڶ�ͷ���߶�β


    ���нṹ��2��ָ�룬һ��ָ���ͷԪ�أ�һ��ָ���βԪ��


    ����Ҫʵ��7������������
        1.���г�ʼ��������һ���ն���
        2.�пղ���
        3.��Ӳ���
        4.���Ӳ���
        5.ȡ��ͷԪ�ز���
        6.��������Ϊ�ն���
        7.�������ٲ���
*/
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

//�ж϶���Ϊ��
int Queue_empty( Queue* qhead )
{
    if(qhead->front == NULL)
    {
        return 1;
    }
    return 0;
}

//��Ӳ���
void enQueue(Queue* qhead,int data)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL );

    pnew->data = data;
    pnew->next = NULL;  //��Ӳ���һ���ŵ���β

    //�ж϶����Ƿ��ǿ�
    if(Queue_empty( qhead ) == 1)
    {
        qhead->front = pnew;  //��ͷָ�����Ԫ��
        qhead->rear = pnew;  //��βָ�����Ԫ��

    }
    else
    {
        qhead->rear->next = pnew;
        qhead->rear = pnew;
    }
}

//���Ӳ���
int dQueue(Queue* qhead)
{
    //�ж϶����Ƿ��ǿ�
    if( Queue_empty( qhead ) == 1 )
    {
        return 1;
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

//��ö�ͷԪ��
int Queue_head_get(Queue* qhead)
{
    //�ж϶����Ƿ�Ϊ��
    if( Queue_empty(qhead) == 1 )
    {
        return -1;  //��ʾʧ��
    }
    return qhead->front->data;  //���ض�ͷԪ�ص�dataֵ
}

void Queue_clear( Queue* qhead )
{
    while( Queue_empty(qhead) != 1 )
    {
        dQueue(qhead);  //������в�Ϊ�վͳ���
    }
}

void Queue_destroy( Queue** qhead )
{
    Queue_clear(*qhead);
    free(*qhead);
    *qhead = NULL;
}

void QueueDisplay(Queue* qhead)
{
    Node* p = qhead->front;
    while(p)
    {
        printf("%d\n",p->data);
        p = p->next;
    }


}

int main()
{
    Queue* qHead = Queue_init();
    enQueue(qHead,1);
    enQueue(qHead,2);
    enQueue(qHead,3);
    enQueue(qHead,4);
    enQueue(qHead,5);

    dQueue(qHead);
    QueueDisplay(qHead);
    Queue_destroy(&qHead);

    if( qHead == NULL )
    {
        printf("NULL\n");
    }

    return 0;
}
