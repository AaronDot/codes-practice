/*
 *	Created on:	2015-07-02
 *	    Author:	Aaron Chou
 * */

#include "queue.h"

void init_queue(LinkQueue *LQ)
{
	LQ->front=LQ->rear=(LQNode *)malloc(sizeof(LQNode));
	if (LQ->front == NULL)
		exit(-1);

	LQ->front->next = NULL;
}

int empty_queue(LinkQueue LQ)
{
	if (LQ.front == LQ.rear)
		return 1;
	else
		return 0;
}

void push_queue(LinkQueue *LQ, ElemType data)
{
	LQNode *s;

	s = (LQNode *)malloc(sizeof(LQNode));
	if (s == NULL)
		exit(-1);

	s->data = data;
	s->next = NULL;
	LQ->rear->next = s;
	LQ->rear = s;
}

int pop_queue(LinkQueue *LQ, ElemType *data)
{
	LQNode *s;

	if (LQ->front == LQ->rear)
		return 0;

	s = LQ->front->next;
	*data = s->data;
	LQ->front->next = s->next;
	if (LQ->rear == s)
		LQ->rear = LQ->front;
	free(s);

	return 1;
}

int head_queue(LinkQueue LQ, ElemType *data)
{
	LQNode *s;

	if (LQ.front == LQ.rear)
		return 0;

	s = LQ.front->next;
	*data = s->data;

	return 1;
}

void clear_queue(LinkQueue *LQ)
{
	while (LQ->front != NULL) {
		free(LQ->front);
		LQ->front = LQ->rear;
	}
}

/* 求队列的长度 */
int length_queue(LinkQueue LQ)
{
	int count = 0;
	QueuePtr p;

	p = LQ.front;
	while (LQ.rear != p) {
		count++;
		p = p->next;
	}

	return count;
}
