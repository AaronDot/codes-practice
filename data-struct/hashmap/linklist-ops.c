/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 * */

#include "linklist.h"

//创建链表
MyList *createMyList()
{
	MyList * re;

	re = (MyList *) malloc(sizeof(MyList));
	re->count = 0;
	re->first = NULL;
	re->last = NULL;
	re->equal = NULL;

	return re;
}

//释放链表
void freeMyList(MyList *list)
{
	MyNode *p;

	while (list->first) {
		p = list->first->next;
		free(list->first);
		list->first = p;
	}

	free(list);
}

//插入在尾部
void myListInsertDataAtLast(MyList *const list, void *const data)
{
	MyNode *node;

	node = (MyNode *) malloc(sizeof(MyNode));
	node->data = data;
	node->next = NULL;

	if (list->count) {
		list->last->next = node;
		list->last = node;
	} else {
		list->first = node;
		list->last = node;
	}

	(list->count)++;
}

//插入在首部
void myListInsertDataAtFirst(MyList *const list, void *const data)
{
	MyNode * node;

	node = (MyNode *) malloc(sizeof(MyNode));
	node->data = data;
	node->next = NULL;

	if (list->count) {
		node->next = list->first;
		list->first = node;
	} else {
		list->first = node;
		list->last = node;
	}

	(list->count)++;
}

//长度
int myListGetSize(const MyList *const list)
{
	return list->count;
}

//打印
void myListOutput(const MyList *const list, void(*pt)(const void *const))
{
	MyNode *p;

	p = list->first;
	while (p) {
		(*pt)(p->data);
		p = p->next;
	}
}

//删除在尾部
void *myListRemoveDataAtLast(MyList *const list)
{
	MyNode *p;
	void *re;

	if (list->count == 1)
		return myListRemoveDataAtFirst(list);

	p = list->first;
	while (p->next != list->last)
		p = p->next;

	re = list->last->data;
	free(list->last);
	p->next = NULL;
	list->last = p;
	(list->count)--;

	return re;
}

//删除在首部
void *myListRemoveDataAtFirst(MyList *const list)
{
	void *re;
	MyNode *p;

	p = list->first;

	list->first = p->next;
	re = p->data;
	free(p);

	(list->count)--;
	if (list->count == 0)
		list->last = NULL;

	return re;
}

//插入
void myListInsertDataAt(MyList *const list, void *const data, int index)
{
	int i;
	MyNode *node, *p;

	if (index == 0) {
		myListInsertDataAtFirst(list, data);
		return;
	}

	if (index == list->count) {
		myListInsertDataAtLast(list, data);
		return;
	}

	node = (MyNode *) malloc(sizeof(MyNode));
	node->data = data;
	node->next = NULL;

	p = list->first;
	for (i = 0; i < index - 1; i++)
		p = p->next;

	node->next = p->next;
	p->next = node;

	(list->count)++;
}

//删除
void *myListRemoveDataAt(MyList *const list, int index)
{
	int i;
	void *re;
	MyNode *p, *tp;

	if (index == 0)
		return myListRemoveDataAtFirst(list);

	if (index == list->count - 1)
		return myListRemoveDataAtLast(list);

	p = list->first;
	for (i = 0; i < index - 1; i++)
		p = p->next;

	tp = p->next;
	p->next = p->next->next;
	re = tp->data;
	free(tp);

	(list->count)--;

	return re;
}

//取得数据
void *myListGetDataAt(const MyList *const list, int index)
{
	int i;
	MyNode *p;

	if (index == list->count - 1)
		return myListGetDataAtLast(list);

	p = list->first;
	for (i = 0; i < index; i++)
		p = p->next;

	return p->data;
}

//取得第一个数据
void *myListGetDataAtFirst(const MyList *const list)
{
	return list->first->data;
}

//取得最后一个数据
void *myListGetDataAtLast(const MyList *const list)
{
	return list->last->data;
}

//查找某个数据的位置,如果equal方法为空，比较地址，否则调用equal方法
//如果不存在返回-1，如果存在，返回出现的第一个位置
int myListFindDataIndex(const MyList *const list, void *data)
{
	MyNode *p = list->first;
	int re = 0;

	if (list->equal) {
		while (p) {
			if (p->data == data ||
					(*(list->equal))(p->data, data))
				return re;

			re++;
			p = p->next;
		}
	} else {
		while (p) {
			if (p->data == data)
				return re;

			re++;
			p = p->next;
		}
	}
	return -1;
}

//创建链表，带有相等参数，用于查找
MyList *createMySearchList(int(*equal)(void *a, void *b))
{
	MyList *re;

	re = createMyList();
	re->equal = equal;

	return re;
}

//创建遍历器
MyListIterator *createMyListIterator(const MyList *const list)
{
	MyListIterator *re;

	re = (MyListIterator *) malloc(sizeof(MyListIterator));
	re->p = list->first;
	re->allSize = list->count;
	re->count = 0;

	return re;
}

//释放遍历器
void freeMyListIterator(MyListIterator* iterator)
{
	free(iterator);
}

//遍历器是否有下一个元素
int myListIteratorHasNext(const MyListIterator* const iterator)
{
	return iterator->count < iterator->allSize;
}

//返回遍历器的下一个元素
void *myListIteratorNext(MyListIterator *const iterator)
{
	void *re;

	re = iterator->p->data;
	iterator->p = iterator->p->next;
	(iterator->count)++;

	return re;
}

//删除对象,返回是否删除成功
int myListRemoveDataObject(MyList *const list, void *data)
{
	void *ld;
	int a = 0;
	MyListIterator *it = createMyListIterator(list);

	while (myListIteratorHasNext(it)) {
		ld = myListIteratorNext(it);
		if (data == ld || (list->equal != NULL &&
				(*(list->equal))(ld, data))) {
		    a = 1;
		    break;
		}
	}

	if (a)
		myListRemoveDataAt(list, it->count - 1);

	return a;
}
