/*
    1.增加联系人
    2.删除联系人
    3.根据名字查找号码
    4.打印联系人信息
    5.修改联系人
    6.退出，退出程序后，数据需要保存到文件
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <windows.h>

typedef struct node
{
    char name[20];  //姓名
    char mob[20];  //手机号码

    struct node* next;
}Node;

//创建通讯录链表
Node* CreateList()
{
    printf("begin CreateList\n");
    Node* head = (Node*)malloc(sizeof(Node));
    assert(head != NULL);

    strcpy(head->name,"");  //姓名为空
    strcpy(head->mob,"");
    head->next = NULL;  //头结点的next指针为空

    return head;
}

//插入数据元素,头插法
void InsertList(Node* head,char *name, char* num)
{
    Node* pnew = (Node*)malloc(sizeof(Node));
    assert( pnew != NULL );

    strcpy(pnew->name,name);
    strcpy(pnew->mob,num);

    //头插法
    pnew->next = head->next;
    head->next = pnew;

    printf("操作成功，正在返回主界面\n");
    Sleep(2000);
}

//删除联系人  通过联系人匹配
void DeleteNode(Node* head,char* name)
{
    Node* p = head->next;
    Node* q = head;
    int flag = 0;
    while( p )
    {
        if( strcmp(p->name,name) )  //相同返回true
        {
            q->next = p->next;
            free(p);
            flag = 1;
            break;
        }
    }
    if( flag )
    {
        printf("找到联系人,已删除\n");
    }
    else
    {
        printf("未找到该联系人\n");
    }
    Sleep(2000);
}

//查找联系人,按姓名查找
void FindNode(Node* head,char* name)
{
    Node* p = head->next;
    Node* q = head;

    int flag = 0;
    while(p)
    {
        if( strcmp(p->name,name) )
        {
            printf("找到该姓名为%s的联系方式: %s\n",name,p->mob);
            flag = 1;
            break;
        }
    }
    if( !flag )
    {
        printf("未找到该人的联系方式\n");
    }

    Sleep(2000);
}

//打印联系人
void DisplayList(Node* head)
{
    Node* p = head->next;
    while(p)
    {
        printf("姓名: %s, 号码: %s\n",p->name,p->mob);
        p = p->next;
    }

    Sleep(20000);  //等待20s
}

//修改联系人
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
        printf("未找到该联系人\n");
    }
    Sleep(2000);
}

void ReadtoFile(Node* head)
{
    Node* p = head->next;
    FILE *in = fopen("D:\\CC++\\数据结构代码\\链表\\TeleBook.txt","r");

    //操作，添加到链表中

    fclose(in);

}

void WritetoFile(Node* head)
{
    Node* p = head->next;
    FILE* out = fopen("D:\\CC++\\数据结构代码\\链表\\TeleBook.txt","w");
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
    printf("**********************欢迎来到通讯录*********************\n");
    printf("***************       1.增加联系人      *****************\n");
    printf("***************       2.删除联系人      *****************\n");
    printf("***************       3.查找联系人      *****************\n");
    printf("***************       4.打印联系人      *****************\n");
    printf("***************       5.修改联系人      *****************\n");
    printf("***************       6.退出            *****************\n");
    printf("*********************************************************\n");
    printf("*********************************************************\n\n");
    printf("请输入你要操作的指令: ");
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
            printf("增加联系人,请输入联系人姓名和号码中间用空格隔开: ");
            scanf("%s %s",name,num);
            InsertList(pHead,name,num);
            //n = Menu();
            break;
        case 2:
            system("cls");
            printf("删除联系人,请输入联系人姓名: ");
            scanf("%s",name);
            DeleteNode(pHead,name);
            //n = Menu();
            break;
        case 3:
            system("cls");
            printf("查找联系人,请输入联系人姓名: ");
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
            printf("请输入要修改的联系人的号码: ");
            scanf("%s %s",name,num);
            ModifyNode(pHead,name,num);
            //n = Menu();
            break;
        case 6:
            //在退出的时候将数据保存到文件中
            WritetoFile(pHead);
            printf("退出成功\n");
            exit(1);
            return 0;
        default:
            break;
        }
    }

    return 0;
}
