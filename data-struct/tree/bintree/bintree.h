#ifndef BINTREE_H_
#define BINTREE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*定义二叉树*/
struct BinTreeNode {
	char elem;
};

struct BinTreeLink {
	struct BinTreeNode *data;
	struct BinTreeLink *lchild, *rchild;
};

typedef struct BinTreeLink BinTnode;
typedef struct BinTreeLink *BinTree;

typedef BinTree ElemType;

void create_bintree(BinTree *proot);
void preorder_recursive(BinTree proot);
void preorder_nonrecursive(BinTree proot);
void preorder_nonrecursive_2(BinTree proot);
void preorder_nonrecursive_3(BinTree proot);
void inorder_recursive(BinTree proot);
void inorder_nonrecursive(BinTree proot);
void inorder_nonrecursive_2(BinTree proot);
void inorder_nonrecursive_3(BinTree proot);
void postorder_recursive(BinTree proot);
void postorder_nonrecursive(BinTree proot);
void postorder_nonrecursive_2(BinTree proot);
void postorder_nonrecursive_3(BinTree proot);
void postorder_nonrecursive_4(BinTree proot);
void layerorder_nonrecursive(BinTree proot);
void layerorder_nonrecursive_2(BinTree proot);
void layerorder_nonrecursive_3(BinTree proot);

int bintree_depth(BinTree proot);
int bintree_node(BinTree proot);

int bintree_total_leafnode(BinTree proot);
int bintree_kthlevel_node(BinTree proot, int kth_level);
int bintree_kthlevel_node_nonrecursive(BinTree proot, int kth_level);
int bintree_kthlevel_leafnode(BinTree proot, int kth_level);
int bintree_kthlevel_leafnode_nonrecursive(BinTree proot, unsigned int kth_level);
BinTree bintree_kthlevel_mthnode(BinTree proot, int kth_level, int mth_node);
int bintree_structure_compare(BinTree proot1, BinTree proot2);
int bintree_structure_compare_nonrecursive(BinTree proot1, BinTree proot2);
int bintree_all_compare(BinTree proot1, BinTree proot2);
int bintree_all_compare_nonrecursive(BinTree proot1, BinTree proot2);
BinTree bintree_mirror(BinTree proot);
BinTree bintree_mirror_nonrecursive(BinTree proot);

BinTree rebuild_bintree(char *in_order, char *post_order, int nodes_total);
BinTree rebuild_bintree_pre(char *pre_order, char *in_order, int nodes_total);
int compare(struct BinTreeNode *node1, struct BinTreeNode *node2);

void selection_menu(void);
void select_function(int choice, int *flag);
#endif
