/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 *
 * http://blog.csdn.net/chenyufeng1991/article/details/50901205
 * */

#include "bstree.h"

int main(int argc, const char * argv[])
{
	BiTNode *tree;

	//这个是引用传递
	CreateBinarySearchTree(&tree);

	MiddleOrder(tree);
	printf("\n");

	printf("请输入要查找的元素:");
	int searchValue;
	scanf("%d", &searchValue);
	SearchValue(tree, searchValue);

	printf("先序遍历:");
	PreOrder(tree);
	printf("\n中序遍历:");
	MiddleOrder(tree);//遍历检查
	printf("\n");

	return 0;
}
