#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


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
void DisplayList(Node* pHead)
{
    Node* p = pHead;
    while(p->next)
    {
        p = p->next;
        printf("���: %d,����: %s\n",p->data,p->name);
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
                flag = 1;  //ȷ�Ϸ����˽���
                //����p r 2��ָ���ָ��
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

//����
void ReverseList(Node* head)
{
    Node* p = head->next;
    Node* q = head;
    Node* r = p->next;
    if( p == NULL || r == NULL )
    {
        return ;
    }

    p->next = NULL;  //�ѵ�һ�����nextָ��NULL
    while( r )
    {
        q = p;  //������һλ
        p = r;
        r = r->next;

        p->next = q;  //����һ��Ԫ��nextָ��ָ��ǰһ��Ԫ��
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
