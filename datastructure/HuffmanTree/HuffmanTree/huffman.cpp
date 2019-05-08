#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "huffman.h"

/*
//快速排序
static int sort(Type arr[], int first, int last)
{
	int i = first, j = last, temp;
	while (i < j)
	{
		while ((arr[i] < arr[j]) && (i < j))
			--j;
		if (arr[i] < arr[j])
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		while ((arr[i] < arr[j]) && (i < j))
			++i;
		if (arr[i] < arr[j])
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	return i;
}

static void quick_sort(Type arr[], int first, int last)
{
	int mid;
	if (first >= last)
	{
		return;
	}
	mid = sort(arr, first, last);
	quick_sort(arr, first, mid - 1);
	quick_sort(arr, mid + 1, last);
}



//先排序
//找最小的两个数字连接起来
//连起来之后再进行排序
//再找最小的两个数字连接起来
//连起来之后再进行排序

HuffmanTree create_huffman(Type arr[], int size)
{
	//先排序
	int first = 0, last = size - 1;
	quick_sort(arr, first, last);
	HuffmanTree T = (HuffmanNode *)malloc(sizeof(HuffmanNode));
	assert(T != NULL);
	//创建结点
	HuffmanNode *p1, *p2;
	for (int i = 1; i < size; ++i)
	{
		
	}
}
*/

//创建最小堆
extern void create_minheap(Type a[], int size);
//新建一个节点，并将最小堆中最小节点的数据复制给该节点
extern HuffmanNode* dump_from_minheap();
//将data插入到二叉堆中。 0表示成功  -1表示失败
extern int dump_to_minheap(HuffmanNode* node);
//销毁最小堆
extern void destroy_minheap();


HuffmanNode* huffman_create_node(Type key, HuffmanNode* left, HuffmanNode* right, HuffmanNode* parent)
{
	HuffmanNode* p;
	p = (HuffmanNode*)malloc(sizeof(HuffmanNode));
	if (p == NULL)
		return NULL;
	p->key = key;
	p->left = left;
	p->right = right;
	p->parent = parent;

	return p;
}


//创建Huffman树，返回Huffman树的根
HuffmanNode* create_huffman(Type a[], int size)
{
	int i;
	HuffmanNode *left, *right, *parent = NULL;

	//建立数组a对应的最小堆
	create_minheap(a, size);


	//用二叉堆找最小值快速方便
	for (i = 0; i < size - 1; ++i)
	{
		left = dump_from_minheap();
		right = dump_from_minheap();
		parent = huffman_create_node(left->key + right->key, left, right, NULL);
		left->parent = parent;
		right->parent = parent;

		//将parent节点数据拷贝到最小堆中
		if (dump_to_minheap(parent) != 0)
		{
			printf("插入失败!\n结束程序\n");
			destroy_huffman(parent);
			parent = NULL;
			break;
		}
	}

	//销毁最小堆
	destroy_minheap();

	return parent;
}

void destroy_huffman(HuffmanTree T)
{
	if (T == NULL)
		return;

	if (T->left != NULL)
		destroy_huffman(T->left);
	if (T->right != NULL)
		destroy_huffman(T->right);

	free(T);
}


/*
HuffmanTree T:Huffman树的节点
Type key:节点的键值

int direction:
	0	表示该节点是根节点
	-1	表示该节点是父节点的左孩子
	1	表示该节点是父节点的右孩子
*/
void huffman_print(HuffmanTree T, Type key, int direction)
{
	if (T == NULL)
		return;
	
	if (0 == direction)
		printf("\t%2d is root\n", T->key);
	else
	{
		printf("%2d is %2d's %6s child\n", T->key, key, direction == 1 ? "right" : "left");
	}
	huffman_print(T->left, T->key, -1);
	huffman_print(T->right, T->key, 1);

}

void print_huffman(HuffmanTree T)
{
	if (T != NULL)
		huffman_print(T, T->key, 0);
}


//前序遍历	根左右
void preorder_huffman(HuffmanTree T)
{
	if (T != NULL)
	{
		printf("%d ", T->key);
		preorder_huffman(T->left);
		preorder_huffman(T->right);
	}
}

//中序遍历	左根右
void inorder_huffman(HuffmanTree T)
{
	if (T != NULL)
	{
		preorder_huffman(T->left);
		printf("%d ", T->key);
		preorder_huffman(T->right);
	}
}

//后序遍历	左右根
void postorder_huffman(HuffmanTree T)
{
	if (T != NULL)
	{
		preorder_huffman(T->left);
		preorder_huffman(T->right);
		printf("%d ", T->key);
	}
}


