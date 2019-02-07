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

typedef struct info
{
    char MobNum[20];  //20个字节

    struct info* next;  //指针占4个字节
}Info;

Info* CreateInfo()
{
    Info* Mhead = (Info*)malloc(sizeof(Info));
    assert(Mhead != NULL);
    strcpy(Mhead->MobNum,"");  //赋值为空
    Mhead->next = NULL;
    return Mhead;
}

typedef struct node
{
    char name[20];
    Info* MobNums;

    struct node* next;
}Node;

//创建通讯录链表
Node* CreateList()
{
    printf("begin CreateList\n");
    Node* head = (Node*)malloc(sizeof(Node));
    assert(head != NULL);

    strcpy(head->name,"");  //姓名为空
    //strcpy(head->MobNums->MobNum,"");  //号码为空
    //head->MobNums = CreateInfo();
//
    head->next = NULL;  //头结点的next指针为空
    //head->MobNums->next = NULL;  //头结点的info结构体的next指针为空

    return head;
}



//插入数据元素,头插法
void InsertList(Node* head,char *name, char* num)
{

}

int Menu()
{
    //printf("begin Menu\n");
    //system("cls");
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
            printf("增加联系人,请输入联系人姓名和号码中间用空格隔开: ");
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
