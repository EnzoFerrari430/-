#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#define MAXSIZE 100

typedef struct queue
{
    int array[MAXSIZE];
    int front;  //头位置的下标
    int rear;  //队尾下标的尾后位置
}Queue;

/*
队头指针进1：front = (front+1)%MAXSIZE
队尾指针进1：rear = (rear+1)%MAXSIZE
队列初始化 front = rear = 0
队空条件 front == rear
队满条件 (rear + 1) % MAXSIZE == front  空一个位置出来


操作：
1.初始化操作  设置一个空队列
2.判空操作
3.入队操作
4.出队操作
5.取队头元素操作
6.将队列置空操作
7.队列销毁操作
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
        return 1;  //是空
    }
    return 0;  //非空
}

int Queue_full(Queue* qhead)
{
    if( (qhead->rear + 1) % MAXSIZE == qhead->front )
    {
        return 1;  //是满
    }
    return 0;  //非满
}

//取队头元素
int Queue_head_get(Queue* qhead)
{
    if( !Queue_empty(qhead) )
    {
        return qhead->array[qhead->front];
    }
    return -1;  //-1表示失败
}

void enQueue(Queue* qhead,int data)
{
    if( Queue_full(qhead) )
    {
        return ;//队满状态
    }
    qhead->array[qhead->rear] = data;
    qhead->rear = (qhead->rear + 1) % MAXSIZE;

}

//出队操作
void dQueue(Queue* qhead)
{
    if( Queue_empty(qhead) )
    {
        //队空状态
        return ;
    }
    qhead->front = (qhead->front +1 ) % MAXSIZE;
}

//清空队列
void Queue_clear(Queue* qhead)
{
    qhead->rear = qhead->front;
}

//销毁队列
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
