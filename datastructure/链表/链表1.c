#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
    �����ã���һ���ṹ������һ�������Ƕ����Ա��ָ�룬���ǵĻ������;��ǽṹ������ʱ��ͨ�����ֽṹ���Ϊ����������Ľṹ�塱

    1.��㣺
        �����򣺴�Ž���������Ϣ
        ָ���򣺴��һ����ַ����ŵĵ�ַ����һ�����ĵ�ַ

    2.ͷָ��  ����һ��ָ�룬ָ���һ�����

    3.ͷ���  ��һ�����

*/

typedef int* PINT;
#define PPINT int*
typedef void* (*PFUN)(void*,int*);
void* fun(void* a,int* b)
{

}

void*(*p1)(void*,int*) = fun;  //����ָ�������
//����ֵ������д��Ȼ������д2�����ŵ�һ�����ŷ��Լ������ָ��������ڶ�������д�������β�����
PFUN p = fun;

//��ͷ���ĵ�����ͨ����
//���ͷ��㲻����κ���Ϣ������ֻ������һ����ͷ����

//������������һ��ͷ���
typedef struct node
{
    int data;
    char name[20];

    struct node* next;
}Node,*pNode;

//����ͷ���
Node* CreateList()
{
    Node* pHead = (Node*)malloc(sizeof(Node));
    assert( pHead != NULL );

    pHead->data = -9999;  //û���������
    strcpy(pHead->name,"");
    pHead->next = NULL;
    return pHead;
}

//������  1.malloc����һ���ڴ� 2.��ֵ �����հ׵��ڴ���д������  3.����
//ͷ�巨
void InsertList(Node* pHead ,int data,const char* name)
{
    //1
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    //2
    pnew->data = data;
    strcpy(pnew->name,name);  //C���Ե��ַ�������

    //3ͷ�巨
    pnew->next = pHead->next;
    pHead->next = pnew;

}

//�ڵ�Posλ��֮ǰ����һ��Ԫ��
void InsertListByPos(Node* pHead,int data,const char* name,int Pos)
{

}

//�������β������Ԫ��
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

//����Ԫ�ص�data��С ��С�������
void InsertListSort(Node* pHead,int data,const char* name)
{
    Node* p = pHead->next;
    Node* q = pHead;
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert(pnew != NULL);

    pnew->data = data;
    strcpy(pnew->name,name);

    //����
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
        //���鵽p�ĺ���
        pnew->next = p->next;
        p->next = pnew;
    }
    else
    {
        //��p��ǰ��q�ĺ������
        pnew->next = p;
        q->next = pnew;
    }
}

//ɾ���ڵ�
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

//ɾ��dataһ�µ�����Ԫ��
//free���ı�ָ������
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

//�����б�
void displayList(Node* pHead)
{
    Node* p = pHead;
    while(p->next)
    {
        p = p->next;
        printf("���: %d,����: %s\n",p->data,p->name);
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
