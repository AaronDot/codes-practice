#ifndef LINKLIST_H_
#define LINKLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*定义链表*/
struct LNode {
	int elem;
	struct LNode *next;
};

struct LNode *init_list(struct LNode **head);
struct LNode *create_list(struct LNode *head);
struct LNode *create_list_2(struct LNode *head);
int insert_list(struct LNode *head, int pos, int e);
struct LNode *get_elem(struct LNode *head, int pos);
int search_elem(struct LNode *head, int e);
int delete_elem(struct LNode *head, int pos);
int clear_list(struct LNode *head);
void destory_list(struct LNode **head);
int empty_list(struct LNode *head);
int length_list(struct LNode *head);
struct LNode *get_privor(struct LNode *head, int e);
struct LNode *get_next(struct LNode *head, int e);
void printf_list(struct LNode *head);
struct LNode *reserve_list(struct LNode *head);
struct LNode *reserve_list_2(struct LNode *head);
void reserve_list_3(struct LNode *head);
void merge_list(struct LNode *La, struct LNode **Lb, struct LNode **Lc);
void move_node(struct LNode **destRef, struct LNode **sourceRef);
struct LNode *sorted_merge(struct LNode *a, struct LNode *b);
struct LNode *sorted_merge_2(struct LNode *a, struct LNode *b);
struct LNode *sorted_merge_3(struct LNode *a, struct LNode *b);
void selection_menu(void);
void select_function(int choice, int *flag);
#endif
