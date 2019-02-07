#include <Windows.h>
#include "SplayTree.h"

int main()
{
	Node *root = NULL;
	root = insert_splaytree(root, 40);
	root = insert_splaytree(root, 20);
	root = insert_splaytree(root, 10);
	root = insert_splaytree(root, 30);
	root = insert_splaytree(root, 60);
	root = insert_splaytree(root, 50);
	root = insert_splaytree(root, 70);
	//inorder_splaytree(root);
	//printf("\n");
	//preorder_splaytree(root);
	//printf("\n");
	//postorder_splaytree(root);
	//printf("\n");
	print_splaytree(root, root->key, 0);
	//root = iterative_splaytree_search(root, 15);
	//print_splaytree(root, root->key, 0);
	root = access_splaytree(root, 30);
	print_splaytree(root, root->key, 0);
	root = access_splaytree(root, 20);
	print_splaytree(root, root->key, 0);
	root = delete_splaytree(root, 50);
	print_splaytree(root, root->key, 0);
	system("pause");
	return 0;
}