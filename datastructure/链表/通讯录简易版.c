/*
    1.������ϵ��
    2.ɾ����ϵ��
    3.�������ֲ��Һ���
    4.��ӡ��ϵ����Ϣ
    5.�޸���ϵ��
    6.�˳����˳������������Ҫ���浽�ļ�
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <windows.h>

typedef struct node
{
    char name[20];  //����
    char mob[20];  //�ֻ�����

    struct node* next;
}Node;

//����ͨѶ¼����
Node* CreateList()
{
    printf("begin CreateList\n");
    Node* head = (Node*)malloc(sizeof(Node));
    assert(head != NULL);

    strcpy(head->name,"");  //����Ϊ��
    strcpy(head->mob,"");
    head->next = NULL;  //ͷ����nextָ��Ϊ��

    return head;
}

//��������Ԫ��,ͷ�巨
void InsertList(Node* head,char *name, char* num)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    strcpy(pnew->name,name);
    strcpy(pnew->mob,num);

    //ͷ�巨
    pnew->next = head->next;
    head->next = pnew;

    printf("�����ɹ������ڷ���������\n");
    Sleep(2000);
}

//ɾ����ϵ��  ͨ����ϵ��ƥ��
void DeleteNode(Node* head,char* name)
{
    Node* p = head->next;
    Node* q = head;
    int flag = 0;
    while( p )
    {
        if( strcmp(p->name,name) )  //��ͬ����true
        {
            q->next = p->next;
            free(p);
            flag = 1;
            break;
        }
    }
    if( flag )
    {
        printf("�ҵ���ϵ��,��ɾ��\n");
    }
    else
    {
        printf("δ�ҵ�����ϵ��\n");
    }
    Sleep(2000);
}

//������ϵ��,����������
void FindNode(Node* head,char* name)
{
    Node* p = head->next;
    Node* q = head;

    int flag = 0;
    while(p)
    {
        if( strcmp(p->name,name) )
        {
            printf("�ҵ�������Ϊ%s����ϵ��ʽ: %s\n",name,p->mob);
            flag = 1;
            break;
        }
    }
    if( !flag )
    {
        printf("δ�ҵ����˵���ϵ��ʽ\n");
    }

    Sleep(2000);
}

//��ӡ��ϵ��
void DisplayList(Node* head)
{
    Node* p = head->next;
    while(p)
    {
        printf("����: %s, ����: %s\n",p->name,p->mob);
        p = p->next;
    }

    Sleep(20000);  //�ȴ�20s
}

//�޸���ϵ��
void ModifyNode(Node* head,char* name,char* num)
{
    Node* p = head->next;
    int flag = 0;
    while( p )
    {
        if( strcmp(p->name,name) )
        {
            strcpy(p->mob,num);
            flag = 1;
            break;
        }
    }
    if( !flag )
    {
        printf("δ�ҵ�����ϵ��\n");
    }
    Sleep(2000);
}

void ReadtoFile(Node* head)
{
    Node* p = head->next;
    FILE *in = fopen("D:\\CC++\\���ݽṹ����\\����\\TeleBook.txt","r");

    //��������ӵ�������

    fclose(in);

}

void WritetoFile(Node* head)
{
    Node* p = head->next;
    FILE* out = fopen("D:\\CC++\\���ݽṹ����\\����\\TeleBook.txt","w");
    while( p )
    {
        fprintf(out,"num:%d name:%s\n",p->name,p->mob);
        p = p->next;
    }
    fclose(out);
}


int Menu()
{
    //printf("begin Menu\n");
    system("cls");
    printf("*********************************************************\n");
    printf("*********************************************************\n");
    printf("**********************��ӭ����ͨѶ¼*********************\n");
    printf("***************       1.������ϵ��      *****************\n");
    printf("***************       2.ɾ����ϵ��      *****************\n");
    printf("***************       3.������ϵ��      *****************\n");
    printf("***************       4.��ӡ��ϵ��      *****************\n");
    printf("***************       5.�޸���ϵ��      *****************\n");
    printf("***************       6.�˳�            *****************\n");
    printf("*********************************************************\n");
    printf("*********************************************************\n\n");
    printf("��������Ҫ������ָ��: ");
    int num;
    scanf("%d",&num);
    return num;
}


int main()
{
    Node* pHead = CreateList();
    int n;
    char name[20],num[20];
    while( 1 )
    {
        n = Menu();
        switch(n)
        {
        case 1:
            system("cls");
            printf("������ϵ��,��������ϵ�������ͺ����м��ÿո����: ");
            scanf("%s %s",name,num);
            InsertList(pHead,name,num);
            //n = Menu();
            break;
        case 2:
            system("cls");
            printf("ɾ����ϵ��,��������ϵ������: ");
            scanf("%s",name);
            DeleteNode(pHead,name);
            //n = Menu();
            break;
        case 3:
            system("cls");
            printf("������ϵ��,��������ϵ������: ");
            scanf("%s",name);
            FindNode(pHead,name);
            //n = Menu();
            break;
        case 4:
            system("cls");
            DisplayList(pHead);
            //n = Menu();
            break;
        case 5:
            system("cls");
            printf("������Ҫ�޸ĵ���ϵ�˵ĺ���: ");
            scanf("%s %s",name,num);
            ModifyNode(pHead,name,num);
            //n = Menu();
            break;
        case 6:
            //���˳���ʱ�����ݱ��浽�ļ���
            WritetoFile(pHead);
            printf("�˳��ɹ�\n");
            exit(1);
            return 0;
        default:
            break;
        }
    }

    return 0;
}
