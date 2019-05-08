#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"


/*

最小堆: 为Huffman树服务

*/

static HuffmanNode *m_heap;		//最小堆数组
static int m_capacity;			//总的容量
static int m_size;				//当前有效数据的数量


static void minheap_filterdown(int start, int end)
{
	int c = start;			//当前节点
	int l = 2 * c + 1;		//左孩子节点
	HuffmanNode tmp = m_heap[c];
	while (l <= end)
	{
		if (l < end && m_heap[l].key > m_heap[l + 1].key)
			++l;
		if (tmp.key > m_heap[l].key)
		{
			m_heap[c] = m_heap[l];
			c = l;
			l = 2 * l + 1;
		}
		else
		{
			break;
		}
	}
	m_heap[c] = tmp;
}

static void minheap_filterup(int start)
{
	int c = start;
	int p = (c - 1) / 2;
	HuffmanNode tmp = m_heap[c];
	while (p >= 0)
	{
		if (m_heap[p].key > tmp.key)
		{
			m_heap[c] = m_heap[p];
		}
		else
		{
			break;
		}
		c = p;
		p = (p - 1) / 2;
	}
	m_heap[c] = tmp;
}

static void swap_node(int i, int j)
{
	HuffmanNode tmp = m_heap[i];
	m_heap[i] = m_heap[j];
	m_heap[j] = tmp;
}

//插入节点  向上调整
//成功返回0  失败返回-1
int dump_to_minheap(HuffmanNode* node)
{
	if (m_size == m_capacity)
		return -1;
	m_heap[m_size] = *node;
	minheap_filterup(m_size);
	++m_size;
	return 0;
}


//将最小堆中的最小的元素取出来
//再调整最小堆，使之重新成为一个最小堆
HuffmanNode* dump_from_minheap()
{
	if (m_size == 0)
		return NULL;
	HuffmanNode *pNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
	if (pNode == NULL)
		return NULL;

	//复制最小节点的数据给node
	*pNode = m_heap[0];
	//将最后一个节点的数据和第一个节点的数据进行交换
	swap_node(0, m_size - 1);
	//交换之后再进行一次下沉调整
	minheap_filterdown(0, m_size - 2);
	--m_size;
	
	return pNode;
}


void create_minheap(Type a[], int size)
{
	int i;

	m_size = size;
	m_capacity = size;
	m_heap = (HuffmanNode *)malloc((sizeof(HuffmanNode))*size);

	//初始化数组
	for (i = 0; i < size; ++i)
	{
		m_heap[i].key = a[i];
		m_heap[i].parent = m_heap[i].left = m_heap[i].right = NULL;
	}

	for (i = (size - 1) / 2; i >= 0; --i)
	{
		minheap_filterdown(i, size - 1);
	}
}

void destroy_minheap()
{
	m_size = 0;
	m_capacity = 0;
	free(m_heap);
}