#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#define MAXSIZE 100

typedef struct queue
{
    int array[MAXSIZE];
    int front;  //ͷλ�õ��±�
    int rear;  //��β�±��β��λ��
}Queue;

/*
��ͷָ���1��front = (front+1)%MAXSIZE
��βָ���1��rear = (rear+1)%MAXSIZE
���г�ʼ�� front = rear = 0
�ӿ����� front == rear
�������� (rear + 1) % MAXSIZE == front  ��һ��λ�ó���


������
1.��ʼ������  ����һ���ն���
2.�пղ���
3.��Ӳ���
4.���Ӳ���
5.ȡ��ͷԪ�ز���
6.�������ÿղ���
7.�������ٲ���
*/

Queue* Queue_init()
{
    Queue* qhead = (Queue*)malloc(sizeof(Queue));
    assert(qhead != NULL);

    qhead->front = 0;
    qhead->rear = 0;

    return qhead;

}

int Queue_empty(Queue* qhead)
{
    if(qhead->front == qhead->rear)
    {
        return 1;  //�ǿ�
    }
    return 0;  //�ǿ�
}

int Queue_full(Queue* qhead)
{
    if( (qhead->rear + 1) % MAXSIZE == qhead->front )
    {
        return 1;  //����
    }
    return 0;  //����
}

//ȡ��ͷԪ��
int Queue_head_get(Queue* qhead)
{
    if( !Queue_empty(qhead) )
    {
        return qhead->array[qhead->front];
    }
    return -1;  //-1��ʾʧ��
}

void enQueue(Queue* qhead,int data)
{
    if( Queue_full(qhead) )
    {
        return ;//����״̬
    }
    qhead->array[qhead->rear] = data;
    qhead->rear = (qhead->rear + 1) % MAXSIZE;

}

//���Ӳ���
void dQueue(Queue* qhead)
{
    if( Queue_empty(qhead) )
    {
        //�ӿ�״̬
        return ;
    }
    qhead->front = (qhead->front +1 ) % MAXSIZE;
}

//��ն���
void Queue_clear(Queue* qhead)
{
    qhead->rear = qhead->front;
}

//���ٶ���
void Queue_destroy(Queue** qhead)
{
    Queue_clear(*qhead);
    free(*qhead);
    *qhead = NULL;
}

void DisplayQueue(Queue* qhead)
{
    int i;
    for(i = qhead->front ; i != qhead->rear; i = (i+1) % MAXSIZE )
    {
        printf("%d\n",qhead->array[i]);
    }
    printf("\n");
}

int main()
{
    Queue* qHead = Queue_init();
    enQueue(qHead,1);
    enQueue(qHead,2);
    enQueue(qHead,3);
    enQueue(qHead,4);
    enQueue(qHead,5);
    enQueue(qHead,6);

    DisplayQueue(qHead);

    dQueue(qHead);
    dQueue(qHead);
    DisplayQueue(qHead);

    Queue_clear(qHead);
    DisplayQueue(qHead);

    return 0;
}
