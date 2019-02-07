#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node
{
    char name[20];
    char no[20];

    struct node* next;
}Node;

Node* CreateList()
{
    Node* head = (Node*)malloc(sizeof(Node));

    head->next = NULL;

    return head;
}

void InsertList(Node* head,char* name,char* no)
{
    Node* pnew = (Node*)malloc(sizeof(Node));

    strcpy(pnew->name,name);
    strcpy(pnew->no,no);

    pnew->next = head->next;
    head->next = pnew;
}

void SavetoFile(Node* head)
{
    FILE* fp = fopen("List.txt","w");  //相对路径，覆盖方式写入
    Node* p = head->next;

    while( p != NULL )
    {
        fwrite(p,sizeof(Node),1,fp);  //存入p为起始地址 大小为Node的1块内容到fp中
        p = p->next;
    }

    fclose(fp);
}

void SavetoFile2(Node* head)
{
    FILE* fp = fopen("List.txt","w");
    Node* p = head->next;
    while( p )
    {
        fprintf(fp,"%s  %s\n",p->name,p->no);
        p = p->next;
    }

    fclose(fp);


}

void LoadfromFile(Node* head)
{
    FILE* fp = fopen("List.txt","r");
    if( fp == NULL )
    {
        return;
    }
    Node temp;
    while(fread(&temp,sizeof(Node),1,fp))
    {
        InsertList(head,temp.name,temp.no);
    }
    fclose(fp);
}

void LoadfromFile2(Node* head)
{
    FILE* fp = fopen("List.txt","r");
    if( fp == NULL )
    {
        return ;
    }

    char buf[40] = {0};
    char name[20] = {0};
    char no[20] = {0};

    while(fgets(buf,40,fp) != NULL)
    {
        sscanf(buf,"%s%s",name,no);
        InsertList(head,name,no);
        memset(buf,0x00,sizeof(buf));
        memset(name,0x00,sizeof(name));
        memset(no,0x00,sizeof(no));
    }
    fclose(fp);
}

void DisplayList(Node* head)
{
    Node* p = head->next;
    while(p)
    {
        printf("%s  %s\n",p->name,p->no);
        p = p->next;
    }
}

int main()
{
    Node* pHead = CreateList();

    LoadfromFile2(pHead);

    DisplayList(pHead);
//    InsertList(pHead,"p1","11111111111");
//    InsertList(pHead,"p2","22222222222");
//    InsertList(pHead,"p3","33333333333");
//    InsertList(pHead,"p4","44444444444");
    SavetoFile2(pHead);



    return 0;
}
