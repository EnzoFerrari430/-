/*
    课后练习
    1.对一个乱序的已存在链表按照int值小序进行排序。

    2.对一个链表倒序。
*/

/*
    单向循环链表
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>

typedef struct node
{
    int data;

    struct node* next;
}Node;

Node* CreateList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    assert(head != NULL);

    head->data = -9999;  //数据域一个没有意义的数
    head->next = head;  //指针指向头结点


    return head;
}

//增加元素在尾部
void InsertListTail(Node* head,int data)
{
    Node* p = head;
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    pnew->data = data;


    //找到最后一个结点
    while( p->next!= head )
    {
        p = p->next;
    }
    pnew->next = p->next;
    p->next = pnew;

}

//打印链表
void DisplayList(Node* head)
{
    Node* p = head->next;

    while( p != head )
    {
        printf("p->data: %d\n",p->data);
        p = p->next;
    }
}

void DisplayListCycle(Node* head)
{
    Node *p = head;
    while( p!= NULL )
    {
        printf("p->data: %d\n",p->data);
        p = p->next;
        Sleep(1000);
    }
}

//删除结点
void DeleteList(Node* head,int data)
{
    Node* p = head->next;
    Node* q = head;
    while( p != head )
    {
        if( p->data == data )
        {
            q->next = p->next;
            free(p);
            return;
        }
        else
        {
            p = p->next;
            q = q->next;
        }

    }


}

//清空链表（保留头结点）
void ClearList(Node* head)
{
    Node* p = head->next;
    Node* q = head;
    while( p!= head )
    {
        q->next = p->next;
        free(p);
        p = q->next;
    }
}



//销毁链表（把头结点也销毁掉）
//修改形参的内容就要把形参的地址传进来，  形参是变量就传一级指针。形参是指针就传2级指针
void DestroyList(Node** head)
{
    ClearList(*head);
    free(*head);
    *head = NULL;  //想要修改head的内容就要传2级指针进来
}

int main()
{
    Node* pHead = CreateList();

    InsertListTail(pHead,1);
    InsertListTail(pHead,2);
    InsertListTail(pHead,3);
    InsertListTail(pHead,4);
    InsertListTail(pHead,5);

    DisplayList(pHead);
    printf("\n");
    DeleteList(pHead,2);

    DisplayList(pHead);
    printf("\n");

    ClearList(pHead);
    DisplayList(pHead);
    printf("\n");

    DestroyList(&pHead);
    //DisplayListCycle(pHead);

    return 0;
}
