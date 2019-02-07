#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct node
{
    int data;

    struct node* prior;  //前一个结点地址
    struct node* next;   //下一个结点地址
} Node;

//这里用带头结点的双向循环链表
Node* CreateList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    assert(head != NULL);

    head->data = -9999;

    head->next = head;
    head->prior = head;

    return head;
}

//头插法
void InsertList(Node* head,int data)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL);

    pnew->data = data;

    //查到头部
    //先把pnew指向设置好，再改变原来链表的指向
    pnew->next = head->next;
    pnew->prior = head;

    head->next->prior = pnew;
    head->next = pnew;

}

void InsertListTail(Node* head,int data)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL);

    pnew->data = data;
    Node* p = head->next;
    Node* q = head;
    while( p != head )
    {
        p = p->next;
        q = q->next;
    }
    //出循环的时候  p指向head  q指向最后一个元素

    pnew->next = p;
    pnew->prior = q;

    p->prior = pnew;
    q->next = pnew;

}

void InsertListTail2(Node* head,int data)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL);

    pnew->data = data;


    pnew->next = head;
    pnew->prior = head->prior;

    head->prior->next = pnew;
    head->prior = pnew;
}

//有序插入
void InsertListBySort(Node* head,int data)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL);

    pnew->data = data;

    Node* p = head->next;
    while( p!= head )
    {
        if(p->data > pnew->data)
        {
            break;
        }

        p = p->next;
    }

    //可以合为一种
//    if( p == head )
//    {
//        pnew->next = p;
//        pnew->prior = p->prior;
//
//        p->prior->next = pnew;
//        p->prior = pnew;
//    }
//    else
//    {
//        pnew->next = p;
//        pnew->prior = p->prior;
//
//        p->prior->next = pnew;
//        p->prior = pnew;
//    }

    pnew->next = p;
    pnew->prior = p->prior;

    p->prior->next = pnew;
    p->prior = pnew;
}

//删除一个结点
void DeleteNode(Node* head,int data)
{
    Node* p = head->next;
    while( p != head )
    {
        if( data == p->data )
        {
            p->prior->next = p->next;
            p->next->prior = p->prior;
            free(p);
            break;  //只删除一个
        }
        p = p->next;
    }


}



void DisplayList(Node* head)
{
    Node* p = head->next;
    while(p != head)
    {
        printf("%d\n",p->data);
        p = p->next;
    }
}

void ReverseDisplayList(Node* head)
{
    Node* p = head->prior;
    while( p != head )
    {
        printf("%d\n",p->data);
        p = p->prior;
    }
}

void ClearList(Node* head)
{
    Node* p = head->next;
    while( p != head )
    {
        head->next = p->next;
        free(p);
        p = head->next;
    }
}

void Destroy(Node** head)
{
    ClearList(*head);
    free(*head);
    *head = NULL;  //传入2级指针，修改形参一级指针内容内容
}

int main()
{
    Node* pHead = CreateList();


//    InsertList(pHead,1);
//    InsertList(pHead,2);
//    InsertList(pHead,3);
//    InsertList(pHead,4);
//    InsertList(pHead,5);
//    InsertList(pHead,6);
//    ReverseDisplayList(pHead);


//    InsertListTail2(pHead,1);
//    InsertListTail2(pHead,2);
//    InsertListTail2(pHead,3);
//    InsertListTail2(pHead,4);
//    InsertListTail2(pHead,5);
//    DisplayList(pHead);

    InsertListBySort(pHead,7);
    InsertListBySort(pHead,8);
    InsertListBySort(pHead,2);
    InsertListBySort(pHead,9);
    InsertListBySort(pHead,4);
    DisplayList(pHead);
    DeleteNode(pHead,4);
    DisplayList(pHead);
    printf("\n接下来是清空链表\n");
    ClearList(pHead);
    DisplayList(pHead);

    return 0;
}
