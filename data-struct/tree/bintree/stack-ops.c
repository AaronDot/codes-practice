/*
 *	Created on:	2015-07-02
 *	    Author:	Aaron Chou
 * */

#include "stack.h"

void init_stack(struct LinkStack **top)
{
	*top = (struct LinkStack *)malloc(sizeof(struct LinkStack));
	if (*top == NULL) {
		printf("init error\n");
		exit(-1);
	}
	(*top)->next = NULL;
}

int empty_stack(struct LinkStack *top)
{
	if (top->next == NULL)
		return 1;
	else
		return 0;
}

void push_stack(struct LinkStack *top, ElemType data)
{
	struct LinkStack *p;

	p = (struct LinkStack *)malloc(sizeof(struct LinkStack));
	if (p == NULL) {
		printf("malloc error\n");
		exit(-1);
	}

	p->data = data;
	p->next = top->next;
	top->next = p;
}

void pop_stack(struct LinkStack *top, ElemType *data)
{
	struct LinkStack *p;

	p = top->next;
	if (p == NULL) {
		printf("stack is empty\n");
		return;
	}

	top->next = p->next;
	*data = p->data;
	free(p);
}

int top_stack(struct LinkStack *top, ElemType *data)
{
	struct LinkStack *p;

	p = top->next;
	if (p == NULL) {
		printf("stack is empty\n");
		return 0;
	}
	*data = p->data;

	return 1;
}

int length_stack(struct LinkStack *top)
{
	struct LinkStack *p;
	int count = 0;

	p = top;
	while (p->next != NULL) {
		p = p->next;
		count ++;
	}

	return count;
}

void destory_statck(struct LinkStack **top)
{
	struct LinkStack *p, *q;

	p = *top;
	while (p != NULL) {
		q = p;
		p = p->next;
		free(q);
	}
}

void clear_stack(struct LinkStack *top)
{
	struct LinkStack *p, *q;

	p = top->next;
	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
	top->next = NULL;
}

/*访问结点*/
ElemType visit(ElemType p)
{
	return (*p).data;
}

#if 0
int init_stack(struct LinkStack *S)
{
	S->base = (ElemType)malloc(STACKSIZE * sizeof(struct LinkStack));
	if (!S->base)
		return -1;
	S->top = S->base;
	S->size = STACKSIZE;
	return 0;
}

void push_stack(struct LinkStack *S, ElemType data)
{
	*(S->top)++ = data;
}

void pop_stack(struct LinkStack *S, ElemType *data)
{
	*data = *(--S->top);
}

Status empty_stack(struct LinkStack S)
{
	return (S.base == S.top);
}

void destory_statck(struct LinkStack *S)
{
	S->base = S->top = NULL;
	S->size = 0;
	free(S->base);
	free(S->top);
}

int top_stack(struct LinkStack S, ElemType *data)
{
	if (!empty_stack(S)) {
		*data = *(--S.top);
		return 0;
	}
	return -1;
}

void clear_stack(struct LinkStack *S)
{
	S->top = S->base;
}

#endif
#if 0
/*初始化栈*/
void init_stack(SeqLinkStack *S)
{
	S->top = -1;
}

/*
 * 进栈
 * 无论是进栈还是取栈顶元素都应该是指向树的指针
 * */
void Push(SeqLinkStack *S, ElemType p)
{
	if (S->top == STACKSIZE - 1) {
		printf("the stack is over flow\n");
	} else {
		S->top = S->top + 1;
		S->data[S->top] = p;
	}
}

/*
 * 出栈
 * */
int Pop(SeqLinkStack *S, ElemType *p)
{
	if (S->top == -1) {
		printf("the stack is under flow\n");
		return 0;
	} else {
		*p = S->data[S->top];
		--S->top;
		return 1;
	}
}

/*
 * 判断栈是不是空
 * */
int EmptyLinkStack(SeqLinkStack S)
{
	if (S.top == -1)
		return 1;
	else
		return 0;
}

/*取出栈顶元素*/
int GetTop(SeqLinkStack S, ElemType *p)
{
	if (S.top==-1) {
		printf("the stack is empty\n");
		return 0;
	} else {
		*p = S.data[S.top];
		return 1;
	}
}
#endif
