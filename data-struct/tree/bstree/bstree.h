/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 * */

#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BTNode {
	int data;
	struct BTNode *lChild;
	struct BTNode *rChild;
}BiTNode;

//声明
void CreateBinarySearchTree(BiTNode **T);
void Insert(BiTNode **T, int x);
void MiddleOrder(BiTNode *T);
void PreOrder(BiTNode *T);
void SearchValue(BiTNode *T, int x);

#endif
