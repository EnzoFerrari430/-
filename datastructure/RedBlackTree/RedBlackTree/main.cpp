/*
树的附加说明
内结点：该结点存在孩子，则该结点成为内结点。叶子结点不是内结点
叶子结点：真正的叶子结点是指向null的结点，这些指向null的结点才是真正的叶子结点，也称外部结点


红黑树是具有下列着色性质的二叉查找树:
1.每一个结点或者着成红色，或者着成黑色
2.根是黑色的
3.如果一个结点是红色的，那么它的子结点必须是黑色的
4.从一个结点到一个NULL指针的每一条路径必须包含相同数目的黑色结点
5.每个叶子结点(NULL)是黑色(附加性质，这里的叶子结点是指为空(NULL)的叶子结点)


红黑树的定理：
1.一棵含有n个结点的红黑树的高度至少为2log(n+1)  (有待证明)



红黑树的基本操作

用于完成冲突情况的基本操作是颜色的改变和树的旋转

1.插入：
和通常一样，困难在于将一个新项，插入到树中。通常会把新项作为树叶放到树中。
如果我们把该项涂成黑色，那么我们肯定违反了性质4，因为这样会产生一条更长的黑结点的路径。所以这新的一项必须涂成红色
如果这新项的父结点是黑色的，则我们的插入完成，如果它的父结点是红色的，那么我们会得到连续的红色结点，这样违反了性质3
在这种情况下，我们必须调整该树以确保条件3满足(且不引起条件4被破坏)

1.1
	如果父结点是黑色的，那么将该结点插入到父结点下，然后将该结点涂成红色

1.2
	如果父结点是红色
	1.2.1
	如果父结点的兄弟结点是黑色的，对该新结点、父结点、祖父结点按照伸展树的方式进行旋转
	旋转的方式有"一"字形和"之"字形。然后再对颜色作出相应的调整，使其遵循红黑树的性质
	在编写程序的时候，我们必须记录父结点、祖父结点和曾祖父结点，其中曾祖父结点用来重新进行连接
	旋转后子树的新根被涂成黑色，因此即使原来曾祖父是红的，我们也排除了两个相邻红结点的可能性

	1.2.2
	如果父结点的兄弟结点是红色的，则继续按照伸展树的方式尽心旋转，但是颜色的转换要和1.2.1有所不同
	原来结构如下，颜色是G(black) P(red) S(red) X(red)
	G->left = P;
	G->right = S;
	P->left = X;
	P->right = B;

	还是按照伸展树的方式进行旋转,旋转后的结构如下 颜色是P(red) X(black) G(black) S(red)
	P->left = X;
	P->right = G;
	G->left = P->right;
	G->right = S
	这里根结点P是红色，所以该红色要往上虑，直到符合红黑树的条件

	可以看到这里上虑的过程比较繁琐，这里可以考虑自顶向下的红黑树
	自顶向下的红黑树:
		在向下找寻插入位置的时候，当我们看到一个结点X有两个红儿子的时候，我们就让X成为红的而让它的两个儿子是黑色的。
		只有当X的父结点P也是红的时候，这种翻转破坏了将破坏红黑的法则。我们使用1.2.1中的适当的旋转.
		不可能存在X的父结点P和P的兄弟结点同时为红的情况，因为在向下的过程中，该情况和结点X的情况一致，会先发生翻转.
		在一次插入过程中，在沿当前路径,最多发生一次翻转，一次旋转
	
2.删除：
	红黑树中的删除也可以自顶向下进行。每一件工作都归于能够删除一片树叶。(类似于二叉搜索树的删除结点的做法)
	要删除一个带两个儿子的结点，我们用右子树的最小结点代替它，该结点必然最多有一个儿子(NullNode)，然后将该结点删除
	
	要删除一个只有右儿子的结点，我们用右子树的最小结点代替它，
	要删除一个只有做儿子的结点，我们用左子树的最大结点代替它，
	对于红黑树带有一个儿子结点的情形，我们不想使用这种方法进行，因为这可能在树的中部连接两个红色结点，为红黑条件的实现增加困难

	红色树叶的删除很简单，但是如果一片树叶是黑的，那么删除操作会复杂的多，删除黑色结点将破坏性质4.





自己总结的内容
	1.一个红色结点的左右儿子必定成对出现,且都是黑色
*/

#include <stdio.h>
#include <Windows.h>
#include "RedBlackTree.h"

int main()
{
	//printf("0x%08x\n", NullNode);
	//printf("red: %d\t\tblack:%d\n", Red, Black);
	//printf("%d\n", NegInfinity);

	RedBlackTree T = Initialize();
	Insert(10, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(85, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(15, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(70, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(20, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(60, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(30, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");
	
	Insert(50, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(65, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(80, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(90, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(40, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(5, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Insert(55, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	Delete(15, T);
	print_redblacktree(T->Right, T->Right->Element, 0);
	printf("\n\n");

	system("pause");
	return 0;
}