#include "rbtree.h"

#define rb_parent(r)		((r)->parent)
#define rb_color(r)		((r)->color)
#define rb_is_red(r)		((r)->color == RED)
#define rb_is_black(r)		((r)->color == BLACK)
#define rb_set_black(r)		do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)		do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)	do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)	do { (r)->color = (c); } while (0)

static struct rb_node *rb_new_node(key_t key, data_t data)
{
	struct rb_node *node;

	node = (struct rb_node *)malloc(sizeof(struct rb_node));

	if (!node) {
		printf("malloc error!\n");
		exit(-1);
	}

	node->key = key, node->data = data;

	return node;
}

/*-----------------------------------------------------------
 * 	 p				p
 *     /   \     left rotate          /   \
 *   node   d   ---------------->    r     d
 *   /  \			    /  \
 *  a    r			  node  c
 *     /  \                       /  \
 *    b    c			 a    b
 *
 * 左旋,以node->r之间的链为“支轴”进行,使r成为该新子树的根,node成为r的左孩子,而r的左孩子(b)则成为node的右孩子.
 * 算法很简单，还有注意一点，各个结点从左往右，不论是左旋前还是左旋后，结点大小都是从小到大。
-----------------------------------------------------------*/
static struct rb_node *rb_rotate_left(struct rb_node *node, struct rb_node *root)
{
	struct rb_node *right = node->right;

	//1. r的左孩子(b)成为node的右孩子
	node->right = right->left;
	if (right->left)
		rb_set_parent(right->left, node);	//node成为b的父节点

	//2. node成为r的左孩子
	right->left = node;

	//3. r成为node父节点的子节点
	rb_set_parent(right, rb_parent(node));
	if (node->parent)
		if (node == node->parent->right)
			node->parent->right = right;
		else
			node->parent->left = right;
	else
		root = right;	//node为根节点(parent==NULL)

	//4. r成为node的父节点
	rb_set_parent(node, right);

	return root;
}

/*-----------------------------------------------------------
 * 	 p				p
 *     /   \     right rotate         /   \
 *    d   node   ---------------->   d     l
 *        /  \			         /  \
 *       l    a			        b   node
 *      /  \                               /  \
 *     b    c			          c    a
-----------------------------------------------------------*/
static struct rb_node *rb_rotate_right(struct rb_node *node, struct rb_node *root)
{
	struct rb_node *left = node->left;

	//1. l的右孩子(c)成为node的左孩子
	node->left = left->right;
	if (left->right)
		rb_set_parent(left->right, node);	//node成为c的父节点

	//2. node成为l的右孩子
	left->right = node;

	//3. l成为node父节点的子节点
	rb_set_parent(left, rb_parent(node));
	if (node->parent)
		if (node == node->parent->right)
			node->parent->right = left;
		else
			node->parent->left = left;
	else
		root = left;	//node为根节点(parent==NULL)

	//4. l成为node的父节点
	rb_set_parent(node, left);

	return root;
}

/*
 * 红黑树修复插入的3种情况:
 * 1. 父节点为红色，叔节点为红色
 * 	调整步骤:
 * 	a. 改变父/叔节点颜色为黑色;
 * 	b. 将爷爷节点置红,这样在这个局部范围内,保持黑色平衡;
 * 	c. 将node置为爷爷节点.
 * 	如果x此时为根,则置x为黑色，调整结束，否则相当于又插入了一个红色节点，进行新一轮迭代。
 * 2. 父节点为红色，叔节点为黑色，左外侧插入
 * 	此时爷爷节点必为黑色。将父节点置为黑色，爷爷节点置为红色，这样，左边多了一个黑色节点，右旋将其降下来。
 * 	新插入节点为x，父节点为p，爷爷节点为g。
 * 3. 父节点为红色，叔节点为黑色，左内侧插入
 * 	此时，左旋，将其变成情况2，再由情况2的步骤进行插入。
 * */
static struct rb_node *rb_insert_rebalance(struct rb_node *node, struct rb_node *root)
{
	struct rb_node *parent, *gparent, *uncle, *tmp;

	parent = rb_parent(node);
	while (parent && rb_is_red(parent)) {
		gparent = rb_parent(parent);
		if (parent == gparent->left) {	//父结点为祖父节点的左孩子
			uncle = gparent->right;
			if (uncle && rb_is_red(uncle)) {	//情况1
				rb_set_black(uncle);
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
			} else {	//情况2
				if (parent->right == node) {	//node为右孩子
					root = rb_rotate_left(parent, root);	//当前结点作为新的俄当前结点,以新的当前结点为支点左旋
					tmp = parent;	//parent与node互换
					parent = node;
					node = tmp;
				}
				//情况3:由情况2变化而来
				rb_set_black(parent);
				rb_set_red(gparent);
				root = rb_rotate_right(gparent, root);	//右旋
			}
		} else if (parent == gparent->right) {	//父结点为祖父节点的右孩子,也分为3种情况,与上面类似
			uncle = gparent->left;
			if (uncle && rb_is_red(uncle)) {
				rb_set_black(uncle);
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
			} else {
				if (parent->left == node) {
					root = rb_rotate_right(parent, root);
					tmp = parent;
					parent = node;
					node = tmp;
				}
				rb_set_black(parent);
				rb_set_red(gparent);
				root = rb_rotate_left(gparent, root);
			}
		}
	}

	rb_set_black(root);	//根结点，不论怎样，都得置为黑色。

	return root;
}

/*
 * 删除可以概括为3种情况:
 * 	1. 情况说明:x是“红+黑”节点
 * 		处理方法：直接把x设为黑色，结束。此时红黑树性质全部恢复
 * 	2. 情况说明:x是“黑+黑”节点，且x是根
 * 		处理方法：什么都不做，结束.此时红黑树性质全部恢复
 * 	3. 情况说明:x是“黑+黑”节点，且x不是根
 * 		处理方法：这种情况又可以划分为4种子情况.这4种子情况如下表所示:
 * 		+-------------------------------------------------------+---------------------------------------+
 * 		| 现象说明						| 处理策略				|
 * 		+-------------------------------------------------------+---------------------------------------+
 * 		| Case 1						| (01) 将x的兄弟节点设为“黑色”		|
 * 		|	x是"黑+黑"节点,x的兄弟节点是红色 		| (02) 将x的父节点设为“红色”		|
 * 		|	(此时x的父节点和x的兄弟节点的子节点都是黑节点)	| (03) 对x的父节点进行左旋		|
 * 		|							| (04) 左旋后，重新设置x的兄弟节点	|
 * 		+-------------------------------------------------------+---------------------------------------+
 * 		| Case 2						| (01) 将x的兄弟节点设为“红色”		|
 * 		|	x是“黑+黑”节点,x的兄弟节点是黑色		| (02) 设置“x的父节点”为“新的x节点”	|
 * 		|	x的兄弟节点的两个孩子都是黑色			|					|
 * 		+-------------------------------------------------------+---------------------------------------+
 * 		| Case 3						| (01) 将x兄弟节点的左孩子设为“黑色”	|
 * 		|	x是“黑+黑”节点,x的兄弟节点是黑色		| (02) 将x兄弟节点设为“红色”		|
 * 		|	x的兄弟节点的左孩子是红色，右孩子是黑色的 	| (03) 对x的兄弟节点进行右旋		|
 * 		|							| (04) 右旋后，重新设置x的兄弟节点	|
 * 		+-------------------------------------------------------+---------------------------------------+
 * 		| Case 4						| (01) 将x父节点颜色 赋值给 x的兄弟节点	|
 * 		|	x是“黑+黑”节点,x的兄弟节点是黑色		| (02) 将x父节点设为“黑色”		|
 * 		|	x的兄弟节点的右孩子是红色的,			| (03) 将x兄弟节点的右子节设为“黑色”	|
 * 		|	x的兄弟节点的左孩子任意颜色			| (04) 对x的父节点进行左旋		|
 * 		|							| (05) 设置“x”为“根节点”		|
 * 		+-----------------------------------------------------------------------------------------------+
 * */
static struct rb_node *rb_erase_rebalance(struct rb_node *node, struct rb_node *parent, struct rb_node *root)
{
	struct rb_node *other, *o_left, *o_right;

	while ((!node || rb_is_black(node)) && node != root) {
		if (parent->left == node) {
			other = parent->right;

			if (rb_is_red(other)) {
				rb_set_black(other);
				rb_set_red(parent);
				root = rb_rotate_left(parent, root);other = parent->right;
			}

			if ((!other->left || rb_is_black(other->left)) &&
					(!other->right || rb_is_black(other->right))) {
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			} else {
				if (!other->right || rb_is_black(other->right)) {
					if ((o_left = other->left))
						rb_set_black(o_left);
					rb_set_red(other);
					root = rb_rotate_right(other, root);
					other = parent->right;
				}

				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);

				if (other->right)
					rb_set_black(other->right);

				root = rb_rotate_left(parent, root);
				node = root;

				break;
			}
		} else {
			other = parent->left;
			if (rb_is_red(other)) {
				rb_set_black(other);
				rb_set_red(parent);
				root = rb_rotate_right(parent, root);
				other = parent->left;
			}
			if ((!other->left || rb_is_black(other->left)) &&
					(!other->right || rb_is_black(other->right))){
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			} else {
				if (!other->left || rb_is_black(other->left)) {
					if ((o_right = other->right))
						rb_set_black(o_right);
					rb_set_red(other);
					root = rb_rotate_left(other, root);
					other = parent->left;
				}
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				if (other->left)
					rb_set_black(other->left);

				root = rb_rotate_right(parent, root);
				node = root;

				break;
			}
		}
	}

	if (node)
		rb_set_black(node);

	return root;
}

static struct rb_node *rb_search_auxiliary(key_t key, struct rb_node *root, struct rb_node** save)
{
	struct rb_node *node = root, *parent = NULL;
	int ret;

	while (node) {
		parent = node;

		ret = node->key - key;
		if (0 < ret)
			node = node->left;
		else if (0 > ret)
			node = node->right;
		else
			return node;
	}

	if (save)
		*save = parent;

	return NULL;
}

/*
 * 1. 查找要插入的位置,时间复杂度为:O(N)
 * 2. 将新节点的color赋为红色
 * 	如果设为黑色,就会导致根到叶子的路径上有一条路上,多一个额外的黑节点,这个是很难调整的.
 * 	但是设为红色节点后,可能会导致出现两个连续红色节点的冲突,那么可以通过颜色调换(color flips)和树旋转来调整
 * 3. 自下而上重新调整该树为红黑树
 * */
struct rb_node *rb_insert(key_t key, data_t data, struct rb_node *root)
{
	struct rb_node *parent = NULL, *node;

	if ((node = rb_search_auxiliary(key, root, &parent)))	//找到插入节点的位置
		return root;

	node = rb_new_node(key, data);	//分配节点
	rb_set_parent(node, parent);
	node->left = node->right = NULL;
	rb_set_red(node);

	if (parent)
		if (parent->key > key)
			parent->left = node;
		else
			parent->right = node;
	else
		root = node;

	return rb_insert_rebalance(node, root);	//修复红黑树的性质
}

struct rb_node *rb_search(key_t key, struct rb_node *root)
{
	return rb_search_auxiliary(key, root, NULL);
}

/*
 * 红黑树的删除
 *
 * 将红黑树内的某一个节点删除。需要执行的操作依次是:
 * 	1. 将红黑树当作一颗二叉查找树，将该节点从二叉查找树中删除;
 * 	2. 通过"旋转和重新着色"等一系列来修正该树，使之重新成为一棵红黑树
 * 详细描述如下:
 *
 * 第一步:将红黑树当作一颗二叉查找树,将节点删除, 这和"删除常规二叉查找树中删除节点的方法是一样的"
 * 分3种情况:
 * 	1. 被删除节点没有儿子，即为叶节点
 * 		直接将该节点删除就OK了。
 * 	2. 被删除节点只有一个儿子
 * 		直接删除该节点，并用该节点的唯一子节点顶替它的位置
 * 	3. 被删除节点有两个儿子
 * 		a. 先找出它的后继节点
 * 		b. 把“它的后继节点的内容”复制给“该节点的内容”;
 * 		c. 删除“它的后继节点”
 * 	在这里，后继节点相当于替身，在将后继节点的内容复制给"被删除节点"之后，再将后继节点删除。这样就巧妙的将问题转换为"删除后继节点"的情况了，下面就考虑后继节点。
 * 	在"被删除节点"有两个非空子节点的情况下，它的后继节点不可能是双子非空。既然"的后继节点"不可能双子都非空，
 * 	就意味着"该节点的后继节点"要么没有儿子，要么只有一个儿子。若没有儿子，则按"情况1"进行处理；若只有一个儿子，则按"情况2"进行处理。
 *
 * 第二步：通过"旋转和重新着色"等一系列来修正该树，使之重新成为一棵红黑树。
 * 	因为"第一步"中删除节点之后，可能会违背红黑树的特性。所以需要通过"旋转和重新着色"来修正该树，使之重新成为一棵红黑树。
 * */
struct rb_node *rb_erase(key_t key, struct rb_node *root)
{
	struct rb_node *child, *parent, *old, *node;
	enum rb_color color;

	node = rb_search_auxiliary(key, root, NULL);	//查找要删除的结点
	if (!node) {
		printf("key %d is not exist!\n");
		return root;
	}

	old = node;	//保存被删节点
	if (node->left && node->right) {	// 被删除节点的"左右孩子都不为空"的情况
		node = node->right;		//获取后继节点
		while (node->left != NULL)
			node = node->left;

		child = node->right;
		parent = node->parent;
		color = node->color;

		if (child)
			rb_set_parent(child, parent);

		if (parent)	//不是根结点(只有根结点没有父结点)
			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
		else	//是根结点
			root = child;

		if (rb_parent(node) == old)	// "被删除节点"是"它的后继节点的父节点"
			parent = node;

		rb_set_parent(node, rb_parent(old));
		rb_set_color(node, rb_color(old));
		node->right = old->right;
		node->left = old->left;

		if (rb_parent(old))
			if (rb_parent(old)->left == old)
				rb_parent(old)->left = node;
			else
				rb_parent(old)->right = node;
		else
			root = node;

		rb_set_parent(old->left, node);
		if (old->right)
			rb_set_parent(old->right, node);
	} else {
		if (!node->left)	//只有右孩子
			child = node->right;
		else if (!node->right)	//只有左孩子
			child = node->left;

		parent = node->parent;
		color = node->color;	// 保存"取代节点"的颜色

		if (child)
			rb_set_parent(child, parent);

		if (parent) {	// "node节点"不是根节点
			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
		} else
			root = child;
	}

	free(old);

	if (color == BLACK)
		root = rb_erase_rebalance(child, parent, root);

	return root;
}
