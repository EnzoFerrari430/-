/*
堆的定义:
	堆(heap),这里所说的堆是数据结构中的堆，而不是内存模型中的堆，堆通常是一个可以被看做一棵树，它满足下列性质
		1.堆中任意结点的值总是不大于（不小于）其子节点的值
		2.堆总是一棵完全树

二叉堆的定义：
	二叉堆是完全二叉树或者近似完全二叉树，它分为两种：最大堆和最小堆
	最大堆：父节点的键值总是大于或等于任何一个子节点的键值
	最小堆：父节点的键值总是小于或等于任何一个子节点的键值

二叉堆一般以数组来实现
	int a[9] = {90,80,70,60,40,30,20,10,50};
	最大堆的性质(第一个元素的索引为0)
	1.索引为i的左孩子的索引是2*i+1
	2.索引为i的右孩子的索引是2*i+2
	3.索引为i的父节点的索引是 (i-1)/2  （整数相除会省去小数部分）



添加
	假设在最大堆[90,80,70,60,40,30,20,10,50]中添加85 步骤如下
		1.将85加到末尾
		2.85大于父节点(40)，将它和父节点交换
		3.重复第二步，直到小于父节点或根节点


删除
	假设从最大堆[90,85,70,60,80,30,20,10,50,40]中删除90 步骤如下
		1.将90从二叉堆中删除
		2.用末尾元素替换被删除的数据
		3.40小于子节点，选取较大的子节点和它交换
		4.重复步骤3，直到40不小于子节点或者40到达末尾

	
*/
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a))/sizeof((a[0])))

static int m_heap[30];			//数据
static int m_capacity = 30;		//总的容量
static int m_size = 0;			//实际容量

/*
最大堆的向上调整算法(从start开始向上，直到0，调整堆)

参数:start被上调节点的起始位置(一般为数组中最后一个元素的索引)
*/

static void maxheap_filterup(int start)
{
	int c = start;
	int p = (c - 1) / 2;
	int tmp = m_heap[c];  //当前节点current大小
	while (c > 0)
	{
		if (m_heap[p] >= tmp)
			break;
		else
		{
			m_heap[c] = m_heap[p];
			c = p;
			p = (p - 1) / 2;
		}
	}
	m_heap[c] = tmp;
}

/*
将data插入到二叉树中

返回0 表示成功
返回-1表示失败

*/

int maxheap_insert(int data)
{
	if (m_size == m_capacity)
		return -1;
	m_heap[m_size] = data;
	maxheap_filterup(m_size);
	m_size++;

	return 0;
}



/*
最大堆的删除代码

返回data在二叉堆中的索引

返回值：
	存在		返回data在数组中的索引
	不存在	返回-1

*/
int get_index(int data)
{
	int i = 0;
	for (i = 0; i < m_size; ++i)
	{
		if (data == m_heap[i])
		{
			return i;
		}
	}
	return -1;
}

/*

最大堆的向下调整算法

注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1),右孩子的索引值是(2N+2)

参数说明
	start		被下调节点的起始位置(一般为0，表示从第i个元素开始)
	end			截至范围(一般为数组中最后一个元素的索引)

*/
static void maxheap_filterdown(int start, int end)
{
	int c = start;			//当前节点的位置
	int l = 2 * c + 1;		//左孩子的位置
	int tmp = m_heap[c];	//当前节点的大小

	while (l <= end)
	{
		//l是左孩子  l+1是右孩子
		if (l < end && m_heap[l] < m_heap[l + 1])
		{
			l++;  //左右孩子中选择较大者，即 m_heap[l+1]
		}
		if (tmp >= m_heap[l])
			break;  //调整结束
		else
		{
			m_heap[c] = m_heap[l];
			c = l;
			l = 2 * l + 1;
		}
	}
	m_heap[c] = tmp;
}

/*

删除最大堆中的data

返回0 表示成功
返回-1表示失败

*/

int maxheap_remove(int data)
{
	int index;
	//如果堆已空就返回-1
	if (m_size == 0)
		return -1;

	//获取data在数组中的索引
	index = get_index(data);
	if (index == -1)
		return -1;

	m_heap[index] = m_heap[--m_size];  //用最后的元素补
	maxheap_filterdown(index, m_size - 1);
	
	return 0;
}

void maxheap_print()
{
	int i;
	for (i = 0; i < m_size; ++i)
	{
		printf("%d ", m_heap[i]);
	}
}

//int main()
//{
//	int a[] = { 10,40,30,60,90,70,20,50,80 };
//	int i, len = LENGTH(a);
//	printf("== 依次添加: ");
//	for (i = 0; i < len; ++i)
//	{
//		printf("%d ", a[i]);
//		maxheap_insert(a[i]);
//	}
//
//	printf("\n====  最大堆: ");
//	maxheap_print();
//
//	return 0;
//}