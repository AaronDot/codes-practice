/*
 *	Created on:	2015-07-02
 *	    Author:	Aaron Chou
 *
 * 	http://blog.csdn.net/hackbuteer1/article/details/6583988
 * 	http://blog.csdn.net/beitiandijun/article/details/42002337
 * */

#include "stack.h"
#include "queue.h"
#include "bintree.h"

int main(void)
{
	int flag = 1, choice;

	selection_menu();

	while (flag) {
		printf("please select the function:");
		scanf("%d", &choice);
		select_function(choice, &flag);
	}

	return 0;
}

void selection_menu(void)
{
	printf("                     本程序实现二叉树的基本操作.\n");
	printf("可以进行建立二叉树,递归先序,中序,后序遍历,非递归先序,中序遍历及非递归层序遍历等操作.\n");
	printf("\n");
	printf("|--------------------------------------------------------------|\n");
	printf("|                    二叉树的基本操作如下:                     |\n");
	printf("|                        0.创建二叉树                          |\n");
	printf("|                        1.递归先序遍历                        |\n");
	printf("|                        2.递归中序遍历                        |\n");
	printf("|                        3.递归后序遍历                        |\n");
	printf("|                        4.非递归先序遍历                      |\n");
	printf("|                        5.非递归中序遍历                      |\n");
	printf("|                        6.非递归后序遍历                      |\n");
	printf("|                        7.非递归层序遍历                      |\n");
	printf("|                        8.二叉树的深度                        |\n");
	printf("|                        9.二叉树的结点个数                    |\n");
	printf("|                        10.退出程序                           |\n");
	printf("|--------------------------------------------------------------|\n");
}

void select_function(int choice, int *flag)
{
	BinTree root = NULL;
	BinTree dest;
//	BinTree root2;
	char pre_order[8] = {1, 2, 4, 7, 3, 5, 6, 8};
	char in_order[8] = {4, 7, 2, 1, 5, 3, 8, 6};
//	char post_order[8] = {7, 4, 2, 5, 8, 6, 3, 1};
//	int ret;

	switch (choice) {
	case 0:
		printf("building bintree and please input the root of bintree:");
		create_bintree(&root);
//		printf("请建立二叉树并输入二叉树2的根节点：");
//		create_bintree(&root2);
		break;
	case 1:
		if (root) {
			printf("the result of bintree's pre_order in recursive way:");
			preorder_recursive(root);
			printf("\n");
		} else {
			printf("          the bintree is NULL\n");
		}
		break;
	case 2:
		if (root) {
			printf("the result of bintree's in_order in recursive way:");
			inorder_recursive(root);
			printf("\n");
		} else {
			printf("          the bintree is NULL\n");
		}
		break;
	case 3:
		if (root) {
			printf("the result of bintree's post_order in recursive way:");
			postorder_recursive(root);
			printf("\n");
		} else {
			printf("          the bintree is NULL\n");
		}
		break;
	case 4:
		if (root) {
			printf("the result of bintree's pre_order in nonrecursive way:");
			preorder_nonrecursive(root);
			printf("\n");
		} else {
			printf("          the bintree is NULL\n");
		}
		break;
	case 5:
		if (root) {
			printf("the result of bintree's in_order in nonrecursive way:");
			inorder_nonrecursive_3(root);
			printf("\n");
		} else {
			printf("          the bintree is NULL\n");
		}
		break;
	case 6:
		if (root) {
			printf("the result of bintree's post_order in nonrecursive way:");
			postorder_nonrecursive_2(root);
			printf("\n");
		} else {
			printf("          the bintree is NULL\n");
		}
		break;
	case 7:
		if (root) {
			printf("the result of bintree's layer_order in nonrecursive way:");
			layerorder_nonrecursive_2(root);
			printf("\n");
		} else {
			printf("          the bintree is NULL\n");
		}
		break;
	case 8:
		if (root)
			printf("the depth of the bintree is: %d\n", bintree_depth(root));
		else
			printf("          the bintree is NULL\n");
		break;
	case 9:
		if (root)
			printf("the number of the bintree's nodes is:%d\n", bintree_node(root));
		else
			printf("          the bintree is NULL\n");
		break;
	case 10:
		if (root) {
			printf("这棵二叉树第三层的结点个数为：%d\n", bintree_kthlevel_node_nonrecursive(root, 3));
			printf("这棵二叉树第二层的叶子结点个数为：%d\n", bintree_kthlevel_leafnode_nonrecursive(root, 2));
			dest = bintree_kthlevel_mthnode(root, 2, 2);
			printf("这棵二叉树第二层第二个节点为：%c\n", dest->data->elem);
		} else
			printf("          the bintree is NULL\n");
		break;
//	case 11:
//		if (root && root2) {
//			ret = bintree_all_compare_nonrecursive(root, root2);
//			if (ret == 1)
//				printf("the same\n");
//			else
//				printf("different\n");
//		}
//		break;
	case 12:
		dest = rebuild_bintree_pre(pre_order, in_order, 8);
		printf("the rebuild bintree's root is: %d\n", dest->data->elem);
		break;
	default:
		flag = 0;
		printf("the program is over, please input any key too quit!\n");
	}
}
