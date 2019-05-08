/*
左倾堆是一棵二叉树，它的节点除了左右子树指针之外，还有2个属性：键值和零距离
	1.键值的作用是比较节点的大小，从而对节点进行排序
	2.零距离(NPL Null Path Length)则是从一个节点到一个"最近的不满节点"的路径长度。不满节点是指该节点的左右孩子至少有一个为NULL，叶节点的NPL为0，NULL节点的NPL为-1

左倾堆的基本性质
	1.节点的键值小于或等于它的左右孩子节点的键值
	2.节点的左孩子的NPL >= 右孩子的NPL
	3.节点的NPL = 它的右孩子的NPL + 1

左倾堆能很好的解决 "合并两个优先队列" 的问题。  左倾堆的合并操作的平摊时间复杂度是O(logn),而完全二叉堆为O(n)
合并就是左倾堆的重点， 插入和删除的操作都是以合并为基础   插入操作就可以看成2棵二叉树合并  删除操作就可以看成移除根节点后，再合并左右两棵左倾树

合并2棵左倾堆的基本思想
	1.如果一个空左倾堆与一个非空左倾堆合并，返回非空左倾堆
	2.如果两个左倾堆都非空，那么比较两个根节点，取较小堆的根节点为新的根节点。将"较小堆的根节点的右孩子"和"较大堆"进行合并
	3.如果新堆的右孩子的NPL > 左孩子的NPL， 则交换左右孩子
	4.设置新堆的根节点的NPL = 右子堆的NPL + 1

*/
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "leftist.h"

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))

int main()
{
	int i;
	int a[] = { 10,40,24,30,36,20,12,16 };
	int b[] = { 17,13,11,15,19,21,23 };
	int alen = LENGTH(a);
	int blen = LENGTH(b);
	LeftistHeap ha, hb;
	ha = hb = NULL;

	printf("\n== 左倾堆(ha)依次添加: ");
	for (i = 0; i < alen; ++i)
	{
		printf("%d ", a[i]);
		ha = insert_leftist(ha, a[i]);
	}
	printf("\n== 左倾堆(ha)的详细信息: \n");
	print_leftist(ha);

	printf("\n== 左倾堆(hb)依次添加: ");
	for (i = 0; i < blen; ++i)
	{
		printf("%d ", b[i]);
		hb = insert_leftist(hb, b[i]);
	}
	printf("\n== 左倾堆(ha)的详细信息: \n");
	print_leftist(hb);

	ha = merge_leftist(ha, hb);
	printf("\n== 合并ha和hb后的详细信息: \n");
	print_leftist(ha);


	destroy_leftist(ha);

	system("pause");
	return 0;

}

