#include "leftist.h"
#include <stdio.h>
#include <stdlib.h>

//前序遍历  根左右
void preorder_leftist(LeftistHeap heap)
{
	if (heap)
	{
		printf("%d ", heap->key);
		preorder_leftist(heap->left);
		preorder_leftist(heap->right);
	}
}

//中序遍历
void inorder_leftist(LeftistHeap heap)
{
	if (heap)
	{
		inorder_leftist(heap->left);
		printf("%d ", heap->key);
		inorder_leftist(heap);
	}
}

//后序遍历
void postorder_leftist(LeftistHeap heap)
{
	if (heap)
	{
		postorder_leftist(heap->left);
		postorder_leftist(heap->right);
		printf("%d ", heap->key);
	}
}

//获取最小值  成功返回0  失败返回-1

int leftist_minimum(LeftistHeap heap, int *pval)
{
	if (!heap)
		return -1;
	
	*pval = heap->key;
	return 0;
}

//交换t的左右孩子  这里交换指针指向
static void swap_node(LeftistHeap t)
{
	LeftistNode* temp = t->left;
	t->left = t->right;
	t->right = temp;
}

//合并左倾堆x和y  并返回合并后的新树
//合并2棵左倾堆的基本思想
//1.如果一个空左倾堆与一个非空左倾堆合并，返回非空左倾堆
//2.如果两个左倾堆都非空，那么比较两个根节点，取较小堆的根节点为新的根节点。将"较小堆的根节点的右孩子"和"较大堆"进行合并
//3.如果新堆的右孩子的NPL > 左孩子的NPL， 则交换左右孩子
//4.设置新堆的根节点的NPL = 右子堆的NPL + 1
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y)
{
	if (x == NULL)
		return y;
	if (y == NULL)
		return x;

	if (x->key < y->key)
	{
		x->right = merge_leftist(x->right, y);
		if (x->left == NULL || x->left->npl < x->right->npl)
			swap_node(x);
		if (x->right == NULL || x->left == NULL)
			x->npl = 0;
		else
			x->npl = x->right->npl + 1;
		return x;
	}
	else
	{
		y->right = merge_leftist(y->right, x);
		if (y->left == NULL || y->left->npl < y->right->npl)
			swap_node(y);
		if (y->right == NULL || y->left == NULL)
			y->npl = 0;
		else
			y->npl = y->right->npl + 1;
		return y;
	}

}


//将节点x插入到左倾堆中，并返回根节点
LeftistNode* insert_leftist(LeftistHeap heap, Type key)
{
	LeftistNode* pNew = (LeftistNode*)malloc(sizeof(LeftistNode));
	pNew->npl = 0;
	pNew->left = pNew->right = NULL;
	pNew->key = key;
	return merge_leftist(heap, pNew);
}


LeftistNode* delete_leftist(LeftistHeap heap)
{
	if (heap == NULL)
		return NULL;
	LeftistNode* l = heap->left;
	LeftistNode* r = heap->right;
	free(heap);
	return merge_leftist(l, r);
}

void destroy_leftist(LeftistHeap heap)
{
	if (heap == NULL)
		return;
	if (heap->left != NULL)
		destroy_leftist(heap->left);
	if (heap->right != NULL)
		destroy_leftist(heap->right);

	free(heap);
}


static void leftist_print(LeftistHeap heap, Type key, int direction)
{
	if (heap != NULL)
	{
		if (direction == 0)
			printf("%2d(%d) is root\n", heap->key, heap->npl);
		else
			printf("%2d(%d) is %2d's %6s child\n", heap->key, heap->npl, key, direction == -1 ? "left" : "right");

		leftist_print(heap->left, heap->key, -1);
		leftist_print(heap->right, heap->key, 1);
	}
}

void print_leftist(LeftistHeap heap)
{
	if (heap != NULL)
		leftist_print(heap, heap->key, 0);
}
















