#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef int Type;

typedef struct AVLTreeNode
{
	Type key;		//关键字
	int height;		//树的高度
	struct AVLTreeNode *left;	//左孩子
	struct AVLTreeNode *right;	//右孩子
}Node,*AVLTree;

//获取树的高度
int avltree_height(AVLTree tree);

//前序遍历AVL树
void preorder_avltree(AVLTree tree);
//中序遍历AVL树
void inorder_avltree(AVLTree tree);
//后序遍历AVL树
void postorder_avltree(AVLTree tree);

//打印AVL树
void print_avltree(AVLTree tree, Type key, int direction);

//递归实现查找AVL树x中键值为key的结点
Node* avltree_search(AVLTree x, Type key);
//非递归实现查找AVL树x中键值为key的结点
Node* iterative_avltree_search(AVLTree x, Type key);

//查找最小结点：返回tree为根结点的AVL树的最小结点
Node* avltree_minimum(AVLTree tree);
//查找最大结点：返回tree为根结点的AVL树的最大结点
Node* avltree_maximum(AVLTree tree);

//找结点x的后继结点。
Node* avltree_successor(Node *x);
//找结点x的前驱结点
Node* avltree_predecessor(Node *x);

//将结点插入到AVL树中，并返回根结点
Node* avltree_insert(AVLTree tree, Type key);

//删除结点(key是结点的值)，返回根结点
Node* avltree_delete(AVLTree tree, Type key);

//重新调整树的高度信息
void avltree_fixheight(AVLTree tree);

//销毁AVL树
void destroy_avltree(AVLTree tree);
#endif