#pragma once

typedef int Type;

typedef struct _LeftistNode
{
	Type key;
	int npl;
	struct _LeftistNode *left;
	struct _LeftistNode *right;
}LeftistNode, *LeftistHeap;

//前序遍历
void preorder_leftist(LeftistHeap heap);
//中序遍历
void inorder_leftist(LeftistHeap heap);
//后序遍历
void postorder_leftist(LeftistHeap heap);

//获取最小值  成功返回0  失败返回-1
int leftist_minimum(LeftistHeap heap, int *pval);

//合并 左倾堆x 和左倾堆y  并返回合并后的新树
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y);

//将节点x插入到左倾堆中，并返回根节点
LeftistNode* insert_leftist(LeftistHeap heap, Type key);

//删除节点(key为节点的值)  并返回根节点
LeftistNode* delete_leftist(LeftistHeap heap);

//销毁左倾堆
void destroy_leftist(LeftistHeap heap);

//打印左倾堆
void print_leftist(LeftistHeap heap);