#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
    自引用：当一个结构体中有一个或者是多个成员是指针，他们的基本类型就是结构体类型时，通常这种结构体称为“引用自身的结构体”

    1.结点：
        数据域：存放结点的数据信息
        指针域：存放一个地址，存放的地址是下一个结点的地址

    2.头指针  声明一个指针，指向第一个结点

    3.头结点  第一个结点

*/

typedef int* PINT;
#define PPINT int*
typedef void* (*PFUN)(void*,int*);
void* fun(void* a,int* b)
{

}

void*(*p1)(void*,int*) = fun;  //函数指针的声明
//返回值类型先写上然后立马写2个括号第一个括号放自己定义的指针变量，第二个括号写函数的形参类型
PFUN p = fun;

//带头结点的单向普通链表
//这个头结点不存放任何信息，作用只是起着一个带头作用

//创建链表，创建一个头结点
typedef struct node
{
    int data;
    char name[20];

    struct node* next;
}Node,*pNode;

//创建头结点
Node* CreateList()
{
    Node* pHead = (Node*)malloc(sizeof(Node));
    assert( pHead != NULL );

    pHead->data = -9999;  //没有意义的数
    strcpy(pHead->name,"");
    pHead->next = NULL;
    return pHead;
}

//插入结点  1.malloc创建一块内存 2.赋值 给这块空白的内存上写入数据  3.连接
//头插法
void InsertList(Node* pHead ,int data,const char* name)
{
    //1
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    //2
    pnew->data = data;
    strcpy(pnew->name,name);  //C语言的字符串拷贝

    //3头插法
    pnew->next = pHead->next;
    pHead->next = pnew;

}

//在第Pos位置之前插入一个元素
void InsertListByPos(Node* pHead,int data,const char* name,int Pos)
{

}

//在链表的尾部插入元素
void InsertListTail(Node* pHead,int data,const char* name)
{
    Node* p = pHead;
    while(p->next)
    {
        p = p->next;
    }
    Node* q = (Node*)malloc(sizeof(Node));
    q->data = data;
    strcpy(q->name,name);

    q->next = p->next;
    p->next = q;

}

//按照元素的data大小 从小到大插入
void InsertListSort(Node* pHead,int data,const char* name)
{
    Node* p = pHead->next;
    Node* q = pHead;
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL);

    pnew->data = data;
    strcpy(pnew->name,name);

    //连接
    while( p )
    {
        if(pnew->data > p->data)
        {
            p = p->next;
            q = q->next;
        }
        else
        {
            break;
        }

    }
    if(!p->next)
    {
        //最后查到p的后面
        pnew->next = p->next;
        p->next = pnew;
    }
    else
    {
        //在p的前面q的后面插入
        pnew->next = p;
        q->next = pnew;
    }
}

//删除节点
void DeleteNodeByData(Node* pHead,int data)
{
    Node* p = pHead->next;
    Node* q = pHead;
    while( p )
    {
        if( data == p->data )
        {
            break;
        }
        p = p->next;
        q = q->next;
    }

    if( p == NULL )
        return;


    q->next = p->next;
    free(p);
}

//删除data一致的所有元素
//free不改变指针内容
void DeleteAllNodeByData(Node* pHead,int data)
{
    Node* p = pHead->next;
    Node* q = pHead;
    while( p )
    {
        if(data == p->data)
        {
            q->next = p->next;
            free(p);
            p = q->next;
        }
        else
        {
            p = p->next;
            q = q->next;
        }
    }
}

//访问列表
void displayList(Node* pHead)
{
    Node* p = pHead;
    while(p->next)
    {
        p = p->next;
        printf("序号: %d,姓名: %s\n",p->data,p->name);
    }
    return ;
}



int main()
{
    Node* head = CreateList();
    InsertList(head,1,"panjunda1");
    InsertList(head,2,"panjunda2");
    InsertList(head,3,"panjunda3");
    InsertList(head,4,"panjunda4");
    InsertList(head,5,"panjunda5");
    InsertList(head,3,"panjunda33");
    InsertList(head,3,"panjunda333");
    InsertList(head,3,"panjunda3333");
    InsertListTail(head,6,"panjunda6");
    InsertListTail(head,7,"panjunda7");
    InsertListSort(head,4,"enzo");
    displayList(head);
    printf("\n");
    DeleteNodeByData(head,4);
    displayList(head);
    DeleteAllNodeByData(head,3);
    printf("\n");
    displayList(head);
    return 0;
}
