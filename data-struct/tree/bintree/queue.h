#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

#define QUEUESIZE 100  /*队列初始容量*/

/*队列数据结构*/
struct LinkQueue {
	ElemType data[QUEUESIZE];
	int front;	/*队列的头指针*/
	int rear;	/*队列的尾指针*/
};

typedef struct QNode {
	ElemType data;
	struct QNode *next;
}LQNode, *QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void init_queue(LinkQueue *LQ);
//int destroy_queue(LinkQueue *Q);
void clear_queue(LinkQueue *LQ);
int empty_queue(LinkQueue LQ);
int length_queue(LinkQueue LQ);
int head_queue(LinkQueue LQ, ElemType *e);
void push_queue(LinkQueue *LQ, ElemType data);
int pop_queue(LinkQueue *LQ, ElemType *e);
//Status traverse_queue(LinkQueue Q, void(*vi)(ElemType));

#endif
