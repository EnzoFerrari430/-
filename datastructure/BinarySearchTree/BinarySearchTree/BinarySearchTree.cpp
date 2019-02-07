/*
	若一个结点有子树，那么该结点称为子树根的“双亲”(父亲结点)
	子树的根是该结点的“孩子”
	有相同双亲(父亲结点)的结点互为"兄弟"
	一个结点的所有子树上的任何结点都是该结点的后裔
	从根结点到某个结点的路径上的所有结点都是该结点的祖先

	结点的度：	结点拥有子树的数目
	叶子：		度为0的结点
	分支结点：	度不为0的结点
	树的度：		树中结点的最大的度

	层次：		根结点的层次为1，其余结点的层次等于该结点的双亲结点的层次加1
	树的高度：	树中结点的最大层次
	无序树：		如果树中结点的各子树之间的次序是不重要的，可以交换位置
	有序树：		如果树中结点的各子树之间的次序是重要的，不可以交换位置
	森林：		0个或多个不相交的树组成，对森林加上一个根，森林即成为树；删去根，树即成为森林

二叉树：  每个结点最多有2个子树的树结构
二叉树性质：
	1.二叉树第i层上结点的数目最多为2^^(i-1)
	2.高度为k的二叉树至多有2^^k - 1个结点
	3.包含n个结点的二叉树的高度至少为log2(n+1)
	4.在任意一颗二叉树中，若终端结点的个数为n0,度为2的结点的个数为n2，则n0 = n2 + 1

满二叉树：
	定义：高度为h并且有2^^h - 1个结点的二叉树，被称为满二叉树
完全二叉树：
	定义：一颗二叉树中，只有最下面2层结点的度可以小于2，并且最下一层的叶结点集中在靠左的若干位置上。这样的二叉树被称为完全二叉树。
	特点：叶子结点只能出现在最下层和次下层，且最下层的叶子结点集中在树的左部。一个满二叉树必定是完全二叉树，而完全二叉树未必是满二叉树
二叉搜索树：
	定义：设X为二叉搜索树中的一个结点，X结点包含关键字key，结点X的key值为key[X]。如果Y是X的左子树中的一个结点，则key[Y] <= key[X],如果Y是X的右子树的一个结点，则key[Y] >= key[X]
	性质：
		1.若任意结点的左子树不空，则左子树上所有结点的值均小于它的根结点的值
		2.若任意结点的右子树不空，则右子树上所有结点的值均大于它的根结点的值
		3.任意结点的左右子树也分别是二叉搜索树
		4.没有键值相等的结点
	前驱结点：结点key值小于该结点key值并且值最大的结点
	后继结点：结点key值大于该结点key值并且值最小的结点
*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <assert.h>
#include "BinarySearchTree.h"

/*
打印二叉树
tree是二叉树的结点
key是二叉树的键值
direction表示该结点的类型：0表示根结点 -1表示左孩子 1表示右孩子
*/
void print_bstree(BSTree tree, Type key, int direction)
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
		print_bstree(tree->left, tree->key, -1);
		print_bstree(tree->right, tree->key, 1);
	}
}

/*
静态函数只能在声明他的文档中可见，不能被其他文件所用
静态函数被分配在一个一直使用的存储区，直到退出应用程序实例，避免了调用函数的压栈出栈，速度快
*/
static Node* create_bstree_node(Type key, Node* parent, Node* left, Node* right)
{
	Node *p = (Node*)malloc(sizeof(Node));
	assert(p != NULL);
	p->key = key;
	p->left = left;
	p->right = right;
	p->parent = parent;
	return p;
}

/*
插入要维护二叉搜索树的性质
插入的元素一般是不能重复的，如果重复的话有下列解决办法
1.每个结点加一个数据项int count 用来记录某个key值出现的次数，类似于智能指针的功能
2.将元素的分类按< 和 >= 区分。后来的相同元素也按照>的方式处理
*/
/*
传入树的根结点和要插入的结点，返回插入后二叉搜索树的根结点
*/
static Node* bstree_insert(BSTree tree, Node* z)
{
	Node* y = NULL;
	Node* x = tree;
	//查找z的插入位置
	while (NULL != x)
	{
		y = x;  //y记录的是x的父结点
		if (z->key < x->key)
		{
			//z小，x往左边走
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	
	z->parent = y;
	//有可能这个二叉搜索树是空的，则y为NULL
	if (NULL == y)
	{
		tree = z;
	}
	else if (z->key < y->key)
	{
		//z当作y的左孩子
		y->left = z;
	}
	else
	{
		y->right = z;
	}
	return tree;
}

/*
插入结点的外部函数
*/
Node* insert_bstree(BSTree tree, Type key)
{
	//step1.  创建结点
	Node* z = create_bstree_node(key, NULL, NULL, NULL);

	//step2.  插入结点
	return bstree_insert(tree, z);
}

/*
删除结点也要维护二叉搜索树的性质
有4种情况
1)叶结点：父结点指向NULL  free该结点
2)只有左孩子：父结点指向左孩子  free该结点  如果是该结点是根结点的话，将root指针指向左孩子，free该根结点
3)只有右孩子：原理同上
4)左右孩子都有：将该结点的前驱或者后继替换到该位置，free该结点

总感觉有bug
*/
static Node* bstree_delete(BSTree tree, Node* z)
{
	//叶结点
	if (NULL == z->left && NULL == z->right)
	{
		//同时也是根结点
		if (tree == z)
		{
			free(z);
			return NULL;
		}
		//是父结点的左孩子
		if (z == z->parent->left)
		{
			z->parent->left = NULL;
			free(z);
		}
		else
		{
			z->parent->right = NULL;
			free(z);
		}
		return tree;
	}
	
	//该结点只有左孩子
	if (NULL != z->left && NULL == z->right)
	{
		//判断是否是根结点
		if (NULL == z->parent)
		{
			//把根结点指向根的左孩子
			z = z->left;
			free(z->parent);  //释放根结点
			z->parent = NULL;
			return z;
		}
		else
		{
			z->parent->left = z->left;
			z->left->parent = z->parent;
			free(z);
			return tree;
		}
	}

	//该结点只有右孩子
	if (NULL == z->left && NULL != z->right)
	{
		//判断是否是根结点
		if (NULL == z->parent)
		{
			//把根结点指向根的右孩子
			z = z->right;
			free(z->parent);
			z->parent = NULL;
			return z;
		}
		else
		{
			z->parent->right = z->right;
			z->right->parent = z->parent;
			free(z);
			return tree;
		}
	}

	//有左孩子和右孩子
	if (NULL != z->left && NULL != z->right)
	{
		//根该结点的前驱交换。前驱结点的右孩子一定为NULL
		Node* p = bstree_predecessor(z);
		//按照前驱是叶结点还是左子树划分
		if (NULL == p->left)
		{
			//将前驱结点的数据附给目标结点，然后free前驱结点
			z->key = p->key;
			p->parent->right = NULL;
			free(p);
		}
		else
		{
			//将前驱结点的数据附给目标结点，然后将目标结点的left指向前驱结点的left
			z->key = p->key;
			p->left->parent = z;
			z->left = p->left;
			free(p);
		}
		return tree;
	}
}

Node* delete_bstree(BSTree tree, Type key)
{
	Node *z, *node;
	if (NULL != (z = bstree_search(tree, key)))
	{
		tree = bstree_delete(tree, z);
	}
	return tree;
}

/*
前序遍历：根左右
*/
void preorder_bstree(BSTree tree)
{
	if (NULL != tree)
	{
		printf("%d ", tree->key);
		preorder_bstree(tree->left);
		preorder_bstree(tree->right);
	}
}

/*
中序遍历：左根右
*/
void inorder_bstree(BSTree tree)
{
	if (NULL != tree)
	{
		inorder_bstree(tree->left);
		printf("%d ", tree->key);
		inorder_bstree(tree->right);
	}
}

/*
后序遍历：左右根
*/
void postorder_bstree(BSTree tree)
{
	if (NULL != tree)
	{
		postorder_bstree(tree->left);
		postorder_bstree(tree->right);
		printf("%d ", tree->key);
	}
}

/*
查找递归版本
*/
Node* bstree_search(BSTree x, Type key)
{
	if (NULL == x || key == x->key)
	{
		return x;
	}
	if (key < x->key)
	{
		bstree_search(x->left, key);
	}
	else
	{
		bstree_search(x->right, key);
	}
}

/*
查找非递归版本
*/
Node* iterative_bstree_search(BSTree x, Type key)
{
	Node *p = x;
	while (NULL != p && key != p->key)
	{
		if (key < p->key)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
	return p;
}

/*
查找最大值:查找最右的结点
*/
Node* bstree_maximum(BSTree tree)
{
	if (NULL == tree)
	{
		return NULL;
	}
	Node* p = tree;
	while (p->right)
	{
		p = p->right;
	}
	return p;
}

/*
查找最小值：查找最左的结点
*/
Node* bstree_minimum(BSTree tree)
{
	if (NULL == tree)
	{
		return NULL;
	}
	Node* p = tree;
	while (p->left)
	{
		p = p->left;
	}
	return p;
}

/*
找结点x的后继结点。
前驱结点：结点key值小于该结点key值并且值最大的结点
后继结点：结点key值大于该结点key值并且值最小的结点
最简单的思路就是中序遍历的方式寻找结点x的前一个或后一个结点
*/
Node* bstree_successor(Node *x)
{
	//如果x存在右孩子，则x的后继一定在x->right为根结点的最左结点
	if (NULL != x->right)
	{
		return bstree_minimum(x->right);
	}
	//如果x没有右孩子，则x有以下2种可能
	//1.x是左孩子，则x的后继结点就是他的父亲结点
	//2.x是右孩子，则查找第一个比当前结点靠右的祖先结点
	Node* y = x->parent;
	while ((NULL != y) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

/*
找结点x的前驱结点。
*/
Node* bstree_predecessor(Node *x)
{
	//如果x存在左孩子，则x的前驱一定是x->left为根结点的最右结点
	if (NULL != x->left)
	{
		return bstree_maximum(x->left);
	}
	//如果x没有左孩子，则x有以下两种可能
	//1.x是一个右孩子，则x的前驱结点就是他的父节点
	//2.x是一个左孩子，则查找x的最低的父节点，并且该父节点要具有右孩子，这个最低的父节点就是x的前驱结点(查找第一个比当前结点靠左的祖先结点)
	Node* y = x->parent;
	while ((NULL != y) && (x == y->left))  //退出条件，y是NULL，或者x是y的右孩子
	{
		x = y;
		y = y->parent;
	}
	return y;  //这里返回的Y要么是NULL，要么是第一个在左边的父节点（孩子结点在右边）
}


void destroy_bstree(BSTree tree)
{
	if (NULL == tree)
	{
		return;
	}

	if (NULL != tree->left)
	{
		destroy_bstree(tree->left);
	}

	if (NULL != tree->right)
	{
		destroy_bstree(tree->right);
	}
	free(tree);
}

int main()
{
	/*
	Node *root = create_bstree_node(3, NULL, NULL, NULL);
	Node *p1 = create_bstree_node(1, NULL, NULL, NULL);
	Node *p2 = create_bstree_node(5, NULL, NULL, NULL);
	Node *p3 = create_bstree_node(2, NULL, NULL, NULL);
	Node *p4 = create_bstree_node(4, NULL, NULL, NULL);
	Node *p5 = create_bstree_node(6, NULL, NULL, NULL);
	root->left = p1;
	root->right = p2;
	p1->right = p3;
	p1->parent = root;
	p2->left = p4;
	p2->right = p5;
	p2->parent = root;
	p3->parent = p1;
	p4->parent = p2;
	p5->parent = p2;
	preorder_bstree(root);
	printf("\n");
	inorder_bstree(root);
	printf("\n");
	postorder_bstree(root);
	printf("\n");

	//前驱
	Node* p = bstree_predecessor(p1);
	if (p)
	{
		printf("this node have predecessor %d\n", p->key);
	}
	else
	{
		printf("this node dont have predecessor\n");
	}

	p = bstree_predecessor(p4);
	if (p)
	{
		printf("this node have predecessor %d\n", p->key);
	}
	else
	{
		printf("this node dont have predecessor\n");
	}

	p = bstree_predecessor(p5);
	if (p)
	{
		printf("this node have predecessor %d\n", p->key);
	}
	else
	{
		printf("this node dont have predecessor\n");
	}

	//后继
	p = bstree_successor(p1);
	if (p)
	{
		printf("this node have successor %d\n", p->key);
	}
	else
	{
		printf("this node dont have successor\n");
	}

	p = bstree_successor(p3);
	if (p)
	{
		printf("this node have successor %d\n", p->key);
	}
	else
	{
		printf("this node dont have successor\n");
	}

	p = bstree_successor(p5);
	if (p)
	{
		printf("this node have successor %d\n", p->key);
	}
	else
	{
		printf("this node dont have successor\n");
	}
	*/
	int arr[] = { 1,5,4,3,2,6 };
	BSTree root = NULL;
	root->left = (Node*)0x00011111;
	Node* p = bstree_minimum(root);
	for (int i = 0; i < 6; ++i)
	{
		printf("%d ", arr[i]);
		root = insert_bstree(root, arr[i]);
	}

	printf("\n== preorder: ");
	preorder_bstree(root);

	printf("\n== inorder: ");
	inorder_bstree(root);

	printf("\n== postorder: ");
	postorder_bstree(root);
	printf("\n");

	printf("==maxnum: %d\n", bstree_maximum(root)->key);
	printf("==minnum: %d\n", bstree_minimum(root)->key);
	printf("== show tree: \n");
	print_bstree(root, root->key, 0);

	printf("\n== delete node: %d", arr[3]);
	root = delete_bstree(root, arr[3]);

	printf("\n== show tree: \n");
	print_bstree(root, root->key, 0);

	system("pause");
	return 0;
}