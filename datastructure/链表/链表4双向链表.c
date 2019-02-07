#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct node
{
    int data;

    struct node* prior;  //ǰһ������ַ
    struct node* next;   //��һ������ַ
} Node;

//�����ô�ͷ����˫��ѭ������
Node* CreateList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    assert(head != NULL);

    head->data = -9999;

    head->next = head;
    head->prior = head;

    return head;
}

//ͷ�巨
void InsertList(Node* head,int data)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL);

    pnew->data = data;

    //�鵽ͷ��
    //�Ȱ�pnewָ�����úã��ٸı�ԭ�������ָ��
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
    //��ѭ����ʱ��  pָ��head  qָ�����һ��Ԫ��

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

//�������
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

    //���Ժ�Ϊһ��
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

//ɾ��һ�����
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
            break;  //ֻɾ��һ��
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
    *head = NULL;  //����2��ָ�룬�޸��β�һ��ָ����������
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
    printf("\n���������������\n");
    ClearList(pHead);
    DisplayList(pHead);

    return 0;
}
