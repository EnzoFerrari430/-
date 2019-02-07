/*
    限定性线性表：限定性表示线性表的插入和删除有有限定性,比如只能插在队头或者队尾


    队列结构有2个指针，一个指向队头元素，一个指向队尾元素


    队列要实现7个基本操作：
        1.队列初始化，设置一个空队列
        2.判空操作
        3.入队操作
        4.出队操作
        5.取队头元素操作
        6.将队列置为空队列
        7.队列销毁操作
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

//判断队列为空
int Queue_empty( Queue* qhead )
{
    if(qhead->front == NULL)
    {
        return 1;
    }
    return 0;
}

//入队操作
void enQueue(Queue* qhead,int data)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL );

    pnew->data = data;
    pnew->next = NULL;  //入队操作一定放到队尾

    //判断队列是否是空
    if(Queue_empty(qhead) == 1)
    {
        qhead->front = pnew;  //队头指向这个元素
        qhead->rear = pnew;  //队尾指向这个元素

    }
    else
    {
        qhead->rear->next = pnew;
        qhead->rear = pnew;
    }
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

    QueueDisplay(qHead);

    return 0;
}
