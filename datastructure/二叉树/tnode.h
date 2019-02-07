#ifndef TNODE_H_INCLUDED
#define TNODE_H_INCLUDED

//结构体定义一般放在头文件中

typedef struct tnode
{
    int data;
    struct tnode* leftchild;
    struct tnode* rightchild;
}TNODE;

typedef struct node
{
    TNODE* t;  //数据域

    struct node* next;
}NODE;

typedef struct queue
{
    NODE* front;
    NODE* rear;
}QUEUE;

extern QUEUE* queue_init();
extern int queue_empty(QUEUE* queue);
extern void enqueue(QUEUE* queue,TNODE* tp);
extern void dequeue(QUEUE* queue);
extern TNODE* queue_gethead(QUEUE* queue);
extern void queue_clear(QUEUE* queue);
extern void queue_display(QUEUE* queue);
extern void queue_destroy(QUEUE** queue);




#endif // TNODE_H_INCLUDED
