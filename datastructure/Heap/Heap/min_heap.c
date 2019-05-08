#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a))/sizeof((a[0])))

static int m_heap[30];			//数据
static int m_capacity = 30;		//总的容量
static int m_size = 0;			//实际容量

int minheap_insert(int data);
int minheap_filterup(int start);
void minheap_print();


int minheap_insert(int data)
{
	if (m_size == m_capacity)
		return -1;  //容量已满

	//没满的话
	m_heap[m_size] = data;
	//向上虑
	minheap_filterup(m_size);
	++m_size;
}

/*
向上虑

参数是起始位置
*/
int minheap_filterup(int start)
{
	int c = start;
	int p = (c - 1) / 2;
	int tmp = m_heap[start];
	//c>0 等价于 p>=0
	while (c > 0)
	{
		if (tmp > m_heap[p])
		{
			m_heap[c] = m_heap[p];
			c = p;
			p = (c - 1) / 2;
		}
		else
		{
			break;
		}
	}
	m_heap[c] = tmp;
}

//获取位置
static int get_index(int data)
{
	int i = 0;
	while (i < m_size)
	{
		if (m_heap[i] == data)
		{
			return i;
		}
		++i;
	}
	return -1;
}

int minheap_remove(int data)
{
	int index;
	if (m_size == 0)
		return -1;

	index = get_index(data);
	if (index == -1)
		return -1;

	m_heap[index] = m_heap[--m_size];
	minheap_filterdown(index, m_size - 1);
	return  0;
}

int minheap_filterdown(int start, int end)
{
	int p = start;
	int l = 2 * p + 1;
	int tmp = m_heap[p];
	while (l <= end)
	{
		if (l < end && m_heap[l] > m_heap[l + 1])
		{
			++l;  //选出左右孩子中较小的那个
		}
		if (tmp > m_heap[l])
		{
			m_heap[p] = m_heap[l];
			p = l;
			l = 2 * l + 1;
		}
		else
		{
			break;
		}
	}
	m_heap[p] = tmp;

}

void minheap_print()
{
	int i;
	for (i = 0; i < m_size; ++i)
	{
		printf("%d ", m_heap[i]);
	}
}

int main()
{
	int a[] = { 10,40,30,60,90,70,20,50,80 };
	int i, len = LENGTH(a);
	printf("== 依次添加: ");
	for (i = 0; i < len; ++i)
	{
		printf("%d ", a[i]);
		minheap_insert(a[i]);
	}

	printf("\n====  最小堆: ");
	minheap_print();

	i = 15;
	minheap_insert(i);
	printf("\n== 添加元素: %d", i);
	printf("\n==最小堆: ");
	minheap_print();

	i = 10;
	minheap_remove(i);
	printf("\n== 删除元素: %d", i);
	printf("\n== 最小堆: ");
	minheap_print();
	printf("\n");


	i = 80;
	minheap_remove(i);
	printf("\n== 删除元素: %d", i);
	printf("\n== 最小堆: ");
	minheap_print();
	printf("\n");

	return 0;
}