/*
    �κ���ϰ
    1.��һ��������Ѵ���������intֵС���������

    2.��һ��������
*/

/*
    ����ѭ������
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

    head->data = -9999;  //������һ��û���������
    head->next = head;  //ָ��ָ��ͷ���


    return head;
}

//����Ԫ����β��
void InsertListTail(Node* head,int data)
{
    Node* p = head;
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    pnew->data = data;


    //�ҵ����һ�����
    while( p->next!= head )
    {
        p = p->next;
    }
    pnew->next = p->next;
    p->next = pnew;

}

//��ӡ����
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

//ɾ�����
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

//�����������ͷ��㣩
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



//����������ͷ���Ҳ���ٵ���
//�޸��βε����ݾ�Ҫ���βεĵ�ַ��������  �β��Ǳ����ʹ�һ��ָ�롣�β���ָ��ʹ�2��ָ��
void DestroyList(Node** head)
{
    ClearList(*head);
    free(*head);
    *head = NULL;  //��Ҫ�޸�head�����ݾ�Ҫ��2��ָ�����
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
