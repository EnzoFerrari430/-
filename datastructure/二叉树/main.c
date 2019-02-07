/*
    Ҷ��㣺
        �˽������û�н���ˡ�
    ��֧��㣺
        �˽�����滹�к��ӡ���������
    ��Ů��
        �����Ÿý��ĺ���
    ���Ķȣ�
        �ý�����Ů��
    ˫�ף�
        �ý�����һ�����
    �ֵܣ�
        ��Щ���ӵ����ͬ��˫��
    ���ȣ�
        �иý��������Դ��˳���ҵ��Ľ��
    ���
        �ý���µ����н��
    ����Σ�
        �������Ϊ1��������+1
    ������ȣ�
        �����Ĳ����
    ���Ķȣ�
        ���Ķ�����ֵΪ���Ķ�


�������Ķ��壺
    һ���������ǽ���һ�����޼��ϣ��ü��ϻ���Ϊ�գ���������һ�������������÷ֱ��Ϊ���������������ġ������ཻ�Ķ��������

���������ص㣺
    ÿ���������ֻ�������������������в����ڶȴ���2�Ľ�㣩

��������5����̬��
    1������
        û�и����
    2��ֻ��һ�������
    3��ֻ��������
    4��ֻ��������
    5��������������

�����������ʣ�
    1����i�����ֻ��2^(i-1)�����
    2�����Ϊk�Ķ���������� 2^k - 1 (k>=1)
    3����������һ�ö����������Ҷ�����Ϊn1,��Ϊ2�Ľ����Ϊn2,��n1 = n2 + 1
    4������n��������ȫ������()�����Ϊ��log2(n+1)

��������չ��
    ����������������������������Ҷ�ӽ��֮���ÿһ����㶼���������ӣ�ÿһ��(��Ȼ�������һ��)������ȫ��䡣
    ��ȫ���������������һ��֮�������ÿһ�㶼����ȫ��䣬�������н�㶼����������롣
    ����������������Ҷ�ӽ��֮���ÿһ����㶼���������ӽ�㡣


�������ı�����
    ���ʸ������� V
    ������������������ L
    ������������������ R

    �����Ĵ�����
        ǰ����� VLR
        ������� LVR
        ������� LRV


������������
    ���壺���������������ǿ�������������һ�����ʵĶ�������
                                                    1.�������������ǿգ����������ϵ����н���ֵ��С�ڸ�����ֵ��
                                                    2.�������������ǿգ����������ϵ����н���ֵ�����ڸ�����ֵ��
                                                    3.�������������ָ�ʽһ�ö���������
                                        �� < �� < �ң�BST���ʣ�


����������ʽ�洢��











*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tnode.h"  //�����Ϳ�����ͷ�ļ��еĽṹ��ͺ���


//��α���
void displayC(TNODE* root)
{
    if( root == NULL )
    {
        return ;
    }

    QUEUE* queue = queue_init();
    enqueue(queue,root);

    TNODE* temp;

    while( queue_empty(queue) != 1)
    {
        temp = queue_gethead(queue);
        printf("%d\n",temp->data);

        if(temp->leftchild != NULL)
        {
            enqueue(queue,temp->leftchild);
        }

        if(temp->rightchild != NULL)
        {
            enqueue(queue,temp->rightchild);
        }
        dequeue(queue);
    }

    queue_destroy(&queue);

}

//���������ӡ����������
void displayLVR(TNODE* root)
{
    if( root->leftchild )
    {
        displayLVR( root->leftchild );
    }

    if( root )
    {
        printf("%d\n",root->data);
    }

    if( root->rightchild )
    {
        displayLVR( root->rightchild );
    }

}


TNODE* insertTree(TNODE* root ,int data)
{
    if( root == NULL )
    {
        TNODE* pnew = (TNODE*)malloc(sizeof(TNODE));
        assert(pnew != NULL);

        pnew->data = data;
        pnew->leftchild = NULL;
        pnew->rightchild = NULL;

        return pnew;
    }

    if( root->data > data )
    {
        root->leftchild =  insertTree(root->leftchild,data);
        return root;
    }
    else
    {
        root->rightchild = insertTree(root->rightchild,data);
        return root;
    }
}

int TreeDeep(TNODE* root)
{
    if( root == NULL )
    {
        return 0;
    }
    int l = TreeDeep(root->leftchild);
    int r = TreeDeep(root->rightchild);
    return (l>r?l:r) + 1;
}

//����һ����
void destroyTree(TNODE** root)
{
    if( *root == NULL )
    {
        return ;
    }
    destroyTree( (*root)->leftchild);
    destroyTree( (*root)->rightchild );
    printf("free:%d\n",(*root)->data);
    free(*root);
    *root = NULL;
    return ;
}

TNODE* GetLeftTreeMax(TNODE* root)
{
    TNODE* p1 = root->leftchild;
    TNODE* p2 = root;
    if( p1->leftchild == NULL )
    {
        p2->leftchild = p1->leftchild;
        return p1;
    }
    while( p1.rightchild != NULL )
    {
        p2 = p1;
        p1 = p1->rightchild;
    }
    p2->rightchild = p1->leftchild;
    return p1;
}

TNODE* deleteTree(TNODE* root,int data)
{
    if(root == NULL)
    {
        return root;
    }
    if( root->data == data )
    {
        if( root->leftchild == NULL && root->rightchild == NULL)
        {
            //����Ҷ���
            free(root);
            root = NULL;
            return root;
        }
        else if( root->leftchild != NULL && root->rightchild == NULL )
        {
            TNODE* p = root->leftchild;
            free( root );
            root = NULL;
            return p;  //��root�����ӵ��������

        }
        else if( root->leftchild == NULL && root->rightchild != NULL )
        {
            TNODE* p = root->rightchild;
            free(root);
            root = NULL;
            return p;  //��root���Һ��ӵ��������
        }
        else
        {
            TNODE* p = GetLeftTreeMax(root);
            p->leftchild = root->leftchild;
            p->rightchild = root->rightchild;
            free(root);
            root = NULL;
            return p;
        }
    }
    else
    {
        if(root->data > data)
        {
            root->leftchild = deleteTree(root->leftchild,data);
        }
        else
        {
            root->rightchild = deleteTree(root->rightchild,data);
        }
        return root;
    }
    return NULL;
}


int main()
{
    TNODE a,b,c,d,e,f;
    a.data = 1;
    a.leftchild = &b;
    a.rightchild = &c;

    b.data = 2;
    b.leftchild = &d;
    b.rightchild = NULL;

    c.data = 3;
    c.leftchild = NULL;
    c.rightchild = &f;

    d.data = 4;
    d.leftchild = NULL;
    d.rightchild = &e;

    e.data = 5;
    e.leftchild = NULL;
    e.rightchild = NULL;

    f.data = 6;
    f.leftchild = NULL;
    f.rightchild = NULL;

    displayC(&a);

    printf("\n");

    TNODE* root = NULL;
    root = insertTree(root,10);
    insertTree(root,15);
    insertTree(root,17);
    insertTree(root,5);
    insertTree(root,7);
    insertTree(root,4);
    insertTree(root,13);
    insertTree(root,11);
    insertTree(root,6);
    insertTree(root,3);

    displayLVR(root);
    printf("\n");
    displayC(root);

    printf("deep: %d\n",TreeDeep(root));
    destroyTree(root);
    return 0;
}
