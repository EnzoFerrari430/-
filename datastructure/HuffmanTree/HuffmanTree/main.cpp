﻿/*
哈夫曼树(HuffmanTree)
定义：给定n个权值作为n个叶子结点，构造一棵二叉树，若树的带权路径长度达到最小，则这棵树被称为哈夫曼树。

百度的定义：给定n个权值作为n个叶子结点，构造一个二叉树，若该树的带权路径长度达到最小，称这样的二叉树为最优二叉树，也称为哈夫曼树。哈夫曼树是带权路径长度最短的树，权值较大的结点离根结点较近

例子：
			180
			/ \
		   /   \
		  100   80
		        / \
			   /   \
			  50   30
				   / \
				  /   \
				 20   10

名词解释：
	1.路径和路径长度
		定义:在一棵树中，从一个结点往下走可以达到的孩子或者是孙子结点之间的通路，称为路径。通路中分支的数目(线段的数目)称为路径长度。
			若规定根结点的层数为1，则从根结点到第L层结点的路径长度为L-1

		在例子中，100和80的路径长度是1,50和30的路径长度是2,20和10的路径长度是3

	2.结点的权及带权路径长度
		定义:若将树中结点赋给一个有某种含义的数值，则这个数值称为该结点的权。结点的带权路径长度为:从根结点到该结点之间的路径长度与该结点的权的乘积

		在例子中，结点20的路径长度是3，它的带权路径长度 = 路径长度 * 权 = 3 * 20 = 60

	3.树的带权路径长度
		定义:树的带权路径长度规定为所有 "叶子结点" 的带权路径长度之和，记为WPL

		在例子中树的WPL = 1 * 100 + 2 * 50 + 3 * 20 + 3 * 10 = 290


假设有n个权值，则构造出的哈夫曼树有n个叶子结点。n个权值分别设为w1,w2...wn，哈夫曼树的构造规则
	1.将w1,w2...wn看成是n棵树的森林(每棵树仅有一个结点)
	2.在森林中选出根节点的权值最小的两个树进行合并，作为一棵新树的左，右子树，且新树的根结点权值为其左，右子树根结点权值之和
	3.在森林中删除选取的两个树，并将新树加入森林
	4.重复 2 3步，直到森林中只剩一棵树为止，该树即为所求得的哈夫曼树



*/

#include <stdio.h>
#include "huffman.h"

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))

int main()
{
	int a[] = { 5,6,8,7,15 };
	int i, ilen = LENGTH(a);
	HuffmanTree root = NULL;

	printf("== 添加数组: ");
	for (i = 0; i < ilen; ++i)
	{
		printf("%d ", a[i]);
	}

	//创建数组对应的Huffman树
	root = create_huffman(a, ilen);

	printf("==树的详细信息: \n");
	print_huffman(root);

	//销毁二叉树
	destroy_huffman(root);
	return 0;
}