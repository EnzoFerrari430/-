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

typedef struct info
{
    char MobNum[20];  //20���ֽ�

    struct info* next;  //ָ��ռ4���ֽ�
}Info;

Info* CreateInfo()
{
    Info* Mhead = (Info*)malloc(sizeof(Info));
    assert(Mhead != NULL);
    strcpy(Mhead->MobNum,"");  //��ֵΪ��
    Mhead->next = NULL;
    return Mhead;
}

typedef struct node
{
    char name[20];
    Info* MobNums;

    struct node* next;
}Node;

//����ͨѶ¼����
Node* CreateList()
{
    printf("begin CreateList\n");
    Node* head = (Node*)malloc(sizeof(Node));
    assert(head != NULL);

    strcpy(head->name,"");  //����Ϊ��
    //strcpy(head->MobNums->MobNum,"");  //����Ϊ��
    //head->MobNums = CreateInfo();
//
    head->next = NULL;  //ͷ����nextָ��Ϊ��
    //head->MobNums->next = NULL;  //ͷ����info�ṹ���nextָ��Ϊ��

    return head;
}



//��������Ԫ��,ͷ�巨
void InsertList(Node* head,char *name, char* num)
{

}

int Menu()
{
    //printf("begin Menu\n");
    //system("cls");
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
    printf("*********************************************************\n");

    int num;
    scanf("%d",&num);
    return num;
}


int main()
{
    printf("begin\n");
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
            n = Menu();
            break;
        case 2:
            n = Menu();
            break;
        case 3:
            n = Menu();
            break;
        case 4:
            n = Menu();
            break;
        case 5:
            n = Menu();
            break;
        case 6:
            return 0;
        default:
            break;
        }
    }

    return 0;
}
