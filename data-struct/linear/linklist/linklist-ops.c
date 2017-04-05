/*
 *	Created on:	2015-07-02
 *	    Author:	Aaron Chou
 * */

#include "linklist.h"

struct LNode *init_list(struct LNode **head)
{
	*head = (struct LNode *)malloc(sizeof(struct LNode));
	if (!*head)
		return NULL;

	(*head)->next = NULL;
	return *head;
}

/*单链表的建立2，尾插法建立单链表*/
struct LNode *create_list(struct LNode *head)
{
	int e;
	struct LNode *new, *plist, *last;

	plist = init_list(&head);
	if (plist == NULL) {
		printf("init list error\n");
		exit(-1);
	}

	last = plist;				/*r始终指向终端结点,开始时指向头结点*/
	while (scanf("%d", &e)) {
		new = (struct LNode *)malloc(sizeof(struct LNode));
		if (!new) {
			printf("alloc new list node fail\n");
			exit(-1);
		}

		new->elem = e;
		last->next = new;		/*将结点插入到表头L-->|1|-->|2|-->NULL*/
		last = new;

		if (getchar() == '\n')
			break;
	}

	last->next = NULL;

	return plist;
}

/*单链表的建立1，头插法建立单链表*/
struct LNode *create_list_2(struct LNode *head)
{
	struct LNode *plist, *new;
	int e;

	plist = init_list(&head);
	if (plist == NULL) {
		printf("init list error\n");
		exit(-1);
	}

	while (scanf("%d", &e)) {
		new = (struct LNode *)malloc(sizeof(struct LNode));
		if (!new) {
			printf("alloc new list node fail\n");
			exit(-1);
		}

		new->elem = e;
		new->next = plist->next;		/*将结点插入到表头L-->|2|-->|1|-->NULL*/
		plist->next = new;

		if (getchar() == '\n')
			break;
	}

	return plist;
}

/*按位置查找*/
struct LNode *get_elem(struct LNode *head, int pos)
{
	int j = 0;
	struct LNode *p = head;

	while (p && (j < pos)) {
		p = p->next;
		j++;
	}

	if (!p || (j > pos))
		return NULL;

	return p;
}

int insert_list(struct LNode *head, int pos, int e)
{
	/*遍历链表*/
	struct LNode *p = NULL;
	struct LNode *s = NULL;

	/*找到pos-1*/
	p = get_elem(head, pos-1);

	if (!p) {
		return -1;
	}

	/*利用s插入e*/
	s = (struct LNode *)malloc(sizeof(struct LNode));
	s->elem = e;
	s->next = p->next;
	p->next = s;

	return 0;
}

/*通过位置删除*/
int delete_elem(struct LNode *head, int pos)
{
	struct LNode *p = NULL, *s = NULL;

	p = get_elem(head, pos - 1);

	if (!p || !p->next)
		return -1;

	s = p->next;
	p->next = s->next;
	free(s);

	return 0;
}

int clear_list(struct LNode *head)
{
	struct LNode *p = NULL, *s = NULL;

	if (head == NULL)
		return -1;

	p = head;
	while (p->next != NULL) {
		s = p->next;
		free(p);
		p = s;
	}
	head->next = NULL;

	return 0;
}

void destory_list(struct LNode **head)
{
	struct LNode *p = NULL;

	while (*head != NULL) {
		p = (*head)->next;
		free(*head);
		*head = p;
	}
}

int empty_list(struct LNode *head)
{
	if (head->next == NULL)
		return 0;
	else
		return 1;
}

int length_list(struct LNode *head)
{
	struct LNode *p = head->next;
	int len = 0;

	while (p != NULL) {
		p = p->next;
		len++;
	}

	return len;
}

/*按值查找*/
int search_elem(struct LNode *head, int e)
{
	struct LNode *p = head->next;
	int pos = 0;

	while (p != NULL && (p->elem != e)) {
		p = p->next;
		pos++;
	}

	if (!p)
		pos = -1;

	return pos;
}

/*根据值找到priv*/
struct LNode *get_privor(struct LNode *head, int e)
{
	struct LNode *p = head;
	struct LNode *s = p->next;

	while (p != NULL && (s->elem != e)) {
		p = s;
		s = p->next;
	}

	return p;
}

/*根据值找到next*/
struct LNode *get_next(struct LNode *head, int e)
{
	struct LNode *p = head;

	while (p->next != NULL && (p->elem != e))
		p = p->next;

	return p->next;
}

void printf_list(struct LNode *head)
{
	struct LNode *p = head;

	while (p->next) {
		p = p->next;
		printf("%d ", p->elem);
	}

	printf("\n");
}

/*
 * 逆置算法思路:
 * 先将head->next置为null,然后将链表的节点依次插入到head后,并与已插入的节点链接起来,就实现了逆置
 * 依次取原链表中每个结点,将其作为第一个结点插入到新的链表中去,指针p用来指向原表中当前结点,p为空时结束
 * 整个算法思想就是把每个结点都插到头结点之后,那两步表示把当前访问结点P直接插到头结点之后
 * */
struct LNode *reserve_list(struct LNode *head)
{
	struct LNode *p = head->next;
	struct LNode *s = NULL;

	head->next = NULL;

	while (p) {
		s = p;
		p = p->next;
		s->next = head->next;	/*将新插入节点与已插入的节点链接起来*/
		head->next = s;		/*将新插入节点与head节点链接起来*/
	}

	return head;
}

/*
 * 分析:
 * 可以用交换数据的方式来达到逆置的目的.
 * 但由于是单链表,可以利用指针改指来达到表逆置的目的.
 * 具体情况入下:
 * (1)当链表为空表或只有一个结点时,该链表的逆置链表与原表相同
 * (2)当链表含2个以上结点时,可将该链表处理成只含第一结点的带头结点链表和一个无头结点的包含该链表剩余结点的链表.
 * 	然后将该无头结点链表中的所有结点顺着链表指针,由前往后将每个结点依次从无头结点链表中摘下,作为第一个结点插入到带头结点链表中.
 * 	这样就可以得到逆置的链表
 * */
struct LNode *reserve_list_2(struct LNode *head)
{
	/*设置两个临时指针变量*/
	struct LNode *p, *q ;

	 /*当链表不是空表或单结点时*/
	if (head->next && head->next->next) {
		p = head->next;
		q = p->next;
		p->next = NULL;		/*将开始结点变成终端结点*/
		while (q) {		/*每次循环将后一个结点变成开始结点*/
			p = q;
			q = q->next;
			p->next = head-> next;
			head->next = p;
		}
		return head;
	}

	return head;			/*如是空表或单结点表,直接返回head*/
}

void reserve_list_3(struct LNode *head)
{
	struct LNode *p, *q, *s;

	p = head->next;
	if (p && p->next) {
		q = p->next;
		p->next = NULL;
	}

	while (q) {
		s = q->next;
		q->next = p;
		p = q;
		q = s;
	}

	head->next = p;
}

/*
 * 已知单链线性表La和Lb的元素按值非递减排列
 * 归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
 * */
void merge_list(struct LNode *La, struct LNode **Lb, struct LNode **Lc)
{
	struct LNode *pa = La->next, *pb = (*Lb)->next, *pc;

	/*用La的头结点作为Lc的头结点*/
	*Lc = pc = La;
	while (pa && pb) {
		if (pa->elem <= pb->elem) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		} else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;	/* 插入剩余段 */
	free(*Lb);			/* 释放Lb的头结点 */
	Lb = NULL;
}

#if 0
struct list *list_merge(struct list *head1, struct list *head2)
{
	struct list *res;

	if (head1 == NULL) return head2;
	if (head2 == NULL) return head1;

	if (head1->key < head2->key) {
		res = head1;
		printf("res1 %d\n",res->key);
		res->next = list_merge(head1->next, head2);
	} else {
		res = head2;
		printf("res2 %d\n",res->key);
		res->next = list_merge(head1, head2->next);
	}

	return res;
}


struct list *list_merge2(struct list *head1, struct list *head2)
{
	struct list *head,*p1,*p2, *pcurrent;

	if (head1 == NULL)
		return head2;

	if (head2 == NULL)
		return head1;

	if (head1->key < head2->key) {
		head = head1;
		p1 = head1->next;
		p2 = head2;
	} else {
		head = head2;
		p2 = head2->next;
		p1 = head1;
	}

	pcurrent = head;
	while (p1 != NULL && p2 != NULL) {
		if (p1->key <= p2->key) {
			pcurrent->next = p1;
			pcurrent = p1;
			p1 = p1->next;
		} else {
			pcurrent->next = p2;
			pcurrent = p2;
			p2 = p2->next;
		}
	}

	if (p1 != NULL)
		pcurrent->next = p1;
	if (p2 != NULL)
		pcurrent->next = p2;

	return head;
}
#endif

/*
 * pull off the front node of the source and put it in dest
 * MoveNode() function takes the node from the front of the source, and move it to the front of the dest.
 * It is an error to call this with the source list empty.
 * 	Before calling MoveNode():
 * 	source == {1, 2, 3}
 * 	dest == {1, 2, 3}
 *
 * 	After calling MoveNode():
 * 	source == {2, 3}
 * 	dest == {1, 1, 2, 3}
 * */
void move_node(struct LNode **destRef, struct LNode **sourceRef)
{
	/* the front source node */
	struct LNode *newNode = *sourceRef;
	assert(newNode != NULL);

	/*Advance the source pointer */
	*sourceRef = newNode->next;
	/* Link th eold dest off the new node */
	newNode->next = *destRef;
	/*Move dest to point to the new node */
	*destRef = newNode;
}

/*
 * see http://www.geeksforgeeks.org/merge-two-sorted-linked-lists/
 * Takes two lists sorted in creasing order, and splices their nodes together to
 * make ont big sorted list which is returned.
 * */
struct LNode *sorted_merge(struct LNode *a, struct LNode *b)
{
	/* a dummy first node to hang the result on */
	struct LNode dummy;

	/* tail points to the last result node */
	struct LNode* tail = &dummy;

	/*so tail->next is the places to add new nodes to the result*/
	dummy.next = NULL;
	while (1) {
		if (a == NULL) {
			tail->next = b;
			break;
		} else if (b == NULL) {
			tail->next = a;
			break;
		}

		if (a->elem <= b->elem)
			move_node(&(tail->next), &a);
		else
			move_node(&(tail->next), &b);

		tail = tail->next;
	}

	return (dummy.next);
}

/* method2 Using local References */
struct LNode *sorted_merge_2(struct LNode *a, struct LNode *b)
{
	struct LNode *result = NULL;

	/*point to the last result pointer */
	struct LNode **lastPtrRef = &result;

	while (1) {
		if (a == NULL) {
			*lastPtrRef = b;
			break;
		} else if(b == NULL) {
			*lastPtrRef = a;
			break;
		}

		if (a->elem <= b->elem)
			move_node(lastPtrRef, &a);
		else
			move_node(lastPtrRef, &b);
		/*tricky:advance to point to the next ".next" field */
		lastPtrRef = &((*lastPtrRef)->next);
	}

	return (result);
}

/*Using Recursion*/
struct LNode *sorted_merge_3(struct LNode *a, struct LNode *b)
{
	struct LNode *result = NULL;

	/*Base cases*/
	if (a == NULL)
		return (b);
	else if(b == NULL)
		return (a);

	/*Pick either a or b, and recur */
	if (a->elem <= b->elem) {
		result = a;
		result->next = sorted_merge_3(a->next, b);
	} else {
		result = b;
		result->next = sorted_merge_3(a, b->next);
	}

	return (result);
}

/*
 * 给定一个单链表,删除倒数第n个节点,返回删除了的链表
 * 	例: 已知: 1->2->3->4->5,  n = 2.
 * 	处理后：1->2->3->5.
 * 	试着遍历一次完成
 * 二:分析
 * 使用双指针,
 * 	因为要删除倒数第n个数,所以两个指针的间距也就是这个n,当右边的指针到达末尾处时,那么左指针的下一个指针就是要删除的节点.
 * 	其实会有下面几种特殊情况:
 * 	1.{1,2},n=1;
 * 	2.{1,2},n=2;
 * 	3.{},0
 * 当然,有人可能会说n可不可以大于节点数,不过这个题目已经限制了n是有效的。
 * 扩展：1、n的值不限制
 * 2、链表不限于单链表，求删除离头节点倒数n个
 * */
struct LNode *remove_nthnode_from_end(struct LNode *head, int n)
{
	struct LNode *right_node, *left_node;
	int i;

	if (head == NULL || head->next == NULL)
		return NULL;

	left_node = right_node = head;

	for (i=1; i<=n; i++) {
		right_node = right_node->next;
	}

	if (right_node == NULL) {
		head = head->next;
		return head;
	}

	while (right_node->next != NULL) {
		left_node = left_node->next;
		right_node = right_node->next;
	}

	left_node->next = left_node->next->next;
	return head;
}
