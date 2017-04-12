/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 * */

#include "bstree.h"

//创建二叉查找树
/**
 *  输入-1时创建结束,其实是一个不断插入的过程
 */
void CreateBinarySearchTree(BiTNode **T)
{
	int num;

	printf("请输入创建二叉查找树的数字序列：\n");

	scanf("%d",&num);
	while (num != -1) {
		Insert(T,num);
		scanf("%d",&num);
	}

	printf("%s函数执行，二叉查找树创建成功\n", __FUNCTION__);
}

//插入节点
void Insert(BiTNode **T, int x)
{
	//这里创建一个要插入的节点
	BiTNode *pInsert;

	pInsert = (BiTNode *)malloc(sizeof(BiTNode));
	pInsert->data = x;
	pInsert->lChild = NULL;
	pInsert->rChild = NULL;

	if ((*T) == NULL) {
		*T = pInsert;
		return;
	}

	if ((*T)->lChild == NULL && x < (*T)->data) {
		(*T)->lChild = pInsert;
		return;
	}

	if ((*T)->rChild == NULL && x > (*T)->data) {
		(*T)->rChild = pInsert;
		return;
	}

	//递归实现
	if (x < (*T)->data)
		Insert(&(*T)->lChild, x);
	if (x > (*T)->data)
		Insert(&(*T)->rChild, x);

}

//中序遍历二叉查找树
//打印的应该是一个递增的序列
void MiddleOrder(BiTNode *T)
{
	if (T == NULL)
		return;

	MiddleOrder(T->lChild);
	printf("%d ",T->data);
	MiddleOrder(T->rChild);
}

//先序遍历二叉查找树
//因为先序遍历+中序遍历 可以唯一确定一棵树，等下可以验证树是否正确
void PreOrder(BiTNode *T)
{
	if (T == NULL)
		return;

	printf("%d ",T->data);
	PreOrder(T->lChild);
	PreOrder(T->rChild);
}

//查找某一个值
//返回1表示找到该值，返回0表示没有找到
void SearchValue(BiTNode *T, int x)
{
	if (T == NULL)
		return;

	if (x < T->data)
		//查左子树
		SearchValue(T->lChild, x);
	else if (x > T->data)
		//查右子树
		SearchValue(T->rChild, x);
	else {
		//找到该值
		printf("该值的内存地址为：%p\n",T);
	}
}
