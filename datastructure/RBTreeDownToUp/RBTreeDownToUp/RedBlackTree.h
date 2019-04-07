#pragma once

#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
typedef enum ColorType {Red,Black}ColorType;
typedef int ElementType;
#define Infinity 9999
#define NegInfinity -9999
//struct RedBlackNode;
//typedef struct RedBlackNode RedBlackNode;
//typedef struct RedBlackNode* RedBlackTree;
//typedef struct RedBlackNode* Position;
//extern Position NullNode;
typedef struct RedBlackNode
{
	ElementType Element;
	struct RedBlackNode *Left;
	struct RedBlackNode *Right;
	struct RedBlackNode *Parent;  //多加一个指向父结点的指针
	ColorType Color;
}RedBlackNode,* RedBlackTree,* Position;
extern Position NullNode;


//初始化红黑树
RedBlackTree Initialize(void);
//前序遍历红黑树
void preorder_redblacktree(RedBlackTree T);
//中序遍历红黑树
void inorder_redblacktree(RedBlackTree T);
//后序遍历红黑树
void postorder_redblacktree(RedBlackTree T);

//左旋转
void left_rotate(Position X, RedBlackTree T);

//右旋转
void right_rotate(Position X, RedBlackTree T);

//红黑树插入结点
RedBlackTree Insert(ElementType Item, RedBlackTree T);

//红黑树删除结点
RedBlackTree Delete(ElementType Item, RedBlackTree T);

RedBlackTree Tree_Successor(RedBlackTree T);


//打印红黑树  direct:0打印当前结点以及颜色  -1打印当前结点的左孩子以及颜色  1打印当前结点的右孩子以及颜色
void print_redblacktree(RedBlackTree T,ElementType element,int direct);

//查找最小结点:返回T为根结点的红黑树的最小结点
Position minium_redblacktree(RedBlackTree T);

//查找最大结点:返回T为根结点的红黑树的最大结点
Position maximum_redblacktree(RedBlackTree T);

//销毁红黑树
void destroy_RedBlackTree(RedBlackTree T);

