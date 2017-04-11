#ifndef RB_TREE_H_
#define RB_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int key_t;
typedef int data_t;

enum rb_color {
	RED = 0,
	BLACK = 1
};

struct rb_node {
	struct rb_node *left;
	struct rb_node *right;
	struct rb_node *parent;
	key_t key;
	data_t data;
	enum rb_color color;
};

/* forward declaration */
struct rb_node* rb_insert(key_t key, data_t data, struct rb_node* root);
struct rb_node* rb_search(key_t key, struct rb_node* root);
struct rb_node* rb_erase(key_t key, struct rb_node* root);

#endif
