#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

#define STACKSIZE 100

/*栈数据结构*/
typedef struct {
	ElemType data[STACKSIZE];
	int top;
}SeqStack;

/*链式存储*/
struct LinkStack {
	ElemType data;
	struct LinkStack *next;
};

void init_stack(struct LinkStack **S);
void push_stack(struct LinkStack *S, ElemType data);
void pop_stack(struct LinkStack *S, ElemType *data);
int empty_stack(struct LinkStack *S);
int top_stack(struct LinkStack *S, ElemType *data);
void clear_stack(struct LinkStack *S);
ElemType visit(ElemType p);

#endif
