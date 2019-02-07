#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "tnode.h"

//����һ�����ļ���

QUEUE* queue_init();
int queue_empty(QUEUE* queue);
void enqueue(QUEUE* queue,TNODE* tp);
void dequeue(QUEUE* queue);
TNODE* queue_gethead(QUEUE* queue);

//static void queue_clear(QUEUE* queue);  //ǰ�����static�ؼ���֮�󣬸ú�����ֻ���ڱ��ļ���ʹ��,ͷ�ļ��Ͳ�����д��
void queue_clear(QUEUE* queue);
void queue_display(QUEUE* queue);
void queue_destroy(QUEUE** queue);

QUEUE* queue_init()
{
    QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
    assert(queue != NULL);

    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

int queue_empty(QUEUE* queue)
{
    if(queue->front == NULL)
    {
        return 1;
    }
    return 0;
}

void enqueue(QUEUE* queue,TNODE* tp)
{
    NODE* pnew = (NODE*)malloc(sizeof(NODE));
    assert(pnew != NULL );

    pnew->t = tp;
    pnew->next = NULL;

    if(queue_empty(queue) == 1)
    {
        queue->front = pnew;
        queue->rear = pnew;
    }
    else
    {
        queue->rear->next = pnew;
        queue->rear = pnew;
    }
    return ;
}

void dequeue(QUEUE* queue)
{
    //�ն���
    if(queue_empty(queue) == 1)
    {
        return ;
    }

    NODE* p = queue->front;
    queue->front = p->next;
    if(queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(p);
    return ;
}

TNODE* queue_gethead(QUEUE* queue)
{
    if(queue_empty(queue) == 1)
    {
        return NULL;
    }
    else
    {
        return queue->front->t;
    }
}

void queue_clear(QUEUE* queue)
{
    while(queue_empty(queue) != 1 )
    {
        dequeue(queue);
    }
    return ;
}

void queue_display(QUEUE* queue)
{
    NODE* p = queue->front;
    while(p!= NULL)
    {
        printf("%d\n",p->t->data);
        p = p->next;
    }
}

void queue_destroy(QUEUE** queue)
{
    queue_clear(*queue);
    free(*queue);

    *queue = NULL;
    return ;
}
