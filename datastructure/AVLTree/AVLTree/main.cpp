#include "avltree.h"
#include <Windows.h>
#include <stdio.h>

static int arr[] = { 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
#define TBL_SIZE(a) ((sizeof(a)) / (sizeof(a[0])))

int main()
{
	//int i, ilen;
	//AVLTree root = NULL;

	//printf("==height: %d\n",avltree_height(root));
	//printf("==insert by sort: ");
	//ilen = TBL_SIZE(arr);
	//for (i = 0; i < ilen; ++i)
	//{
	//	printf("%d ", arr[i]);
	//	root = avltree_insert(root, arr[i]);
	//}

	//printf("\n== preorder_print: ");
	//preorder_avltree(root);

	//printf("\n== inorder_print: ");
	//inorder_avltree(root);

	//printf("\n== postorder_print: ");
	//postorder_avltree(root);
	//printf("\n");

	//print_avltree(root, root->key, 0);

	//AVLTree root2 = NULL;
	//root2 = avltree_insert(root2, 5);
	//root2 = avltree_insert(root2, 2);
	//root2 = avltree_insert(root2, 4);
	//printf("\n");

	//print_avltree(root2, root2->key, 0);

	AVLTree root3 = NULL;
	root3 = avltree_insert(root3, 10);
	root3 = avltree_insert(root3, 5);
	root3 = avltree_insert(root3, 12);
	root3 = avltree_insert(root3, 3);
	root3 = avltree_insert(root3, 8);
	root3 = avltree_insert(root3, 14);
	root3 = avltree_insert(root3, 1);
	root3 = avltree_delete(root3, 8);
	printf("\n");

	print_avltree(root3, root3->key, 0);
	
	system("pause");
	return 0;
}