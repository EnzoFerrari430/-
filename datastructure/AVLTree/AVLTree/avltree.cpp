#include "avltree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/*
AVL树，是最先发明的自平衡二叉搜索树，他的特点是AVL树中任何结点的两个子树的高度最大差是1

所以在删除或者插入结点的时候就经常会造成AVL树失衡。
失衡只能是下面4种状态：
LL(左左),LR(左右),RR(右右),RL(右左)
1)LL:插入或者删除一个结点后,根的左子树的左子树还有非空结点，导致"根的左子树的高度"比"根的右子树的高度"大2，导致AVL树失去平衡
2)LR:插入或者删除一个结点后,根的左子树的右子树还有非空结点，导致"根的左子树的高度"比"根的右子树的高度"大2，导致AVL树失去平衡
3)RL:插入或者删除一个结点后,根的右子树的左子树还有非空结点，导致"根的右子树的高度"比"根的左子树的高度"大2，导致AVL树失去平衡
4)RR:插入或者删除一个结点后,根的右子树的右子树还有非空结点，导致"根的右子树的高度"比"根的左子树的高度"大2，导致AVL树失去平衡

LL的旋转:
	LL是左边偏重了，	
*/

#define HEIGHT(p)	((NULL ==p)? 0 : (((Node*)(p))->height))
#define MAX(a,b)	( (a)>(b) ? (a) : (b) )

//获取AVL树的高度
int avltree_height(AVLTree tree)
{
	return HEIGHT(tree);
}

//前序遍历AVL树:根左右
void preorder_avltree(AVLTree tree)
{
	if (NULL != tree)
	{
		printf("%d ",tree->key);
		preorder_avltree(tree->left);
		preorder_avltree(tree->right);
	}
}

//中序遍历AVL树：左根右
void inorder_avltree(AVLTree tree)
{
	if (NULL != tree)
	{
		inorder_avltree(tree->left);
		printf("%d ",tree->key);
		inorder_avltree(tree->right);
	}
}

//后序遍历AVL树：左右根
void postorder_avltree(AVLTree tree)
{
	if (NULL != tree)
	{
		postorder_avltree(tree->left);
		postorder_avltree(tree->right);
		printf("%d ",tree->key);
	}
}

//递归查找AVL树x中键值为key的结点
Node* avltree_search(AVLTree x, Type key)
{
	if (x->key == key || x == NULL)
	{
		return x;
	}
	else if (x->key < key)  //key值比根结点大
	{
		avltree_search(x->right, key);
	}
	else
	{
		avltree_search(x->left, key);
	}
}

//非递归查找AVL树x中键值为key的结点
Node* iterative_avltree_search(AVLTree x, Type key)
{
	Node *p = x;
	while (p)
	{
		if (key == p->key)
			break;
		else if (key < p->key)
			p = p->left;
		else
			p = p->right;
	}
	return p;  //不管是不是NULL
}


/*
打印AVL树
tree是AVL树的结点
key是AVL树的键值
direction表示该结点的类型：0表示根结点 -1表示左孩子 1表示右孩子
*/
void print_avltree(AVLTree tree, Type key, int direction)
{
	if (NULL != tree)
	{
		if (0 == direction)
		{
			printf("%2d is root\n", tree->key);
		}
		else
		{
			printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");
		}
		print_avltree(tree->left, tree->key, -1);
		print_avltree(tree->right, tree->key, 1);
	}
}


/*
查找最小结点：返回tree为根结点的AVL树的最小结点
该结点必定在最左边
*/
Node* avltree_minimum(AVLTree tree)
{
	Node* p = tree;
	if (NULL == tree)
	{
		return NULL;
	}
	else
	{
		while (p->left)
		{
			p = p->left;
		}
	}
	return p;
}

/*
查找最小结点：返回tree为根结点的AVL树的最小结点
该结点必定在最左边
*/
Node* avltree_maximum(AVLTree tree)
{
	Node* p = tree;
	if (NULL == tree)
	{
		return NULL;
	}
	else
	{
		while (p->right)
		{
			p = p->right;
		}
	}
	return p;
}

//创建根结点
static Node* avltree_create_node(Type key, Node* left, Node* right)
{
	Node* p = (Node*)malloc(sizeof(Node));
	assert(p != NULL);

	p->key = key;
	p->height = 0;
	p->left = left;
	p->right = right;
	return p;
}

/*
LL旋转:返回旋转后的根结点
*/
static Node* left_left_rotation(AVLTree tree)
{
	Node* left_node = tree->left;
	tree->left = left_node->right;
	left_node->right = tree;

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	left_node->height = MAX(HEIGHT(left_node->left), tree->height) + 1;

	return left_node;
}

/*
RR旋转:返回旋转后的根结点
*/
static Node* right_right_rotation(AVLTree tree)
{
	Node* right_node = tree->right;
	tree->right = right_node->left;
	right_node->left = tree;

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	right_node->height = MAX(tree->height, HEIGHT(right_node->right)) + 1;

	return right_node;
}

/*
LR旋转:返回旋转后的根结点
1.对着根结点的孙子结点(left_right_node)RR旋转
2.将left_right_node再进行LL旋转
*/
static Node* left_right_rotation(AVLTree tree)
{
	Node* left_node = tree->left;
	Node* left_right_node = left_node->right;

	//RR旋转
	left_node->right = left_right_node->left;
	left_right_node->left = left_node;
	tree->left = left_right_node;

	//LL旋转
	tree->left = left_right_node->right;
	left_right_node->right = tree;

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	left_node->height = MAX(HEIGHT(left_node->left), HEIGHT(left_node->right)) + 1;
	left_right_node->height = MAX(tree->height, left_node->height) + 1;

	return left_right_node;
}

/*
RL旋转:返回旋转后的根结点
1.对着根结点的孙子结点(right_left_node)LL旋转
2.将right_left_node再进行RR旋转
*/
static Node* right_left_rotation(AVLTree tree)
{
	Node* right_node = tree->right;
	Node* right_left_node = right_node->left;

	//LL旋转
	right_node->left = right_left_node->right;
	right_left_node->right = right_node;
	tree->right = right_left_node;

	//RR旋转
	tree->right = right_left_node->left;
	right_left_node->left = tree;

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	right_node->height = MAX(HEIGHT(right_node->left), HEIGHT(right_node->right)) + 1;
	right_left_node->height = MAX(tree->height, right_node->height) + 1;

	return right_left_node;
}

/*
将结点插入到AVL树中，并返回根结点
*/
Node* avltree_insert(AVLTree tree, Type key)
{
	if (NULL == tree)
	{
		//创建结点
		tree = avltree_create_node(key, NULL, NULL);
		assert(tree != NULL);
	}
	else if (key < tree->key)  //插入到左子树
	{
		tree->left = avltree_insert(tree->left, key);
		//插入结点后，若AVL树失去平衡，则进行相应的调节,LL和LR情况
		if ((HEIGHT(tree->left) - HEIGHT(tree->right)) == 2)
		{
			if (key < tree->left->key)
			{
				//插入到左左部分
				tree = left_left_rotation(tree);
			}
			else
			{
				//插入到左右部分
				tree = left_right_rotation(tree);
			}
		}
	}
	else if (key > tree->key)  //插入到右子树
	{
		tree->right = avltree_insert(tree->right, key);
		//插入结点后，若AVL树失去平衡，则进行相应的调节,RR和RL情况
		if ((HEIGHT(tree->right) - HEIGHT(tree->left)) == 2)
		{
			if (key < tree->right->key)
			{
				//插入到RL部分
				tree = right_left_rotation(tree);
			}
			else
			{
				//插入到RR部分
				tree = right_right_rotation(tree);
			}
		}
	}

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	return tree;
}

/*
后继结点：最接近该结点的右侧结点
*/
Node* avltree_successor(Node* x)
{
	Node* p = NULL;
	//如果x有右孩子，则后继结点必定在右孩子为根结点的最左结点
	if (x->right)
	{
		p = avltree_minimum(x->right);
	}
	return p;
}


/*
前驱结点：最接近该结点的左侧结点
*/
Node* avltree_predecessor(Node *x)
{
	Node* p = NULL;
	//如果x有左孩子，则前驱结点必定在左孩子为根结点的最右结点
	if (x->left)
	{
		p = avltree_maximum(x->left);
	}
	return p;
}


/*
分析：
	分类讨论1：
		如果是叶结点：
			free该结点，再判断平衡情况。平衡情况就只用判断该叶结点的父结点是否平衡就好。因为这棵树的前提是一棵AVL树。
			现在假设父结点是root，要删除的结点x是root的左结点，root的右孩子是y，不管y是不是NULL
			没删除x结点前有3种情况：
				1.x->height == y->height
					这种情况直接free该结点就好。
				2.x->height > y->height  y结点为NULL
					这种情况free该结点，然后再重新计算出这一支子树的高度
				3.x->height < y->height  y结点的孩子结点不为空
					这种情况free该结点，然后进行旋转操作，再重新计算出这一支子树的高度
		如果不是叶结点：
			方案一：把删除该结点后剩余的元素，全部打散，再重新插入  - -！
			方案二：现在在查阅BinarySearchTree之后，类似于BinarySearchTree的删除方法，找到前驱,交换前驱数据
			方案三：网上高手的递归删除法
	分类讨论2：
		该结点有2个孩子结点：
		该结点有1个孩子结点：
		该结点有0个孩子结点：
*/
/*
删除结点(key是结点的值)，返回根结点
*/
static Node* delete_node(AVLTree tree, Node* z)
{
	//递归出口
	if (NULL == tree || NULL == z)
	{
		return NULL;
	}

	if (z->key < tree->key)  //删左边
	{
		tree->left = delete_node(tree->left, z);
		if (2 == (HEIGHT(tree->right) - HEIGHT(tree->left)))
		{
			if (HEIGHT(tree->right->left) > HEIGHT(tree->right->right))
			{
				//高度差是右孩子的左子树造成的,RL旋转
				tree = right_left_rotation(tree);
			}
			else
			{
				//RR旋转
				tree = right_right_rotation(tree);
			}
		}
	}
	else if (z->key > tree->key)  //删右边
	{
		tree->right = delete_node(tree->right, z);
		if (2 == (HEIGHT(tree->left) - HEIGHT(tree->right)))
		{
			if (HEIGHT(tree->left->right) > HEIGHT(tree->left->left))
			{
				//高度差是右孩子的左子树造成的,LR旋转
				tree = left_right_rotation(tree);
			}
			else
			{
				//LL旋转
				tree = left_left_rotation(tree);
			}
		}
	}
	else  //z == tree
	{
		//采用方案2
		//该结点有2个孩子结点
		if ((tree->left) && (tree->right))
		{
			if (HEIGHT(tree->left) > HEIGHT(tree->right))
			{
				//类似于BinarySearchTree的删除方法，找到前驱,交换前驱数据
				Node* max = avltree_predecessor(tree->left);
				tree->key = max->key;
				tree->left = delete_node(tree->left, max);
			}
			else
			{
				//类似于BinarySearchTree的删除方法。
				//注意，这里要用的是后继结点去替换当前结点
				Node* min = avltree_successor(tree->right);
				tree->key = min->key;
				tree->right = delete_node(tree->right, min);
			}
		}
		else  //只有1个或0个结点
		{
			Node* tmp = tree;
			tree = tree->left ? tree->left : tree->right;
			free(tmp);
		}
	}
	return tree;
}

Node* avltree_delete(AVLTree tree, Type key)
{
	Node* p = iterative_avltree_search(tree, key);
	if (NULL == p)
	{
		//printf("this node does not exist\n");
		return tree;
	}

	tree = delete_node(tree, p);
	//删除一个结点之后要重新调整结点的高度
	avltree_fixheight(tree);
	return tree;
}

/*
递归的调整树的每个结点的高度信息
*/
void avltree_fixheight(AVLTree tree)
{
	if (tree->left)
	{
		avltree_fixheight(tree->left);
	}
	if (tree->right)
	{
		avltree_fixheight(tree->right);
	}
	if (NULL == tree->left && NULL == tree->right)
	{
		tree->height = 1;
	}
	else
	{
		tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	}
}

/*
递归销毁AVLTree
*/
void destroy_avltree(AVLTree tree)
{
	//递归出口
	if (NULL == tree)
	{
		return;
	}
	if (tree->left)
	{
		destroy_avltree(tree->left);
	}
	if (tree->right)
	{
		destroy_avltree(tree->right);
	}
	if (NULL == tree->left && NULL == tree->right)
	{
		free(tree);
		tree = NULL;
	}
}