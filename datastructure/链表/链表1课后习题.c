#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


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
void DisplayList(Node* pHead)
{
    Node* p = pHead;
    while(p->next)
    {
        p = p->next;
        printf("序号: %d,姓名: %s\n",p->data,p->name);
    }
    return ;
}

void SortList(Node* head)
{
    Node* p;
    Node* q;
    Node* r;
    int flag = 1;
    while( flag )
    {
        flag = 0;
        p = head->next;
        q = head;
        r = p->next;
        while( r )
        {
            if( p->data > r->data )
            {
                flag = 1;  //确认发生了交换
                //交换p r 2个指针的指向
                q->next = r;
                p->next = r->next;
                r->next = p;
                break;
            }
            else
            {
                p = p->next;
                r = r->next;
                q = q->next;
            }
        }
    }
}

//逆序
void ReverseList(Node* head)
{
    Node* p = head->next;
    Node* q = head;
    Node* r = p->next;
    if( p == NULL || r == NULL )
    {
        return ;
    }

    p->next = NULL;  //把第一个结点next指向NULL
    while( r )
    {
        q = p;  //往后移一位
        p = r;
        r = r->next;

        p->next = q;  //将后一个元素next指针指向前一个元素
    }

    head->next = p;
}



int main()
{
    Node* pHead = CreateList();
    InsertList(pHead,7,"gggg");
    InsertList(pHead,8,"hhhh");
    InsertList(pHead,2,"bbbb");
    InsertList(pHead,9,"iiii");
    InsertList(pHead,4,"dddd");
    DisplayList(pHead);
    printf("\n");
    SortList(pHead);
    DisplayList(pHead);
    printf("\n");

    ReverseList(pHead);
    DisplayList(pHead);
    printf("\n");

    return 0;
}
