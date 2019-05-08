#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"


/*

��С��: ΪHuffman������

*/

static HuffmanNode *m_heap;		//��С������
static int m_capacity;			//�ܵ�����
static int m_size;				//��ǰ��Ч���ݵ�����


static void minheap_filterdown(int start, int end)
{
	int c = start;			//��ǰ�ڵ�
	int l = 2 * c + 1;		//���ӽڵ�
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

//����ڵ�  ���ϵ���
//�ɹ�����0  ʧ�ܷ���-1
int dump_to_minheap(HuffmanNode* node)
{
	if (m_size == m_capacity)
		return -1;
	m_heap[m_size] = *node;
	minheap_filterup(m_size);
	++m_size;
	return 0;
}


//����С���е���С��Ԫ��ȡ����
//�ٵ�����С�ѣ�ʹ֮���³�Ϊһ����С��
HuffmanNode* dump_from_minheap()
{
	if (m_size == 0)
		return NULL;
	HuffmanNode *pNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
	if (pNode == NULL)
		return NULL;

	//������С�ڵ�����ݸ�node
	*pNode = m_heap[0];
	//�����һ���ڵ�����ݺ͵�һ���ڵ�����ݽ��н���
	swap_node(0, m_size - 1);
	//����֮���ٽ���һ���³�����
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

	//��ʼ������
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