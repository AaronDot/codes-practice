/*
 * 红黑树，一种二叉查找树，但在每个结点上增加一个存储位表示结点的颜色，可以是Red或Black
 * 通过对任何一条从根到叶子的路径上各个结点着色方式的限制，红黑树确保没有一条路径会比其他路径长出俩倍，因而是接近平衡的。
 *
 * 红黑树的5个性质(保证一棵n个结点的红黑树的高度始终保持在logn):
 * 	1. 每个结点要么是红的要么是黑的
 * 	2. 根结点是黑的
 * 	3. 每个叶结点(叶结点即指树尾端NIL指针或NULL结点)都是黑的
 * 	4. 如果一个结点是红的，那么它的两个儿子都是黑的
 * 	5. 对于任意结点而言，其到叶结点树尾端NIL指针的每条路径都包含相同数目的黑结点
 *
 * http://blog.csdn.net/v_JULY_v
 * */

#include "rbtree.h"

int main(int argc, char *argv[])
{
	struct rb_node* root = NULL, *node = NULL;
	int i, count = 900;
	key_t key;

	srand(time(NULL));

	for (i = 1; i < count; ++i) {
		key = rand() % count;
		if ((root = rb_insert(key, i, root))) {
			printf("[i = %d] insert key %d success!\n", i, key);
		} else {
			printf("[i = %d] insert key %d error!\n", i, key);
			exit(-1);
		}

		if ((node = rb_search(key, root))) {
			printf("[i = %d] search key %d success!\n", i, key);
		} else {
			printf("[i = %d] search key %d error!\n", i, key);
			exit(-1);
		}

		if (!(i % 10)) {
			if ((root = rb_erase(key, root)))
				printf("[i = %d] erase key %d success\n", i, key);
			else
				printf("[i = %d] erase key %d error\n", i, key);
		}
	}
	return 0;
}
