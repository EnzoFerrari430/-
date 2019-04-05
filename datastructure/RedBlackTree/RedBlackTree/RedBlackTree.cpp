/*
这里的实现参考的是  数据结构与算法分析 C语言描述 第二版

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
		NullNode->Left = NullNode->Right = NullNode;
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
	T->Left = T->Right = NullNode;
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

//LL旋转 右旋转  返回根结点
RedBlackTree rightSingleRotate(RedBlackTree T)
{
	RedBlackTree k1;
	k1 = T->Left;

	T->Left = k1->Right;
	k1->Right = T;

	return k1;
}

//RR旋转 左旋转
RedBlackTree leftSingleRotate(RedBlackTree T)
{
	RedBlackTree k1;
	k1 = T->Right;

	T->Right = k1->Left;
	k1->Left = T;
	return k1;
}


static Position Rotate(ElementType Item, RedBlackTree Parent)
{
	if (Item < Parent->Element)
		return Parent->Left = Item < Parent->Left->Element ? rightSingleRotate(Parent->Left) : leftSingleRotate(Parent->Left);
	else
		return Parent->Right = Item < Parent->Right->Element ? rightSingleRotate(Parent->Right) : leftSingleRotate(Parent->Right);
}

/*
自顶向下红黑树
需要记录当前结点X 父结点P 祖父结点GP 曾祖父结点GGP
X结点的2个孩子为红结点的时候要进行翻转
翻转之后X和P都为红时要对X P GP进行旋转 曾祖父结点GGP用于连接新的根结点
*/


static Position X, BRO, P, GP, GGP;
static void HandleReorient(ElementType Item, RedBlackTree T)
{
	//颜色翻转
	X->Color = Red;
	X->Left->Color = Black;
	X->Right->Color = Black;
	//自顶向下的红黑树最多发生一次翻转+一次旋转,所以这里再沿当前路径查询一次是否需要旋转即可
	
	//X的父结点也是红色,需要进行旋转
	if (P->Color == Red)
	{
		////如果P已经是根结点
		//if (P == T->Right)
		//{
		//	//不可能，如果P是红色的话，P就不可能是根结点
		//}
		
		//不管是单旋转还是多旋转都是把GP结点涂成红色
		GP->Color = Red;
		/*
		2019-2-20 21:51:11 自己的想法
		if ((X->Element < P->Element) != (X->Element < GP->Element))
		{
			//LR双旋转
			if (X->Element > P->Element)
			{
				P->Right = X->Left;
				X->Left = P;
				GP->Left = P->Right;
				X->Right = GP;
			}
			//RL双旋转
			else
			{
				P->Left = X->Right;
				X->Right = P;
				GP->Right = X->Left;
				X->Left = GP;
			}

			//新的根
			if (X->Element < GGP->Element)
			{
				GGP->Left = X;
			}
			else
			{
				GGP->Right = X;
			}
			X->Color = Black;
		}
		else
		{
			//LL单旋转
			if (X->Element < P->Element)
			{
				GP->Left = P->Right;
				P->Right = GP;
			}
			//RR单旋转
			else
			{
				GP->Right = P->Left;
				P->Left = GP;
			}

			//新的根要和该根的父结点连接
			if (P->Element < GGP->Element)
				GGP->Left = P;
			else
				GGP->Right = P;
			P->Color = Black;
		}
		*/

		//旋转 X P GP
		if ((Item < P->Element) != (Item < GP->Element))
		{
			Rotate(Item, GP);
		}
		X = Rotate(Item, GGP);  //新的根X挂到GGP的下面
		X->Color = Black;  //将新的根涂黑
	}
	
	//把整个树的根结点涂成黑色
	T->Right->Color = Black;
}

RedBlackTree Insert(ElementType Item, RedBlackTree T)
{
	X = P = GP = T;
	NullNode->Element = Item;
	while (X->Element != Item)
	{
		GGP = GP;
		GP = P;
		P = X;
		if (Item < X->Element)
			X = X->Left;
		else
			X = X->Right;

		if (X->Left->Color == Red && X->Right->Color == Red)
		{
			//已经把结点X记录了下来
			HandleReorient(Item, T);
		}
	}
	
	//和已有的数据发生了重复
	if (X != NullNode)
		return NullNode;
	
	//没发生重复
	X = (RedBlackNode*)malloc(sizeof(RedBlackNode));
	assert(NULL != X);
	X->Color = Red;
	X->Element = Item;
	X->Left = X->Right = NullNode;
	if (P->Element < X->Element)
		P->Right = X;
	else
		P->Left = X;
	HandleReorient(Item, T);
	return T;
}

/*
删除结点，也是自顶向下的方式
自顶向下的方式就代表着，需要进行颜色的翻转，一个结点的两个儿子都是红色的就将两个儿子结点的颜色设置成黑色，将父结点设置成红色


自我反思：
	一开始我以为红黑树的性质之一是叶结点必须是红色。所以纠结于删除的时候替换的结点颜色要不要替换过去

书中没有给出源码，参考下面这篇博客
https://blog.csdn.net/javyzheng/article/details/12339463
（X为当前节点，T为X兄弟，P为X父节点）
Step1  将根标记涂成红色

Step2  旋转,目的是自顶向下，将要删除的结点向下滤到叶子结点
	2.1  如果根的两个children都是黑色的
		 a.根颜色变红
		 b.X指向搜索路径上根的children
		 c.这里分3类
			2a1.  X有两个黑儿子，T也有两个黑儿子。反转X P T的颜色
			2a2.  X有两个黑儿子，T的左儿子(L)为红。L T P进行双旋转(之字形),X P变色
			2a3.  X有两个黑儿子，T的右儿子(R)为红。R T P进行单旋转(一字型),X P T R都变色

	2.2  如果根的两个children不都是黑的，X指向根
		a.继续向下
		b.如果新的X是红，继续向下
		c.如果新的X是黑，(必有T为红，P为黑) 单旋转T P  同时T P变色
		d.回到Step2

Step3  最终找到要删除节点，这是一个叶节点，将节点以红节点身份删除

Step4  将根结点涂成黑色
*/

RedBlackTree Delete(ElementType Item, RedBlackTree T)
{
	//第一步先将根标记涂成红色
	T->Color = Red;
	X = T->Right;
	BRO = T->Left;
	GGP = GP = P = T;
	
	while (NullNode != X)
	{
		//Step2
		if (Black == X->Left->Color && Black == X->Right->Color)
		{
			if (Black == BRO->Left->Color && Black == BRO->Right->Color)
			{
				//2a1 X有两个黑儿子，T也有两个黑儿子，反转X P T
				P->Color = Black;
				X->Color = Red;
				if (NullNode != BRO)
					BRO->Color = Red;
			}
			else
				solveStep2A23();

			if (X->Element == Item)
				Item = findItem(Item);
			else
				normalDown(Item);
		}
		else
		{
			//2.2根的两个children不都是黑的，X指向根
			//a.落到下一层
			if (Item != X->Element)
			{

				//GGP = GP;
				//GP = P;
				//P = X;
				//X = X->Left;
				//BRO = P->Right;
				////b.如果新的X是红的，继续向下
				//while (X->Color == Red)
				//{
				//	if (Item < X->Element)
				//	{
				//		GGP = GP;
				//		GP = P;
				//		P = X;
				//		X = X->Left;
				//		BRO = P->Right;
				//	}
				//	else
				//	{
				//		GGP = GP;
				//		GP = P;
				//		P = X;
				//		X = X->Right;
				//		BRO = P->Left;
				//	}
				//}
				
				normalDown(Item);
				//c.如果新的X是黑，(必有T为红，P为黑) 单旋转T P  同时T P变色

			}
			else
				Item = findItem(Item);

			//如果删除完成了，则X会变成NullNode
			if (NullNode == X)
				break;

			if (Black == X->Color)
				solve2B();
			else if (X->Element != Item)
				normalDown(Item);
			else
				Item = findItem(Item);  //如果没有删除结点X就更新替代结点X的结点的Element值,如果删除了结点X的替代结点，结点X将成为NullNode从而退出循环
		}
	}
	T->Color = Black;
	T->Right->Color = Black;

	return T;
}


void solveStep2A23()
{
	//BRO在右边
	if (P->Left == X)
	{
		if (BRO->Left->Color == Red)
		{
			//之字型旋转  X P变色
			
			//X要变红，然后黑高度和原来要保持一致，就只有这种方式
			
			X->Color = Red;
			P->Color = Black;
			P->Right = rightSingleRotate(BRO);
			if (GP->Left == P)
				GP->Left = leftSingleRotate(P);
			else
				GP->Right = leftSingleRotate(P);
		}
		else
		{
			//一字型旋转  P X BRO BRO->Right 都变色
			X->Color = Red;
			P->Color = Black;
			BRO->Color = Red;
			BRO->Right->Color = Black;
			if (GP->Left == P)
				GP->Left = leftSingleRotate(P);
			else
				GP->Right = leftSingleRotate(P);
		}
	}
	//BRO在左边
	else
	{
		if (BRO->Right->Color == Red)
		{
			//之字型
			X->Color = Red;
			P->Color = Black;
			P->Left = leftSingleRotate(BRO);
			if (GP->Left == P)
				GP->Left = rightSingleRotate(P);
			else
				GP->Right = rightSingleRotate(P);
		}
		else
		{
			//一字型旋转  P X BRO BRO->Left变色
			P->Color = Black;
			X->Color = Red;
			BRO->Color = Red;
			BRO->Left->Color = Black;
			if (GP->Left == P)
				GP->Left = rightSingleRotate(P);
			else
				GP->Right = rightSingleRotate(P);
		}
	}
}

void solve2B()
{
	BRO->Color = Black;
	P->Color = Red;

	//这里旋转之后GP没有紧跟在P之后，会导致GGP = GP 和 GP = P中间会插一个结点

	if (P->Left == X)
	{
		if (GP->Left == P)
			GP->Left = leftSingleRotate(P);
		else
			GP->Right = leftSingleRotate(P);
		BRO = P->Left;
	}
	else
	{
		if (GP->Left == P)
			GP->Left = rightSingleRotate(P);
		else
			GP->Right = rightSingleRotate(P);
		BRO = P->Left;
	}
}

//寻找一个替换的结点,在Delete函数里面已经保证X是红色的
ElementType findItem(ElementType Item)
{
	ElementType temp;
	RedBlackTree ToDelete;
	//如果是要寻找的结点，先判断是否是叶子结点，如果不是再通过替换结点删除
	if (X->Left == NullNode && X->Right == NullNode)
	{
		if (X == P->Left)
			P->Left = NullNode;
		else
			P->Right = NullNode;
		free(X);
		X = NullNode;
		temp =  Item;
	}
	else
	{
		//不是叶子结点
		if (X->Right != NullNode)
		{
			ToDelete = minium_redblacktree(X->Right);
			//值替换
			X->Element = ToDelete->Element;
			temp = ToDelete->Element;
			if (Red == ToDelete->Color)
			{
				//直接删除该结点
				X->Right = DeleteNode(ToDelete, X->Right);
				X = NullNode;  //!!!!!为什么要加这个？
			}
			else
			{
				//A2中：往右前进,此时新的X，一定是黑色，兄弟BRO也一定是黑色，此时就回到了step2
				//B2中：右前进,此时新的X，可能是红色也可能是黑色，如果是红色的话，一定不是ToDelete节点，因为在上面已经排除过了
				GP = P;
				P = X;
				BRO = P->Left;
				X = X->Right;
			}
		}
		else
		{
			ToDelete = maximum_redblacktree(X->Left);
			//值替换
			X->Element = ToDelete->Element;
			temp = ToDelete->Element;
			if (Red == ToDelete->Color)
			{
				//直接删除该结点
				X->Left = DeleteNode(ToDelete, X->Right);
				X = NullNode;  //!!!!!为什么要加这个？
			}
			else
			{
				//A2中：往左前进,此时新的X，一定是黑色，兄弟BRO也一定是黑色，此时就回到了step2
				//B2中：左前进,此时新的X，可能是红色也可能是黑色，如果是红色的话，一定不是ToDelete节点，因为在上面已经排除过了
				GP = P;
				P = X;
				BRO = P->Right;
				X = X->Left;
			}
		}
	}
	return temp;
}

void normalDown(ElementType Item)
{
	if (Item < X->Element)
	{
		GGP = GP;
		GP = P;
		P = X;
		X = X->Left;
		BRO = P->Right;
	}
	else
	{
		GGP = GP;
		GP = P;
		P = X;
		X = X->Right;
		BRO = P->Left;
	}
}

//删除只有一个孩子，或者没有孩子的结点
RedBlackTree DeleteNode(RedBlackTree target, RedBlackTree T)
{
	RedBlackTree origin = T;
	RedBlackTree Parent = NullNode;
	while (T != target)
	{
		Parent = T;
		if (target->Element < T->Element)
			T = T->Left;
		else
			T = T->Right;
	}

	if (T == origin)
	{
		RedBlackTree temp;
		if (T->Right != NullNode)
			temp = T->Right;
		else
			temp = T->Left;
		free(T);
		return temp;
	}

	if (Parent->Right == T)
	{
		if (T->Right != NullNode)
			P->Right = T->Right;
		else
			Parent->Right = T->Left;
	}
	else
	{
		if (T->Right != NullNode)
			Parent->Left = T->Right;
		else
			Parent->Left = T->Left;
	}
	free(T);
	return origin;
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