#include "leftist.h"
#include <stdio.h>
#include <stdlib.h>

//ǰ�����  ������
void preorder_leftist(LeftistHeap heap)
{
	if (heap)
	{
		printf("%d ", heap->key);
		preorder_leftist(heap->left);
		preorder_leftist(heap->right);
	}
}

//�������
void inorder_leftist(LeftistHeap heap)
{
	if (heap)
	{
		inorder_leftist(heap->left);
		printf("%d ", heap->key);
		inorder_leftist(heap);
	}
}

//�������
void postorder_leftist(LeftistHeap heap)
{
	if (heap)
	{
		postorder_leftist(heap->left);
		postorder_leftist(heap->right);
		printf("%d ", heap->key);
	}
}

//��ȡ��Сֵ  �ɹ�����0  ʧ�ܷ���-1

int leftist_minimum(LeftistHeap heap, int *pval)
{
	if (!heap)
		return -1;
	
	*pval = heap->key;
	return 0;
}

//����t�����Һ���  ���ｻ��ָ��ָ��
static void swap_node(LeftistHeap t)
{
	LeftistNode* temp = t->left;
	t->left = t->right;
	t->right = temp;
}

//�ϲ������x��y  �����غϲ��������
//�ϲ�2������ѵĻ���˼��
//1.���һ�����������һ���ǿ�����Ѻϲ������طǿ������
//2.�����������Ѷ��ǿգ���ô�Ƚ��������ڵ㣬ȡ��С�ѵĸ��ڵ�Ϊ�µĸ��ڵ㡣��"��С�ѵĸ��ڵ���Һ���"��"�ϴ��"���кϲ�
//3.����¶ѵ��Һ��ӵ�NPL > ���ӵ�NPL�� �򽻻����Һ���
//4.�����¶ѵĸ��ڵ��NPL = ���Ӷѵ�NPL + 1
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


//���ڵ�x���뵽������У������ظ��ڵ�
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
















