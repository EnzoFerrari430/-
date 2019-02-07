#pragma once
#include <stdio.h>

typedef int Type;

typedef struct SplayTreeNode
{
	Type key;
	struct SplayTreeNode* left;
	struct SplayTreeNode* right;
}Node, *SplayTree;

//外部接口函数

//前序遍历伸展树
void preorder_splaytree(SplayTree tree);

//中序遍历伸展树
void inorder_splaytree(SplayTree tree);

//后序遍历伸展树
void postorder_splaytree(SplayTree tree);

//递归实现查找伸展树x中键值为key的结点
Node* splaytree_search(SplayTree x, Type key);

//非递归实现查找伸展树x中键值为key的结点
Node* iterative_splaytree_search(SplayTree x, Type key);

//查找最小结点:返回tree为根结点的伸展树的最小结点
Node* splaytree_minimum(SplayTree tree);

//查找最大结点:返回tree为根结点的伸展树的最大结点
Node* splaytree_maximum(SplayTree tree);

//旋转key对应结点的结点为根结点
Node* splaytree_splay(SplayTree tree, Type key);

//将结点插入到伸展树中，并返回根结点
Node* insert_splaytree(SplayTree tree, Type key);

//删除结点(key为结点的值),并返回根结点
Node* delete_splaytree(SplayTree tree, Type key);

//销毁伸展树
void destroy_splaytree(SplayTree tree);

//打印伸展树
void print_splaytree(SplayTree tree, Type key, int direction);

//访问结点
Node* access_splaytree(SplayTree tree, Type key);