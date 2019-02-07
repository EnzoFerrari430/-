/*
    叶结点：
        此结点下面没有结点了。
    分支结点：
        此结点下面还有孩子。根结点除外
    子女：
        紧接着该结点的孩子
    结点的度：
        该结点的子女数
    双亲：
        该结点的上一个结点
    兄弟：
        这些结点拥有相同的双亲
    祖先：
        有该结点往上溯源，顺序找到的结点
    子孙：
        该结点下的所有结点
    结点层次；
        根结点层次为1，往下逐级+1
    树的深度：
        该树的层次数
    树的度：
        结点的度最大的值为树的度


二叉树的定义：
    一个二叉树是结点的一个有限集合，该集合或者为空，或者是由一个根结点加上两棵分别称为左子树和右子树的、互不相交的二叉树组成

二叉树的特点：
    每个结点至多只有两棵子树（二叉树中不存在度大于2的结点）

二叉树有5中形态：
    1：空树
        没有根结点
    2：只有一个根结点
    3：只有左子树
    4：只有右子树
    5：左右子树都有

二叉树的性质：
    1：第i层最多只有2^(i-1)个结点
    2：深度为k的二叉树最多有 2^k - 1 (k>=1)
    3：对于任意一棵二叉树，如果叶结点数为n1,度为2的结点数为n2,则n1 = n2 + 1
    4：具有n个结点的完全二叉树()的深度为：log2(n+1)

二叉树拓展：
    完美二叉树（满二叉树）：除了叶子结点之外的每一个结点都有两个孩子，每一层(当然包含最后一层)都被完全填充。
    完全二叉树：除了最后一层之外的其他每一层都被完全填充，并且所有结点都保持向左对齐。
    完满二叉树：除了叶子结点之外的每一个结点都有两个孩子结点。


二叉树的遍历：
    访问根结点记作 V
    遍历根的左子树记作 L
    遍历根的右子树记作 R

    遍历的次序有
        前序遍历 VLR
        中序遍历 LVR
        后序遍历 LRV


二叉排序树：
    定义：二叉排序树或者是空树，或者满足一下性质的二叉树：
                                                    1.若它的左子树非空，则左子树上的所有结点的值均小于根结点的值。
                                                    2.若它的右子树非空，则右子树上的所有结点的值均大于根结点的值。
                                                    3.左右子树本身又各式一棵二叉排序树
                                        左 < 根 < 右（BST性质）


二叉树的链式存储：











*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tnode.h"  //这样就可以用头文件中的结构体和函数


//层次遍历
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

//中序遍历打印二叉排序树
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

//销毁一棵树
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
            //这是叶结点
            free(root);
            root = NULL;
            return root;
        }
        else if( root->leftchild != NULL && root->rightchild == NULL )
        {
            TNODE* p = root->leftchild;
            free( root );
            root = NULL;
            return p;  //把root的左孩子当做根结点

        }
        else if( root->leftchild == NULL && root->rightchild != NULL )
        {
            TNODE* p = root->rightchild;
            free(root);
            root = NULL;
            return p;  //把root的右孩子当做根结点
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
