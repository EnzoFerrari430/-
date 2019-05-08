#pragma once

typedef int Type;

typedef struct _HuffmanNode
{
	Type key;  //权值
	struct _HuffmanNode *left;
	struct _HuffmanNode *right;
	struct _HuffmanNode *parent;
}HuffmanNode, *HuffmanTree;


//前序遍历
void preorder_huffman(HuffmanTree T);

//中序遍历
void inorder_huffman(HuffmanTree T);

//后序遍历
void postorder_huffman(HuffmanTree T);

//创建Huffman树
HuffmanTree create_huffman(Type arr[], int size);

//销毁Huffman树
void destroy_huffman(HuffmanTree T);

//打印Huffman树
void print_huffman(HuffmanTree T);