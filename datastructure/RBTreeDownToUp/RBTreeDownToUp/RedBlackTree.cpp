/*
参考文章
http://www.cnblogs.com/skywang12345/p/3245399.html

*/
#include "RedBlackTree.h"

Position NullNode = NULL;

RedBlackTree Initialize(void)
{
	/*
		这里使用2个标记结点：一个是为根，一个是NullNode
		NullNode的作用是像在伸展树中那样指示一个NULL指针
		根标记将存储关键字NegInfinity和一个指向真正的根的右指针
	*/
	RedBlackTree T;
	if (NULL == NullNode)
	{
		NullNode = (RedBlackNode*)malloc(sizeof(RedBlackNode));
		assert(NULL != NullNode);
		NullNode->Left = NullNode->Right = NullNode->Parent = NullNode;
		NullNode->Color = Black;
		NullNode->Element = Infinity;
	}

	//创建根标记
	T = (RedBlackNode*)malloc(sizeof(RedBlackNode));
	if (NULL == T)
	{
		assert(NULL != T);
	}
	T->Element = NegInfinity;
	T->Left = T->Right = T->Parent = NullNode;
	T->Color = Black;
	return T;
}

void preorder_redblacktree(RedBlackTree T)
{
	if (T->Right != NullNode)
	{
		printf("%d ", T->Right->Element);
		preorder_redblacktree(T->Right->Left);
		preorder_redblacktree(T->Right->Right);
	}
}

void inorder_redblacktree(RedBlackTree T)
{
	if (T->Right != NullNode)
	{
		inorder_redblacktree(T->Right->Left);
		printf("%d ", T->Right->Element);
		inorder_redblacktree(T->Right->Right);
	}
}

void postorder_redblacktree(RedBlackTree T)
{
	if (T->Right != NullNode)
	{
		postorder_redblacktree(T->Right->Left);
		postorder_redblacktree(T->Right->Right);
		printf("%d ", T->Right->Element);
	}
}

static void rbtree_insert_fixup(Position X, RedBlackTree T)
{
	Position Y;
	while (Red == X->Parent->Color)
	{
		if (X->Parent == X->Parent->Parent->Left)
		{
			Y = X->Parent->Parent->Right;
			if (Red == Y->Color)
			{
				X->Parent->Color = Black;
				Y->Color = Black;
				X->Parent->Parent->Color = Red;
				X = X->Parent->Parent;
			}
			else
			{
				if (X == X->Parent->Right)
				{
					X = X->Parent;
					left_rotate(X, T);
				}

				if (X == X->Parent->Left)
				{
					X->Parent->Color = Black;
					X->Parent->Parent->Color = Red;
					right_rotate(X->Parent->Parent, T);
				}
			}
		}
		else
		{
			Y = X->Parent->Parent->Left;
			if (Red == Y->Color)
			{
				X->Parent->Color = Black;
				Y->Color = Black;
				X->Parent->Parent->Color = Red;
				X = X->Parent->Parent;
			}
			else
			{
				if (X == X->Parent->Left)
				{
					X = X->Parent;
					right_rotate(X, T);
				}

				if (X == X->Parent->Right)
				{
					X->Parent->Color = Black;
					X->Parent->Parent->Color = Red;
					left_rotate(X->Parent->Parent, T);
				}
			}

		}
	}
	T->Right->Color = Black;
}

/*
RB-INSERT(T, z)
 y ← nil[T]                        // 新建节点“y”，将y设为空节点。
 x ← root[T]                       // 设“红黑树T”的根节点为“x”
 while x ≠ nil[T]                  // 找出要插入的节点“z”在二叉树T中的位置“y”
	 do y ← x
		if key[z] < key[x]
		   then x ← left[x]
		   else x ← right[x]
 p[z] ← y                          // 设置 “z的父亲” 为 “y”
 if y = nil[T]
	then root[T] ← z               // 情况1：若y是空节点，则将z设为根
	else if key[z] < key[y]
			then left[y] ← z       // 情况2：若“z所包含的值” < “y所包含的值”，则将z设为“y的左孩子”
			else right[y] ← z      // 情况3：(“z所包含的值” >= “y所包含的值”)将z设为“y的右孩子”
 left[z] ← nil[T]                  // z的左孩子设为空
 right[z] ← nil[T]                 // z的右孩子设为空。至此，已经完成将“节点z插入到二叉树”中了。
 color[z] ← RED                    // 将z着色为“红色”
 RB-INSERT-FIXUP(T, z)             // 通过RB-INSERT-FIXUP对红黑树的节点进行颜色修改以及旋转，让树T仍然是一颗红黑树



 RB-INSERT-FIXUP(T, z)
while color[p[z]] = RED                                                  // 若“当前节点(z)的父节点是红色”，则进行以下处理。
	do if p[z] = left[p[p[z]]]                                           // 若“z的父节点”是“z的祖父节点的左孩子”，则进行以下处理。
		  then y ← right[p[p[z]]]                                        // 将y设置为“z的叔叔节点(z的祖父节点的右孩子)”
			   if color[y] = RED                                         // Case 1条件：叔叔是红色
				  then color[p[z]] ← BLACK                    ▹ Case 1   //  (01) 将“父节点”设为黑色。
					   color[y] ← BLACK                       ▹ Case 1   //  (02) 将“叔叔节点”设为黑色。
					   color[p[p[z]]] ← RED                   ▹ Case 1   //  (03) 将“祖父节点”设为“红色”。
					   z ← p[p[z]]                            ▹ Case 1   //  (04) 将“祖父节点”设为“当前节点”(红色节点)
				  else if z = right[p[z]]                                // Case 2条件：叔叔是黑色，且当前节点是右孩子
						  then z ← p[z]                       ▹ Case 2   //  (01) 将“父节点”作为“新的当前节点”。
							   LEFT-ROTATE(T, z)              ▹ Case 2   //  (02) 以“新的当前节点”为支点进行左旋。
						  color[p[z]] ← BLACK                 ▹ Case 3   // Case 3条件：叔叔是黑色，且当前节点是左孩子。(01) 将“父节点”设为“黑色”。
						  color[p[p[z]]] ← RED                ▹ Case 3   //  (02) 将“祖父节点”设为“红色”。
						  RIGHT-ROTATE(T, p[p[z]])            ▹ Case 3   //  (03) 以“祖父节点”为支点进行右旋。
	   else (same as then clause with "right" and "left" exchanged)      // 若“z的父节点”是“z的祖父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
color[root[T]] ← BLACK

*/

//自顶向下插入，自底向上调整
RedBlackTree Insert(ElementType Item, RedBlackTree T)
{
	Position Y = NullNode;
	Position X = T;
	while (X != NullNode)
	{
		Y = X;
		if (Item < X->Element)
		{
			X = X->Left;
		}
		else if (Item > X->Element)
		{
			X = X->Right;
		}
		else
			return NullNode;  //发生了重复，不插入
	}

	X = (RedBlackNode*)malloc(sizeof(RedBlackNode));
	X->Color = Red;
	X->Element = Item;
	X->Left = NullNode;
	X->Right = NullNode;
	X->Parent = Y;
	if (X->Element < Y->Element)
		Y->Left = X;
	else
		Y->Right = X;
	rbtree_insert_fixup(X, T);

	return T;
}

void left_rotate(Position X, RedBlackTree T)
{
	Position Y = X->Right;
	X->Right = Y->Left;
	Y->Left->Parent = X;

	Y->Parent = X->Parent;
	if (X->Parent == T)
	{
		T->Right = Y;
	}
	else if(X == X->Parent->Left)
	{
		X->Parent->Left = Y;
	}
	else
	{
		X->Parent->Right = Y;
	}

	Y->Left = X;
	X->Parent = Y;
}

void right_rotate(Position X, RedBlackTree T)
{
	Position Y = X->Left;
	X->Left = Y->Right;
	Y->Right->Parent = X;

	Y->Parent = X->Parent;
	if (X->Parent == T)
	{
		T->Right = Y;
	}
	else if (X == X->Parent->Left)
	{
		X->Parent->Left = Y;
	}
	else
	{
		X->Parent->Right = Y;
	}

	Y->Right = X;
	X->Parent = Y;
}


/*
删除结点
第一步：将红黑树当做一棵二叉查找树，将结点删除
	这和"删除常规二叉查找树中删除结点的方法是一样的" 分成3种情况
	1.被删除结点没有儿子，那么直接将该结点删除就行
	2.被删除结点只有一个儿子，那么直接将该结点删除，并用该结点的唯一子结点顶替它的位置
	3.被删除的结点有两个儿子。那么，先找出它的后继结点；然后把"它的后继结点的内容"复制给"该结点的内容"；之后，删除它的后继结点。
		如果要被删除的结点有两个非空子结点的情况下，它的后继结点不可能是双子非空，所以它的后继结点要么只有一个儿子，要么没有儿子，就可以按照情况1和2对应处理

第二步：通过旋转和重新着色等一系列来修正该树，使之重新成为一个红黑树


RB-DELETE(T, z)
if left[z] = nil[T] or right[z] = nil[T]
   then y ← z                                  // 若“z的左孩子” 或 “z的右孩子”为空，则将“z”赋值给 “y”；
   else y ← TREE-SUCCESSOR(z)                  // 否则，将“z的后继节点”赋值给 “y”。
if left[y] ≠ nil[T]
   then x ← left[y]                            // 若“y的左孩子” 不为空，则将“y的左孩子” 赋值给 “x”；
   else x ← right[y]                           // 否则，“y的右孩子” 赋值给 “x”。
p[x] ← p[y]                                    // 将“y的父节点” 设置为 “x的父节点”
if p[y] = nil[T]
   then root[T] ← x                            // 情况1：若“y的父节点” 为空，则设置“x” 为 “根节点”。
   else if y = left[p[y]]
		   then left[p[y]] ← x                 // 情况2：若“y是它父节点的左孩子”，则设置“x” 为 “y的父节点的左孩子”
		   else right[p[y]] ← x                // 情况3：若“y是它父节点的右孩子”，则设置“x” 为 “y的父节点的右孩子”
if y ≠ z
   then key[z] ← key[y]                        // 若“y的值” 赋值给 “z”。注意：这里只拷贝z的值给y，而没有拷贝z的颜色！！！
		copy y's satellite data into z
if color[y] = BLACK
   then RB-DELETE-FIXUP(T, x)                  // 若“y为黑节点”，则调用
return y



RB-DELETE-FIXUP(T, x)
while x ≠ root[T] and color[x] = BLACK
	do if x = left[p[x]]
		  then w ← right[p[x]]                                             // 若 “x”是“它父节点的左孩子”，则设置 “w”为“x的叔叔”(即x为它父节点的右孩子)
			   if color[w] = RED                                           // Case 1: x是“黑+黑”节点，x的兄弟节点是红色。(此时x的父节点和x的兄弟节点的子节点都是黑节点)。
				  then color[w] ← BLACK                        ▹  Case 1   //   (01) 将x的兄弟节点设为“黑色”。
					   color[p[x]] ← RED                       ▹  Case 1   //   (02) 将x的父节点设为“红色”。
					   LEFT-ROTATE(T, p[x])                    ▹  Case 1   //   (03) 对x的父节点进行左旋。
					   w ← right[p[x]]                         ▹  Case 1   //   (04) 左旋后，重新设置x的兄弟节点。
			   if color[left[w]] = BLACK and color[right[w]] = BLACK       // Case 2: x是“黑+黑”节点，x的兄弟节点是黑色，x的兄弟节点的两个孩子都是黑色。
				  then color[w] ← RED                          ▹  Case 2   //   (01) 将x的兄弟节点设为“红色”。
					   x ←  p[x]                               ▹  Case 2   //   (02) 设置“x的父节点”为“新的x节点”。
				  else if color[right[w]] = BLACK                          // Case 3: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的左孩子是红色，右孩子是黑色的。
						  then color[left[w]] ← BLACK          ▹  Case 3   //   (01) 将x兄弟节点的左孩子设为“黑色”。
							   color[w] ← RED                  ▹  Case 3   //   (02) 将x兄弟节点设为“红色”。
							   RIGHT-ROTATE(T, w)              ▹  Case 3   //   (03) 对x的兄弟节点进行右旋。
							   w ← right[p[x]]                 ▹  Case 3   //   (04) 右旋后，重新设置x的兄弟节点。
						color[w] ← color[p[x]]                 ▹  Case 4   // Case 4: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的右孩子是红色的。(01) 将x父节点颜色 赋值给 x的兄弟节点。
						color[p[x]] ← BLACK                    ▹  Case 4   //   (02) 将x父节点设为“黑色”。
						color[right[w]] ← BLACK                ▹  Case 4   //   (03) 将x兄弟节点的右子节设为“黑色”。
						LEFT-ROTATE(T, p[x])                   ▹  Case 4   //   (04) 对x的父节点进行左旋。
						x ← root[T]                            ▹  Case 4   //   (05) 设置“x”为“根节点”。
	   else (same as then clause with "right" and "left" exchanged)        // 若 “x”是“它父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
color[x] ← BLACK


*/

static void rbtree_delete_fixup(Position child, Position parent, RedBlackTree T)
{

	Position w;

	while (Black == child->Color && child != T->Right)
	{
		//child是左孩子
		if (parent->Left == child)
		{
			w = parent->Right;
			if (Red == w->Color)
			{
				//case1  当前结点是黑+黑，且兄弟结点是红色
				parent->Color = Red;
				w->Color = Black;
				left_rotate(parent, T);
				w = parent->Right;
			}

			if (Black == w->Left->Color && Black == w->Right->Color)
			{
				//case2  当前结点是黑+黑，且兄弟结点是黑色且兄弟结点的两个儿子都是黑色
				w->Color = Red;
				child = parent;
				parent = parent->Parent;
			}
			else
			{
				if (Black == w->Right->Color)
				{
					//case3  当前结点是黑+黑，且兄弟结点是黑色且兄弟结点的左儿子是红色，右儿子是黑色
					w->Left->Color = Black;
					w->Color = Red;
					right_rotate(w, T);
					w = parent->Right;
				}

				//case4  当前结点是黑+黑，兄弟结点是黑色，兄弟结点的右孩子是红色，左孩子任意颜色
				w->Color = parent->Color;
				parent->Color = Black;
				w->Right->Color = Black;
				left_rotate(parent, T);
				child = T->Right;
			}

		}
		else
		{
			//child是右孩子
			w = parent->Left;
			if (Red == w->Color)
			{
				//case1  当前结点是黑+黑，兄弟结点是红色
				//目标转换成情况2 3 4
				//方案  父结点变红，兄弟结点变黑  对父结点右旋
				parent->Color = Red;
				w->Color = Black;
				right_rotate(parent, T);
				w = parent->Left;
			}

			if (Black == w->Left->Color && Black == w->Right->Color)
			{
				//case2  当前结点是黑+黑，兄弟结点是黑色而且兄弟结点的两个儿子结点也都是黑色
				//目标向上过滤，直到出现下面三种情况
				//				1.当前结点是红+黑
				//				2.当前结点是根结点
				//				3.当前结点的兄弟结点有颜色为红的结点，按3 4的情况调整
				//方案，将当前结点的兄弟结点设为红色，设置当前结点的父结点为新的当前结点
				w->Color = Red;
				child = parent;
				parent = parent->Parent;
			}
			else
			{
				if (Black == w->Left->Color)
				{
					//case3  当前结点是黑+黑，兄弟结点是黑色而且兄弟的右孩子是红色，左孩子是黑色
					//目标  将情况3转换成情况4
					//方案  将兄弟结点的右孩子设为黑色，兄弟结点设为红色，对兄弟结点进行左旋，左旋之后重新设置当前结点的兄弟结点
					w->Color = Red;
					w->Right->Color = Black;
					left_rotate(w, T);
					w = parent->Left;
				}

				//case4  当前结点是黑+黑，兄弟结点是黑色而且兄弟结点的左孩子是红色，右孩子颜色不用管
				//目标  完成调整
				//方案  兄弟结点的颜色设为父结点的颜色，父结点的颜色设为黑色，兄弟结点的左孩子设为黑色，对父结点进行右旋，设置当前结点为根节点
				//理由  兄弟结点设置父结点的颜色，父结点颜色设为黑色，这样就可以在当前结点这条路上补上一个黑色的结点，使黑高度一致
				w->Color = parent->Color;
				parent->Color = Black;
				w->Left->Color = Black;
				right_rotate(parent, T);
				child = T->Right;
			}
		}
	}
	if (NullNode != child)
		child->Color = Black;

	return;
}

//在Delete函数中先将Z结点踢出去，然后再在delete_fixup中调整
RedBlackTree Delete(ElementType Item, RedBlackTree T)
{
	Position Y = NullNode, X = NullNode, parent = NullNode;
	Position Z = T;
	int color;
	while (Z != NullNode)
	{
		//Y = T;
		if (Item < Z->Element)
		{
			Z = Z->Left;
		}
		else if (Item > Z->Element)
		{
			Z = Z->Right;
		}
		else
			break;
	}
	if (NullNode == Z)
	{
		return NullNode;  //没有找到值为Item的结点,不删除结点,直接返回
	}

	if (NullNode != Z->Left || NullNode != Z->Right)
	{
		//有2个儿子的情况,它的后继结点不可能有2个儿子
		Y = Tree_Successor(Z);

		if (Z->Parent != T)
		{
			if (Z == Z->Parent->Left)
			{
				Z->Parent->Left = Y;
			}
			else
			{
				Z->Parent->Right = Y;
			}

		}
		else
			T->Right = Y;

		//因为Y是Z的后继结点，所以Y不可能存在左孩子
		X = Y->Right;
		parent = Y->Parent;
		color = Y->Color;

		//"被删除的结点"是"它的后继结点的父结点"
		if (parent == Z)
		{
			parent = Y;
		}
		else
		{
			//能进来这里表示Y一定在Z->Right的左边,Y是parent的左孩子
			if (X != NullNode)
			{
				X->Parent = parent;
			}
			parent->Left = X;  //把Y的右孩子挂到parent的左子树上

			Y->Right = Z->Right;
			Z->Right->Parent = Y;
		}

		Y->Parent = Z->Parent;
		Y->Color = Z->Color;  //颜色覆盖,如果原来Y的颜色是红色就不需要调整
		Y->Left = Z->Left;
		Z->Left->Parent = Y;

		if (Black == color)  //Y原来是黑色的,这里就少了一个黑色结点，需要进行调整
		{
			rbtree_delete_fixup(X, parent, T);
		}
		free(Z);
		return T;


	}

	//只有一个儿子或没有儿子
	Y = Z;
	if (NullNode != Y->Left)
	{
		X = Y->Left;
	}
	else
	{
		X = Y->Right;
	}

	parent = Y->Parent;
	color = Y->Color;

	if (NullNode != X)
	{
		X->Parent = parent;
	}

	//Z结点不是根结点
	if (parent != T)
	{
		if (parent->Left == Y)
		{
			parent->Left = X;
		}
		else
		{
			parent->Right = X;
		}
	}
	else
	{
		T->Right = X;
	}

	if (Black == color)
	{
		rbtree_delete_fixup(X, parent, T);
	}

	free(Z);
	return T;
}

RedBlackTree Tree_Successor(RedBlackTree T)
{
	if (NullNode != T->Right)
	{
		return minium_redblacktree(T->Right);  //如果T的右孩子不为空，则T的后继结点就是T的右孩子为根的最小结点
	}

	//如果T没有右孩子，则有一下两种可能
	//1.T是一个左孩子，则T的后继结点为它的父结点
	//2.T是一个右孩子，则查找T的最低的父结点，并且该父结点要有左孩子,这个最低的父结点就是T的后继结点,第一个比当前结点靠右的祖先结点
	Position Y = T->Parent;
	while ((NullNode != Y) && (T == Y->Right))
	{
		T = Y;
		Y = Y->Parent;
	}
	return Y;
}


void print_redblacktree(RedBlackTree T, ElementType element, int direct)
{
	if (NullNode != T)
	{
		if (0 == direct)
		{
			printf("%d is the root and the color is %s\n", element, T->Color == Red ? "red" : "black");
		}
		else
			printf("%d is the %d's %s and the color is %s\n", T->Element, element, direct == -1 ? "leftchild" : "rightchild", T->Color == Red ? "red" : "black");
		print_redblacktree(T->Left, T->Element, -1);
		print_redblacktree(T->Right, T->Element, 1);
	}
}


/*
查找最小结点:返回T为根结点的红黑树的最小结点
该结点必然在T为根结点的最左边
*/
Position minium_redblacktree(RedBlackTree T)
{
	while (T->Left != NullNode)
	{
		T = T->Left;
	}
	return T;
}

/*
查找最大结点:返回T为根结点的红黑树的最大结点
该结点必然在T为根结点的最右边
*/
Position maximum_redblacktree(RedBlackTree T)
{
	while (T->Right != NullNode)
	{
		T = T->Right;
	}
	return T;
}

//销毁红黑树
void destroy_RedBlackTree(RedBlackTree T)
{
	if (NullNode != T)
	{
		destroy_RedBlackTree(T->Left);
		destroy_RedBlackTree(T->Right);
		free(T);
	}
}