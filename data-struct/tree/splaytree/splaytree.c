/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 *
 * http://www.cnblogs.com/skywang12345/p/3604238.html
 * */

#include "splaytree.h"

static int arr[] = {10,50,40,30,20,60};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main(int *argc, char **argv)
{
	int i, ilen;
	SplayTree root = NULL;

	printf("== 依次添加: ");

	ilen = TBL_SIZE(arr);
	for(i=0; i<ilen; i++) {
		printf("%d ", arr[i]);
		root = insert_splaytree(root, arr[i]);
	}

	printf("\n== 前序遍历: ");
	preorder_splaytree(root);

	printf("\n== 中序遍历: ");
	inorder_splaytree(root);

	printf("\n== 后序遍历: ");
	postorder_splaytree(root);
	printf("\n");

	printf("== 最小值: %d\n", splaytree_minimum(root)->key);
	printf("== 最大值: %d\n", splaytree_maximum(root)->key);
	printf("== 树的详细信息: \n");
	print_splaytree(root, root->key, 0);

	i = 30;
	printf("\n== 旋转节点(%d)为根节点\n", i);
	printf("== 树的详细信息: \n");
	root = splaytree_splay(root, i);
	print_splaytree(root, root->key, 0);

	// 销毁伸展树
	destroy_splaytree(root);

	return 0;
}