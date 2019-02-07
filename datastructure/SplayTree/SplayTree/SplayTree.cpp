#include "SplayTree.h"
#include <stdlib.h>
/*
伸展树属于二叉排序树
1.所以它具有和二叉排序树一样是性质
2.除了拥有二叉排序树的性质之外，伸展树还具有一个特点是：当某个结点被访问时，伸展树会通过旋转使该结点成为树根
	这样能使下次要访问该结点时，能够迅速的访问到该结点

伸展树的旋转：
	1.插入
		插入结点z到tree中，旋转z直至树根
	2.删除
		删除tree中的结点X:
			我们可以通过访问要被删除的结点，实行删除操作。
			这种操作会将结点上推至根处。
			如果删除该结点，则得到两棵子树
	3.查询
		将tree中查询到的结点z旋转到树根
*/

/*
伸展的情况分类:
	1.结点X的父结点P就是树根
		这种情况下只需要旋转X和树根
	2.结点X有父结点P和祖父结点G
		这种情况下分为有之字形和一字形:
			之字形:类似于AVL树的LR和RL情况
				这种情况的旋转方式也和AVL树的旋转方式一样

			一字形:类似于AVL树的LL和RR情况
				这种情况就和AVL的旋转方式不一样了
				例子:
						3				1
					   /				 \
					  2		 展开成	      2
					 /				       \
					1						3
				这样的好处是  展开操作不仅将访问的结点移动到了根结点处  而且还有把访问路径上的大部分结点的深度大致减少了一半
				某些浅的结点向下推后两个层次
*/


/*
前序遍历伸展树  根左右
*/
void preorder_splaytree(SplayTree tree)
{
	printf("%d ",tree->key);
	if (tree->left)
	{
		preorder_splaytree(tree->left);
	}
	if (tree->right)
	{
		preorder_splaytree(tree->right);
	}
}


/*
中序遍历伸展树  左右根
*/
void inorder_splaytree(SplayTree tree)
{
	if (tree->left)
	{
		inorder_splaytree(tree->left);
	}
	printf("%d ", tree->key);
	if (tree->right)
	{
		inorder_splaytree(tree->right);
	}
}


/*
后序遍历伸展树  左右根
*/
void postorder_splaytree(SplayTree tree)
{
	if (tree->left)
	{
		postorder_splaytree(tree->left);
	}
	if (tree->right)
	{
		postorder_splaytree(tree->right);
	}
	printf("%d ", tree->key);
}


/*
伸展t结点至树根
怎么找到t的祖父结点?
*/
static Node* splaytree_splay(SplayTree tree, Node* t,Node *g)
{

	return tree;
}



/*
递归实现查找伸展树x中键值为key的结点，
找到之后要将该结点提升至树根
*/
Node* splaytree_search(SplayTree x, Type key)
{
	if (NULL == x)
	{
		return NULL;
	}
	else if (key == x->key)
	{
		return x;
	}
	if (key < x->key)
	{
		return splaytree_search(x->left,key);
	}
	else
	{
		return splaytree_search(x->right, key);
	}
}


/*
非递归实现查找伸展树x中键值为key的结点
*/
Node* iterative_splaytree_search(SplayTree x, Type key)
{
	Node *p = x;
	while (p && p->key != key)
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
查找最小结点:返回tree为根结点的伸展树的最小结点
该结点必定在最左端
*/
Node* splaytree_minimum(SplayTree tree)
{
	Node* p = tree;
	while (p->left)
	{
		p = p->left;
	}
	return p;
}


/*
查找最大结点:返回tree为根结点的伸展树的最大结点
该结点必定在最右端
*/
Node* splaytree_maximum(SplayTree tree)
{
	Node* p = tree;
	while (p->right)
	{
		p = p->right;
	}
	return p;
}


/*
将结点插入到伸展树中，并返回根结点
插入不用在该结点上进行旋转
因为伸展树不太需要在插入的时候就进行旋转
访问的时候旋转就可以了
*/
Node* insert_splaytree(SplayTree tree, Type key)
{
	if (NULL == tree)
	{
		tree = (Node*)malloc(sizeof(Node));
		tree->key = key;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	else if (key == tree->key)
	{
		//如果相等就不插入,直接返回
		return tree;
	}
	else if (key < tree->key)
	{
		tree->left = insert_splaytree(tree->left, key);
	}
	else
	{
		tree->right = insert_splaytree(tree->right, key);
	}
	return tree;
}

/*
好好理解N的作用:
	结点N用来表示tree结点的左子树和右子树的指向

	
	这个谁想的出来啊

处理的情况
	1.伸展树中存在键值为key的结点
		将键值为key的结点旋转为根结点
	2.伸展树中不存在键值为key的
*/
Node* splaytree_splay(SplayTree tree, Type key)
{
	Node N, *l, *r, *c;
	if(tree == NULL)
		return tree;

	N.left = N.right = NULL;
	l = r = &N;

	for (;;)
	{
		if (key < tree->key)
		{
			if (tree->left == NULL)
			{
				break;
				//return NULL;
			}

			//一字形,LL  只要差2级就开始旋转
			//右旋
			if (key < tree->left->key)
			{
				c = tree->left;
				tree->left = c->right;
				c->right = tree;
				tree = c;
				if (tree->left == NULL)
					break;
			}

			//右链接
			r->left = tree;
			r = tree;
			tree = tree->left;

		}
		else if (key > tree->key)
		{
			if (tree->right == NULL)
				break;

			if (key > tree->right->key)
			{
				c = tree->right;
				tree->right = c->left;
				c->left = tree;
				tree = c;
				if (tree->right == NULL)
				{
					break;
				}
			}

			//左链接
			l->right = tree;
			l = tree;
			tree = tree->right;
		}
		else
		{
			break;
		}
	}

	//组合
	l->right = tree->left;
	r->left = tree->right;
	tree->left = N.right;
	tree->right = N.left;
	return tree;
}


/*
打印伸展树
*/
void print_splaytree(SplayTree tree, Type key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)
		{
			printf("%2d is root\n", tree->key);
		}
		else
		{
			if (direction == 1)
			{
				printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");
			}
			else if (direction == -1)
			{
				printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");
			}
		}
		
		print_splaytree(tree->left, tree->key, -1);
		print_splaytree(tree->right, tree->key, 1);

	}

}


/*
访问值为key的结点，
如果没有该结点返回NULL
如果有该结点将该结点旋转到树根
*/
Node* access_splaytree(SplayTree tree, Type key)
{
	if (NULL == tree)
	{
		return NULL;
	}

	if (NULL == iterative_splaytree_search(tree, key))
	{
		return tree;
	}
	else
	{
		tree = splaytree_splay(tree, key);
		return tree;
	}
}


/*
删除结点(key为结点的值),并返回根结点
将该要删除的结点推向根结点，然后删除该根结点
然后再将该左子树的最大子结点推向左子树的根
此时该左子树将没有右孩子，就可以将右子树附着到该左子树上
*/
Node* delete_splaytree(SplayTree tree, Type key)
{
	Node* x;
	if (NULL == tree)
	{
		return NULL;
	}

	if (NULL == iterative_splaytree_search(tree, key))
	{
		return tree;
	}
	else
	{
		tree = splaytree_splay(tree, key);
		if (tree->left != NULL)
		{
			//splaytree_splay直接旋转了值为key的前驱结点
			x = splaytree_splay(tree->left, key);
			x->right = tree->right;
		}
		else
			x = tree->right;
	}
	free(tree);
	return x;
}

/*
销毁伸展树
*/
void destroy_splaytree(SplayTree tree)
{
	if (NULL == tree)
	{
		return;
	}

	if (NULL != tree->left)
	{
		destroy_splaytree(tree->left);
	}
	if (NULL != tree->right)
	{
		destroy_splaytree(tree->right);
	}
	free(tree);
}