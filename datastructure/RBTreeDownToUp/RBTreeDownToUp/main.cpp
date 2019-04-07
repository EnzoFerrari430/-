#include <stdio.h>
#include <Windows.h>
#include "RedBlackTree.h"

/*
此篇完成自底向上的方式
*/

int main()
{
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