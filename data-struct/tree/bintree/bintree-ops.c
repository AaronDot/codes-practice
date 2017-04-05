/*
 *	Created on:	2015-07-02
 *	    Author:	Aaron Chou
 *
 *	    http://blog.csdn.net/column/details/dsaal.html
 * */

#include "bintree.h"
#include "queue.h"
#include "stack.h"

/*创建二叉树*/
void create_bintree(BinTree *proot)
{
	char ch;

	scanf("\n%c", &ch);
	if (ch == '#') {
		*proot = NULL;
	} else {
		*proot = (BinTree)malloc(sizeof(BinTnode));
		(*proot)->data->elem = ch;
		printf("please input the %c's left child:", ch);
		create_bintree(&((*proot)->lchild));
		printf("please input the %c's right child:", ch);
		create_bintree(&((*proot)->rchild));
	}
}

/*
 * 前序遍历-->递归方式
 * */
void preorder_recursive(BinTree proot)
{
	if (proot == NULL)
		return;

	printf("%c ", proot->data->elem);
	preorder_recursive(proot->lchild);
	preorder_recursive(proot->rchild);
}

/*
 * 前序遍历-->非递归方式
 * 遍历思想:
 * 	先让根进栈,只要栈不为空,就可以做弹出操作.每次弹出一个结点,记得把它的左右结点都进栈,记得右子树先进栈,这样可以保证右子树在栈中总处于左子树的下面.
 * */
void preorder_nonrecursive(BinTree proot)
{
	struct LinkStack *bintree_stack;
	BinTree curr = NULL;

	if (proot == NULL)
		return;

	init_stack(&bintree_stack);
	push_stack(bintree_stack, proot);

	while (!empty_stack(bintree_stack)) {
		pop_stack(bintree_stack, &curr);
		if (curr != NULL) {
			printf("%c ", curr->data->elem);
			push_stack(bintree_stack, curr->rchild);
			push_stack(bintree_stack, curr->lchild);
		}
	}
}

/*
 * 第一步:首先判断树proot是否为空,若不为空,则进行第二步;若为空,则进行第三步
 * 第二步:访问proot,然后将proot入栈,将proot左结点赋给proot,然后对新proot进行第一步
 * 第三步:判断栈是否为空,如果不为空,则取出栈顶元素,并出栈,然后将栈顶元素的右结点赋给proot,然后进行第一步;如果proot为NULL并且栈空,则结束
 * */
void preorder_nonrecursive_2(BinTree proot)
{
	struct LinkStack *bintree_stack;
	BinTree curr = NULL;

	if (proot == NULL)
		return;

	init_stack(&bintree_stack);
	curr = proot;
	while (curr != NULL || !empty_stack(bintree_stack)) {
		while (curr != NULL) {
			printf("%c ", curr->data->elem);
			push_stack(bintree_stack, curr);
			curr = curr->lchild;
		}
		if (!empty_stack(bintree_stack)) {
			pop_stack(bintree_stack, &curr);
			curr = curr->rchild;
		}
	}
}

void preorder_nonrecursive_3(BinTree proot)
{
	struct LinkStack *bintree_stack;
	BinTree curr = NULL;	/*栈顶元素的右子树*/

	if (proot == NULL)
		return;

	init_stack(&bintree_stack);
	while (proot) {
		push_stack(bintree_stack, proot);
		printf("%c ", proot->data->elem);
		proot = proot->lchild;
	}

	while (!empty_stack(bintree_stack)) {
		pop_stack(bintree_stack, &curr);	/*弹出栈顶元素*/
		curr = curr->rchild;
		/*栈顶元素存在右子树，则对右子树同样遍历到最下方*/
		while (curr) {
			printf("%c ", curr->data->elem);
			push_stack(bintree_stack, curr);
			curr = curr->lchild;
		}
	}
}

/*
 * 中序遍历-->递归方式
 * */
void inorder_recursive(BinTree proot)
{
	if (proot == NULL)
		return;

	inorder_recursive(proot->lchild);
	printf("%c ", proot->data->elem);
	inorder_recursive(proot->rchild);
}

/*
 * 中序遍历-->非递归方式
 * */
void inorder_nonrecursive(BinTree proot)
{
	struct LinkStack *bintree_stack;
	BinTree curr = NULL;

	if (proot == NULL)
		return;

	init_stack(&bintree_stack);
	push_stack(bintree_stack, proot);

	while (!empty_stack(bintree_stack)) {
		while ((top_stack(bintree_stack, &curr) != 0) && curr)
			push_stack(bintree_stack, curr->lchild);

		pop_stack(bintree_stack, &curr);
		if (!empty_stack(bintree_stack)) {
			pop_stack(bintree_stack, &curr);
			printf("%c ",  visit(curr));
			push_stack(bintree_stack, curr->rchild);
		}
	}
}

/*
 * 第一步：给定根节点proot，判断proot是否为空，如果不为空，然后进行第二步；如果为空，则进行第三步；
 * 第二步：将proot入栈，将proot的左结点赋给proot，然后进行第一步；
 * 第三步：判断栈是否为空；如果为空，则结束，如果不为空，则取出栈顶元素给proot，并出栈，访问proot，然后将proot的右结点赋给proot，然后进行第一步。*/
void inorder_nonrecursive_2(BinTree proot)
{
	struct LinkStack *bintree_stack;
	BinTree curr = NULL;

	if(proot == NULL)
		return;

	init_stack(&bintree_stack);
	/*指向当前要检查的节点*/
	curr = proot;
	while (curr != NULL || !empty_stack(bintree_stack)) {
		while (curr != NULL) {
			push_stack(bintree_stack, curr);
			curr = curr->lchild;
		}
		if (!empty_stack(bintree_stack)) {
			pop_stack(bintree_stack, &curr);
			printf("%c ", curr->data->elem);
			curr = curr->rchild;
		}
	}
}

void inorder_nonrecursive_3(BinTree proot)
{
	struct LinkStack *bintree_stack;
	BinTree curr = NULL;

	if(proot == NULL)
		return;

	init_stack(&bintree_stack);
	/*指向当前要检查的节点*/
	curr = proot->lchild;
	push_stack(bintree_stack, proot);
	while (curr != NULL || !empty_stack(bintree_stack)) {
		/* 一直向左走*/
		while (curr != NULL) {
			push_stack(bintree_stack, curr);
			curr = curr->lchild;
		}
		pop_stack(bintree_stack, &curr);
		printf("%c ", curr->data->elem);
		curr = curr->rchild;
	}
}

/*
 * 后序遍历-->递归方式
 * */
void postorder_recursive(BinTree proot)
{
	if (proot == NULL)
		return;

	postorder_recursive(proot->lchild);
	postorder_recursive(proot->rchild);
	printf("%c ", proot->data->elem);
}

/*
 * 后序遍历-->非递归方式
 * */
void postorder_nonrecursive(BinTree proot)
{
	struct LinkStack *bintree_stack;
	BinTree curr, tmp;

	init_stack(&bintree_stack);
	curr = proot;

	while (curr || !empty_stack(bintree_stack)) {
		if (curr != tmp) {
			while (curr != NULL) {
				push_stack(bintree_stack, curr);
				if (curr->lchild != NULL)
					curr = curr->lchild;
				else
					curr = curr->rchild;
			}
		}
		if (empty_stack(bintree_stack))
			break;
		top_stack(bintree_stack, &tmp);
		if (tmp->rchild == curr) {
			pop_stack(bintree_stack, &curr);
			printf("%c ", visit(curr));
			curr = tmp;
		} else {
			curr = tmp->rchild;
		}
	}
}

/*
 * 第一步：给定proot，判断proot是否为NULL；如果不为NULL，执行第二步；如果为NULL，执行第三步；
 * 第二步：将proot入栈，并将proot的左结点赋给proot，执行第一步；
 * 第三步：如果栈不为空，则将栈顶元素赋给proot，判断proot是否有右子树以及右子树是否访问过；如果没有右子树或者已经访问过右子树，则访问proot并出栈，然后执行第一步；如果有右子树并且右子树还没有访问过，则将proot右结点赋给proot，然后执行第一步。
 * */
void postorder_nonrecursive_2(BinTree proot)
{
	struct LinkStack *bintree_stack;
	BinTree curr = NULL;		/*指向当前要检查的节点*/
	BinTree prev = NULL;		/*指向前一个被访问的节点*/

	init_stack(&bintree_stack);
	curr = proot ;

	while (curr != NULL || !empty_stack(bintree_stack)) {  // 栈空时结束
		while (curr != NULL) {          // 一直向左走直到为空
			push_stack(bintree_stack, curr);
			curr = curr->lchild;
		}
		top_stack(bintree_stack, &curr);
		// 当前节点的右孩子如果为空或者已经被访问，则访问当前节点
		if (curr->rchild == NULL || curr->rchild == prev) {
			printf("%c ", curr->data->elem);
			prev = curr;
			pop_stack(bintree_stack, &curr);
			curr = NULL;
		} else {
			curr = curr->rchild;      // 否则访问右孩子
		}
	}
}

/*
 * 首先将根节点proot入栈1
 * 步骤一:将栈1的栈顶元素赋给proot,然后将proot入栈2;然后先将proot左结点入栈1,后将proot右结点入栈1,顺序一定不能错
 * 步骤二:出栈2,就获得后序遍历
 * */
void postorder_nonrecursive_3(BinTree proot)  // 后序遍历的非递归     双栈法
{
	struct LinkStack *stack_first, *stack_second;
	BinTree curr, tmp;           // 指向当前要检查的节点

	init_stack(&stack_first);
	init_stack(&stack_second);

	push_stack(stack_first, proot);
	while (!empty_stack(stack_first)) {  // 栈空时结束
		pop_stack(stack_first, &curr);
		push_stack(stack_second, curr);
		if (curr->lchild)
			push_stack(stack_first, curr->lchild);
		if (curr->rchild)
			push_stack(stack_first, curr->rchild);
	}
	while (!empty_stack(stack_second)) {
		top_stack(stack_second, &tmp);
		printf("%c ", tmp->data->elem);
		pop_stack(stack_second, &tmp);
	}
}

/*
 * 后序遍历由于遍历父节点是在遍历子节点之后，而且左节点和右节点遍历后的行为不一样
 * 所以需要用变量来记录前一次访问的节点，根据前一次节点和现在的节点的关系来确定具体执行什么操作
 * */
void postorder_nonrecursive_4(BinTree proot)
{
	struct LinkStack *bintree_stack;
	BinTree prev = NULL, curr = NULL;

	if (proot == NULL)
		return;

	init_stack(&bintree_stack);

	push_stack(bintree_stack, proot);
	while (!empty_stack(bintree_stack)) {
		top_stack(bintree_stack, &curr);
		if (prev == NULL || prev->lchild == curr || prev->rchild == curr) {
			if(curr->lchild != NULL)
				push_stack(bintree_stack, curr->lchild);
			else if(curr->rchild != NULL)
				push_stack(bintree_stack, curr->rchild);
		} else if (curr->lchild == prev) {
			if (curr->rchild != NULL)
				push_stack(bintree_stack, curr->rchild);
		} else {
			printf("%c ", curr->data->elem);
			pop_stack(bintree_stack, &curr);
		}
		prev = curr;
	}
}

/*
 * 层次遍历-->非递归方式
 * */
void layerorder_nonrecursive(BinTree proot)
{
	LinkQueue bintree_queue;	/*队列tq*/
	BinTree curr;			/*用来返回对头元素*/

	init_queue(&bintree_queue);		/*创建队列*/
	push_queue(&bintree_queue, proot);		/*将proot插入队尾*/
	while (pop_queue(&bintree_queue, &curr) == 1) {		/*当队头元素不空时执行while循环*/
		if (curr) {
			printf("%c ", curr->data->elem);		/*访问队头元素*/
			push_queue(&bintree_queue, curr->lchild);		/*将结点左孩子插入队尾*/
			push_queue(&bintree_queue, curr->rchild);		/*将结点右孩子插入队尾*/
		}
	}
}

void layerorder_nonrecursive_2(BinTree proot)
{
	LinkQueue bintree_queue;	/*队列tq*/
	BinTree curr;			/*用来返回对头元素*/

	init_queue(&bintree_queue);		/*创建队列*/
	curr = proot;
	if (curr != NULL)
		push_queue(&bintree_queue, curr);

	while (!empty_queue(bintree_queue)) {
		pop_queue(&bintree_queue, &curr);
		printf("%c ", curr->data->elem);         /*访问队头元素*/
		if (curr->lchild != NULL)
			push_queue(&bintree_queue, curr->lchild);
		if (curr->rchild != NULL)
			push_queue(&bintree_queue, curr->rchild);
	}
}

/*
 * 第一步:需要借助队列,首先将根节点proot入队
 * 第二步:当队列不空时,获得队首元素并出队，赋给proot，执行第三步
 * 第三步:如果proot左节点存在，则入队；如果proot右节点存在，则入队；执行第二步
 * */
void layerorder_nonrecursive_3(BinTree proot)     //方法二、非递归层次遍历二叉树
{
	LinkQueue bintree_queue;		/*队列tq*/
	BinTree curr;

	if (proot == NULL)
		return;

	init_queue(&bintree_queue);		/*创建队列*/
	push_queue(&bintree_queue, proot);		/*将proot插入队尾*/

	while (pop_queue(&bintree_queue, &curr) == 1) { //如果队尾指针不等于对头指针时
		printf("%c ", curr->data->elem);
		if(curr->lchild != NULL)  //将队首结点的左孩子指针入队列
			push_queue(&bintree_queue, curr->lchild);		/*将结点左孩子插入队尾*/
		if(curr->rchild != NULL)
			push_queue(&bintree_queue, curr->rchild);		/*将结点右孩子插入队尾*/
	}
}

int bintree_depth(BinTree proot)   //树的深度
{
	int ldepth, rdepth;

	if (proot == NULL)
		return 0;

	ldepth = bintree_depth(proot->lchild);
	rdepth = bintree_depth(proot->rchild);

	return ((ldepth > rdepth ? ldepth : rdepth) + 1);
}

int bintree_node(BinTree proot)
{
	if (proot == NULL)
		return 0;

	return (bintree_node(proot->lchild) + bintree_node(proot->rchild) + 1);
}

/*
 * 求二叉树叶子节点数
 * 1.递归方式
 * 如果给定节点proot为NULL，则是空树，叶子节点为0，返回0；
 * 如果给定节点proot左右子树均为NULL，则是叶子节点，且叶子节点数为1，返回1；
 * 如果给定节点proot左右子树不都为NULL，则不是叶子节点，以proot为根节点的子树叶子节点数=proot左子树叶子节点数+proot右子树叶子节点数
 * 2.非递归方式
 * 在遍历二叉树时，判断当前访问的节点是不是叶子节点，然后对叶子节点求和即可。
 * */
int bintree_total_leafnode(BinTree proot)
{
	if (proot == NULL)
		return 0;

	if (proot->lchild == NULL && proot->rchild == NULL)
		return 1;

	return (bintree_total_leafnode(proot->lchild) + bintree_total_leafnode(proot->rchild));
}

/*
 * 求二叉树第K层的节点数
 * （1）递归方式：
 * 给定根节点proot：
 * 如果proot为空，或者层数kth_level <= 0，则为空树或者不合要求，则返回0；
 * 如果proot不为空，且此时层数kth_level==1，则此时proot为第K层节点之一，则返回1；
 * 如果proot不为空，且此时层数kth_level > 1，则此时需要求proot左子树（kth_level - 1 ）层节点数和proot右子树（kth_level-1）层节点数；
 * */
int bintree_kthlevel_node(BinTree proot, int kth_level)
{
	if (proot == NULL || kth_level <= 0)
		return 0;

	if (proot != NULL && kth_level == 1)
		return 1;

	return (bintree_kthlevel_node(proot->lchild, kth_level - 1) + bintree_kthlevel_node(proot->rchild, kth_level - 1));
}

/*
 * （2）非递归方式
 * 借助队列实现：
 * */
int bintree_kthlevel_node_nonrecursive(BinTree proot, int kth_level)
{
	LinkQueue bintree_queue;		/*队列tq*/
	int cur_level_node = 0;
	int cur_level = 0;
	int cnt_node = 0;
	BinTree curr;

	if (proot == NULL)
		return 0;

	init_queue(&bintree_queue);		/*创建队列*/
	push_queue(&bintree_queue, proot);		/*将proot插入队尾*/

	while (!empty_queue(bintree_queue)) {
		++cur_level;	/*当前层数*/
		cur_level_node = length_queue(bintree_queue);
		if (cur_level == kth_level)	/*如果层数等于给定层数*/
			break;

		/*将下一层节点入队*/
		while (cnt_node < cur_level_node) {
			++cnt_node;
			pop_queue(&bintree_queue, &proot);
			if (proot->lchild != NULL)
				push_queue(&bintree_queue, proot->lchild);
			if (proot->rchild != NULL)
				push_queue(&bintree_queue, proot->rchild);
		}
	}

	while (!empty_queue(bintree_queue))
		pop_queue(&bintree_queue, &curr);

	if (cur_level == kth_level)
		return cur_level_node;

	return 0;  /*如果kth_level大于树的深度*/
}

/*
 * 3、求二叉树第K层叶子节点数
 * （1）递归方式
 * 给定节点proot：
 * 如果proot为空，或者层数kth_level <= 0, 则为空树或者是层数非法，则返回0；
 * 如果proot不为空，且此时层数kth_level==1时，需要判断是否为叶子节点：
 *     如果proot左右子树均为空，则proot为第K层叶子节点之一，则返回1；
 *         如果proot左右子树之一存在，则proot不是叶子节点，则返回0；
 *         如果proot不为空，且此时层数kth_level > 1，需要返回 kth_level-1层的左子树和右子树结点数。
 * */
int bintree_kthlevel_leafnode(BinTree proot, int kth_level)
{
	if (proot == NULL || kth_level <= 0)
		return 0;

	if (proot != NULL && kth_level == 1) {
		if (proot->lchild == NULL && proot->rchild == NULL)
			return 1;
		else
			return 0;
	}

	return (bintree_kthlevel_leafnode(proot->lchild, kth_level - 1) + bintree_kthlevel_leafnode(proot->rchild, kth_level -1));
}

/*
 * （2）非递归方式
 * 借助队列实现
 * */
int bintree_kthlevel_leafnode_nonrecursive(BinTree proot, unsigned int kth_level)
{
	LinkQueue bintree_queue;
	int cur_level_node = 0;
	int cur_level = 0;
	int cnt_node = 0;
	int leaf_nodes = 0;

	if(proot == NULL)
		return 0;

	init_queue(&bintree_queue);		/*创建队列*/
	push_queue(&bintree_queue, proot);		/*将proot插入队尾*/

	while (!empty_queue(bintree_queue)) {
		++cur_level;//当前层数
		cur_level_node = length_queue(bintree_queue);
		if (cur_level == kth_level)//如果层数等于给定层数
			break;

		while (cnt_node < cur_level_node) {//将下一层节点入队
			++cnt_node;
			pop_queue(&bintree_queue, &proot);
			if (proot->lchild != NULL)
				push_queue(&bintree_queue, proot->lchild);
			if (proot->rchild != NULL)
				push_queue(&bintree_queue, proot->rchild);
		}
	}

	if (cur_level == kth_level) {
		cnt_node = 0;
		while (cnt_node < cur_level_node) {
			++cnt_node;
			pop_queue(&bintree_queue, &proot);

			if (proot->lchild == NULL && proot->rchild == NULL)
				leaf_nodes++;
		}
		return leaf_nodes; //返回叶子节点数
	}

	return 0;  //如果kth_level大于树的深度
}

/*
 * 求二叉树中第K层的第M个节点
 * 借助队列实现
 * 首先将给定根节点proot入队：
 * 第一步：如果队列未空，获取当前队列的长度，即当前层的节点总数；
 * 第二步：记录当前遍历的层数，判断是否超出指定层数，如果超出则退出；如果小于指定层数，则对当前层的所有左右节点入队操作；如果等于指定 层数，则进行第三步；
 * 第三步：获取当前队列中节点总数，如果当前节点总数小于指定节点数，则退出；如果节点总数大于指定节点数，则进行第四步；
 * 第四步：遍历当前层节点，如果节点数等于指定节点数，则放回此节点。
 * 第三步：循环结束后，如果没有符合条件的节点就返回NULL。
 * */
BinTree bintree_kthlevel_mthnode(BinTree proot, int kth_level, int mth_node)
{
	LinkQueue bintree_queue;
	int cur_level = 0;      //当前层计数器
	int cnt_node = 0;   //当前层节点数计数器
	int cur_level_node = 0;//当前层节点总数
	BinTree curr;


	if (proot == NULL || kth_level <= 0 || mth_node <= 0)
		return NULL;

	init_queue(&bintree_queue);		/*创建队列*/
	push_queue(&bintree_queue, proot);		/*将proot插入队尾*/

	while (!empty_queue(bintree_queue)) {
		++cur_level;
		if (cur_level > kth_level)//如果层数已大于指定层数，则退出
			break;

		cnt_node = 0; //当前层节点数计数器归0
		cur_level_node = length_queue(bintree_queue);//当前层的节点总数
		while (cnt_node < cur_level_node) {
			++cnt_node;//记录当前层的节点数
			pop_queue(&bintree_queue, &proot);

			if (cur_level == kth_level && cnt_node == mth_node)//看当前节点的层数和在当前层中的节点次序是否符合要求
				break;

			//将当前层节点的左右结点均入队，即将下一层节点入队
			if (proot->lchild != NULL)
				push_queue(&bintree_queue, proot->lchild);
			if (proot->rchild != NULL)
				push_queue(&bintree_queue, proot->rchild);
		}

		if (cur_level == kth_level && cnt_node == mth_node) //看当前节点的层数和在当前层中的节点次序是否符合要求
			break;
	}
	while (!empty_queue(bintree_queue))//清空栈
		pop_queue(&bintree_queue, &curr);

	if (cur_level == kth_level && cnt_node == mth_node) //看当前节点的层数和在当前层中的节点次序是否符合要求
		return proot;

	return NULL;
}

/*
 * 2、比较两个二叉树结构是否相同，不涉及存储的数据
 * （1）递归方式
 * 如果两个二叉树proot都为空树，则自然相同，返回true；
 * 如果两个二叉树proot一个为空树，另一个不为空树，则不相同，返回false；
 * 如果两个二叉树都不为空树，则需要分别比较左右子树后，根据比较结果共同判定，只要有一个为false，则返回false。
 * */
int bintree_structure_compare(BinTree proot1, BinTree proot2)
{
	int left_tree, right_tree;

	//如果都为空树，则相同
	if (proot1 == NULL && proot2 == NULL)
		return 1;
	//如果一个为空，一个不为空，则不相同
	if ((proot1 != NULL && proot2 == NULL) ||
			(proot1 == NULL && proot2 != NULL))
		return 0;
	//如果都不为空，则 需要比较左右子树后，再根据比较结果断定
	left_tree = bintree_structure_compare(proot1->lchild, proot2->lchild);
	right_tree = bintree_structure_compare(proot1->rchild, proot2->rchild);

	return (left_tree && right_tree);
}

/*
 * （2）非递归方式
 * 借助队列实现
 * 实现算法：
 * 首先将给定根节点proot1和proot2都入队
 * 第一步：当两个队列未空时，分别获取两个树的当前层次中节点总数（即当前队列中节点个数），先比较节点个数是否相同，如果不相同，则两个树自然不同；如果节点个数相同，需要出队进行比较。如果有一个队列未空，则退出比较。
 * 第二步：如果有一个队列未空，则清空队列并返回不同。
 * */
int bintree_structure_compare_nonrecursive(BinTree proot1, BinTree proot2)
{
	LinkQueue bintree1_queue, bintree2_queue;
	BinTree curr1, curr2;
	int cur_level_node_root1 = 0;
	int cur_level_node_root2 = 0;
	int flag = 1; //作为比较不一致时跳出标识
	int cnt_root1 = 0;//遍历本层节点时的计数器
	int cnt_root2 = 0;

	if (proot1 == NULL && proot2 == NULL)
		return 0;

	init_queue(&bintree1_queue);
	init_queue(&bintree2_queue);
	push_queue(&bintree1_queue, proot1);
	push_queue(&bintree2_queue, proot2);

	while ((!empty_queue(bintree1_queue)) && (!empty_queue(bintree2_queue))) { //当两个队列均不为空时，才进行比较
		cur_level_node_root1 = length_queue(bintree1_queue);  //获取树1的当前层节点总数
		cur_level_node_root2 = length_queue(bintree2_queue); //获取树2的当前层节点总数
		if (cur_level_node_root1 != cur_level_node_root2) {
			flag = 0;//当前层节点总数都不一致，不需要比较了，直接跳出
			break;
		}

		cnt_root1 = cnt_root2 = 0;
		while ((cnt_root1 < cur_level_node_root1)  && (cnt_root2 < cur_level_node_root2)) {
			++cnt_root1;
			++cnt_root2;
			pop_queue(&bintree1_queue, &proot1);
			pop_queue(&bintree2_queue, &proot2);

			//判断proot1和proot2左右节点结构是否相同
			if ((proot1->lchild != NULL && proot2->lchild == NULL) || (proot1->lchild == NULL && proot2->lchild != NULL) ||
					(proot1->rchild != NULL && proot2->rchild == NULL) || (proot1->rchild == NULL && proot2->rchild != NULL)) {
				flag = 0;
				break;
			}

			//将左右节点入队
			if (proot1->lchild != NULL)
				push_queue(&bintree1_queue, proot1->lchild);
			if (proot1->rchild != NULL)
				push_queue(&bintree1_queue, proot1->rchild);
			if (proot2->lchild != NULL)
				push_queue(&bintree2_queue, proot2->lchild);
			if (proot2->rchild != NULL)
				push_queue(&bintree2_queue, proot2->rchild);
		}

		if (flag == 0)
			break;
	}

	//如果比较标志为false，则不相同
	if (flag == 0) {
		while(!empty_queue(bintree1_queue))
			pop_queue(&bintree1_queue, &curr1);
		while(!empty_queue(bintree2_queue))
			pop_queue(&bintree2_queue, &curr2);
		return 0;
	}

	return 1;
}

/*
 * 3、比较两个二叉树结构和数据是否同时相同，即两个一模一样的树
 * 与上面的不同之处在于：在比较结构是否相同之后，需要比较当前节点的数据是否一致。
 * 算法是一致的，只需要添加一行代码即可。
 * （1）递归方式：
 * */
int bintree_all_compare(BinTree proot1, BinTree proot2)
{
	int left_root, right_root;

	//如果都为空树，则相同
	if (proot1 == NULL && proot2 == NULL)
		return 1;
	//如果一个为空，一个不为空，则不相同
	if ((proot1 != NULL && proot2 == NULL) ||
			(proot1 == NULL && proot2 != NULL))
		return 0;
	//比较当前节点中的数据
	if (proot1->data->elem != proot2->data->elem)
		return 0;
	//如果都不为空，则 需要比较左右子树后，再根据比较结果断定
	left_root = bintree_all_compare(proot1->lchild, proot2->lchild);
	right_root = bintree_all_compare(proot1->rchild, proot2->rchild);

	return (left_root && right_root);
}

int bintree_all_compare_nonrecursive(BinTree proot1, BinTree proot2)
{
	LinkQueue bintree1_queue, bintree2_queue;
	BinTree curr1, curr2;
	int cur_level_node_root1 = 0, cur_level_node_root2 = 0;
	int flag = 1; //作为比较不一致时跳出标识
	int cnt_root1 = 0, cnt_root2 = 0;//遍历本层节点时的计数器

	if (proot1 == NULL && proot2 == NULL)
		return 0;

	init_queue(&bintree1_queue);
	init_queue(&bintree2_queue);
	push_queue(&bintree1_queue, proot1);
	push_queue(&bintree2_queue, proot2);

	while ((!empty_queue(bintree1_queue)) && (!empty_queue(bintree2_queue))) { //当两个队列均不为空时，才进行比较
		cur_level_node_root1 = length_queue(bintree1_queue);  //获取树1的当前层节点总数
		cur_level_node_root2 = length_queue(bintree2_queue); //获取树2的当前层节点总数
		if (cur_level_node_root1 != cur_level_node_root2) {
			flag = 0;//当前层节点总数都不一致，不需要比较了，直接跳出
			break;
		}

		cnt_root1 = cnt_root2 = 0;
		while (cnt_root1 < cur_level_node_root1  && cnt_root2 < cur_level_node_root1) {
			++cnt_root1;
			++cnt_root2;
			pop_queue(&bintree1_queue, &proot1);
			pop_queue(&bintree2_queue, &proot2);

			//比较当前节点中数据是否一致
			if (proot1->data->elem != proot2->data->elem) {
				flag = 0;
				break;
			}
			//判断proot1和proot2左右节点结构是否相同
			if (( proot1->lchild != NULL && proot2->lchild == NULL) || (proot1->lchild == NULL && proot2->lchild != NULL) ||
					(proot1->rchild != NULL && proot2->rchild == NULL) ||(proot1->rchild == NULL && proot2->rchild != NULL)) {
				flag = 0;
				break;
			}

			//将左右节点入队
			if (proot1->lchild != NULL)
				push_queue(&bintree1_queue, proot1->lchild);
			if (proot1->rchild != NULL)
				push_queue(&bintree1_queue, proot1->rchild);
			if (proot2->lchild != NULL)
				push_queue(&bintree2_queue, proot2->lchild);
			if (proot2->rchild != NULL)
				push_queue(&bintree2_queue, proot2->rchild);
		}
		if (flag == 0)
			break;
	}

	//如果比较标志为false，则不相同
	if (flag == 0) {
		while(!empty_queue(bintree1_queue))
			pop_queue(&bintree1_queue, &curr1);
		while(!empty_queue(bintree2_queue))
			pop_queue(&bintree2_queue, &curr2);
		return 0;
	}

	return 1;
}

/*
 * 二叉树镜像
 * (1)递归方式
 * 如果proot为NULL，则为空树，返回；
 * 如果proot不为NULL，交换proot左右结点，然后分别求左右子树的镜像；
 * */
BinTree bintree_mirror(BinTree proot)
{
	BinTree mirror;

	if (proot == NULL)
		return NULL;

	mirror = proot->lchild;
	proot->lchild = proot->rchild;
	proot->rchild = mirror;

	bintree_mirror(proot->lchild);
	bintree_mirror(proot->rchild);

	return proot;
}

/*
 * (2)非递归方式
 * 步骤描述：借助队列
 * 首先，将根节点proot入队；
 * 第一步：当队列未空时，获取当前层次的节点总数，即当前队列的长度；执行第二步；
 * 第二步：按照当前层的节点总数，出队进行遍历节点，在遍历时，交换左右节点，如果左右节点存在，则入队；当遍历完当前层所有节点时，遍历下一层，执行第一步。
 * */
BinTree bintree_mirror_nonrecursive(BinTree proot)
{
	LinkQueue bintree_queue;
	BinTree temp;
	int cur_level_node_root = 0;
	int cnt_node = 0;

	if (proot == NULL)
		return NULL;

	init_queue(&bintree_queue);
	push_queue(&bintree_queue, proot);

	while (!empty_queue(bintree_queue)) {
		cur_level_node_root = length_queue(bintree_queue);
		cnt_node = 0;
		while (cnt_node < cur_level_node_root) {
			++cnt_node;
			pop_queue(&bintree_queue, &proot);
			temp = proot->lchild;
			proot->lchild = proot->rchild;
			proot->rchild = temp;

			if (proot->lchild != NULL)
				push_queue(&bintree_queue, proot->lchild);
			if (proot->rchild != NULL)
				push_queue(&bintree_queue, proot->rchild);
		}
	}

	return proot;
}

int compare(struct BinTreeNode *node1, struct BinTreeNode *node2)
{
	if (node1->elem == node2->elem)
		return 0;
	else
		return -1;
}

/*
 * 二、根据前序遍历序列和中序遍历序列重建二叉树
 * 算法说明：
 * 由中序遍历序列可知，第一个节点是根节点，
 * 由前序遍历序列可知，第一个节点是根节点的左子树节点，而且前序遍历中，根节点左边是左子树，右边是右子树，因此通过中序遍历的根节点可以确定的是：
 * 根节点在前序遍历中的位置（通过遍历前序遍历序列，比较每一个节点与中序遍历中的第一个节点即根节点可知）；
 * 左子树的节点数，因为一旦找到前序遍历中根节点的位置，就找到左右子树的分界点，也就是说，前序遍历中根节点左边的都是左子树节点，可以通过遍历知道左子树的节点数；
 * 同样，右子树的节点数也可以确定。
 * 通过以上确定的信息，可以划分出前序遍历中的左右子树节点数，根节点位置；因此，下面就是进行求根节点左节点和右节点，而根据上述划分，可以知道左子树前序和中序序列起始位置以及长度、右子树前序和中序序列起始位置以及长度，这样可以递归按照上述方式同样获得左右子树的根节点。
 * 通过递归可以求得整个树的结构。
 * */
BinTree rebuild_bintree_pre(char *pre_order, char *in_order, int nodes_total)
{
	BinTree proot = NULL;
	char *left_preorder, *left_inorder, *right_preorder, *right_inorder;
	int left_nodes_total, right_nodes_total; //由根节点索引可以确定左右子树的长度，因为中序遍历根节点作为左右子树的分隔点
	char root_node;
	int root_index = -1, i;

	if (pre_order == NULL || in_order == NULL || nodes_total <= 0)
		return NULL;

	proot = (BinTree)malloc(sizeof(BinTnode));
	proot->data = (struct BinTreeNode *)malloc(sizeof(struct BinTreeNode));
	if (proot == NULL)
		return NULL;

	root_node = *pre_order;  //找到当前树的根节点
	proot->data->elem = root_node;
	for (i = 0; i < nodes_total; ++i) {
		if (root_node == *(in_order + i)) {
			root_index = i;
			break;
		}
	}

	if (root_index == -1)
		return NULL;

	//根据查找到根节点得到的信息，左子树长度，右子树长度等
	left_nodes_total = root_index;
	left_preorder = pre_order + 1;
	left_inorder = in_order;
	proot->lchild = rebuild_bintree_pre(left_preorder, left_inorder, nodes_total);

	//右子树信息
	right_nodes_total = nodes_total - left_nodes_total - 1;//减去右子树节点数和一个根节点
	right_preorder = pre_order + left_nodes_total + 1;
	right_inorder = in_order + left_nodes_total + 1;
	proot->rchild = rebuild_bintree_pre(right_preorder, right_inorder, right_nodes_total);

	return proot;
}

/*
 * 2、由中序遍历和后序遍历重建二叉树
 * 中序遍历中，根节点总是位于左右子树中间，将左右子树分开。
 * 后序遍历中，根节点总是在左右子树之后。
 * 重建算法：
 * 现在说一下重建根节点的过程，其他节点可以递归建立。
 * 由后序遍历定义可知，后序遍历序列的最后一个元素必定是整个树的根节点，这样就确定了根节点。
 * 由中序遍历定义可知，在中序遍历中查找根节点，可以确定根节点在中序遍历序列中位置，这样就可以将中序遍历序列分为左右子树，一旦确定左右子树，左右子树的长度也就确定了，根据左右子树的长度，在后序遍历序列中，可以确定左右子树的根节点，这样递归下去既可以确定整个树。
 * */
BinTree rebuild_bintree(char *in_order, char *post_order, int nodes_total)
{
	BinTree proot = NULL;
	char *left_postorder, *left_inorder, *right_postorder, *right_inorder;
	int left_nodes_total, right_nodes_total;	/*由根节点索引可以确定左右子树的长度，因为中序遍历根节点作为左右子树的分隔点*/
	int root_index = -1, i;
	char root_node;

	if (in_order == NULL || post_order == NULL || nodes_total <= 0)
		return NULL;

	proot = (BinTree)malloc(sizeof(BinTnode));
	proot->data = (struct BinTreeNode *)malloc(sizeof(struct BinTreeNode));
	if (proot == NULL)
		return NULL;

	root_node = *(post_order + nodes_total - 1);	/*后序遍历序列的最后一个值是根节点*/
	proot->data->elem = root_node;

	for (i = 0 ; i < nodes_total; i++) {
		if (*(in_order + i) == root_node) {
			root_index = i;
			break;
		}
	}

	if (root_index == -1)
		return NULL;

	left_nodes_total = root_index;
	left_postorder = post_order;
	left_inorder = in_order;
	proot->lchild = rebuild_bintree(left_inorder, left_postorder, left_nodes_total);

	right_nodes_total = nodes_total - left_nodes_total - 1;
	right_postorder = post_order + left_nodes_total;	/*确定了左右子树的长度，也就确定了左右子树序列的起始位置*/
	right_inorder = in_order + left_nodes_total + 1;
	proot->rchild = rebuild_bintree(right_inorder, right_postorder, right_nodes_total);

	return proot;
}

/*
 * 查找二叉树中两个节点的最低祖先节点（或最近公共父节点等）
 * 	最低祖先节点就是从根节点遍历到给定节点时的最后一个相同节点
 * (1)递归方式
 * 	如果给定proot是NULL，即空树，则返回的公共节点自然就是NULL；
 * 	如果给定proot与两个节点中任何一个相同，说明，proot在就是所要找的两个节点之一，则直接返回proot，表明在当前链路中找到至少一个节点；
 * 	如果给定proot不是两个节点中任何一个，则说明，需要在proot的左右子树中重新查找，
 * 		此时有三种情况：两个节点都在左子树上；两个节点都在右子树上；一个在左子树，一个在右子树上；具体来说，就是：
 * 情况一：如果左子树查找出的公共节点是NULL，则表明从左子树根节点开始到左子树的所有叶子节点等所有节点中，没有找到两个节点中的任何一个，这就说明，这两个节点不在左子树上，不在左子树，则必定在右子树上；
 * 情况二：如果右子树查找的公共节点是NULL，说明在右子树中无法找到任何一个节点，则两个节点必定在左子树上；
 * 情况三： 如果左右子树查找的公共节点都不是NULL，说明左右子树中各包含一个节点，则当前节点proot就是最低公共节点，返回就可以了。
 * 三种情况是互斥的， 只能是其中之一。
 * */
BinTree bintree_last_common_parent(BinTree proot, BinTree pnode1, BinTree pnode2)
{
	BinTree root_left, root_right;

	if (proot == NULL) //说明是空树，不用查找了，也就找不到对应节点，则返回NULL
		return NULL;

	if (proot == pnode1 || proot == pnode2)//说明在当前子树的根节点上找到两个节点之一
		return proot;

	root_left = bintree_last_common_parent(proot->lchild, pnode1, pnode2);  //左子树中的查找两个节点并返回查找结果
	root_right = bintree_last_common_parent(proot->rchild, pnode1, pnode2);//右子树中查找两个节点并返回查找结果

	if (root_left == NULL)//如果在左子树中没有找到，则断定两个节点都在右子树中，可以返回右子树中查询结果；否则，需要结合左右子树查询结果共同断定
		return root_right;
	if (root_right == NULL)//如果在右子树中没有找到，则断定两个节点都在左子树中，可以返回左子树中查询结果；否则，需要结合左右子树查询结果共同断定
		return root_left;

	return proot;//如果在左右子树中都找两个节点之一，则proot就是最低公共祖先节点，返回即可。
}

#if 0
BinTree *bintree_last_common_parent_nonrecursive(BinTree *proot,  BinTree *pnode1, BinTree *pnode2)
{
	vector vec1;//用来保存从根节点到指定节点的遍历路径，前序遍历
	vector vec2;
	stack st;
	bool find_flag1 = false;
	bool find_flag2 = false;
	BinTree *common_parent = NULL;

	if (proot == NULL || pnode1 == NULL || pnode2 == NULL)
		return;

	while (proot != NULL || !st.empty()) {
		while (proot != NULL) {
			if (findflag1 == false) {//没有找出所有的节点：从根节点到指定节点，在遍历时继续入栈
				vec1.push_back(proot);
				if (proot == pnode1)//找到，则设置标志位
					find_flag1 = true;
			}
			if (findflag2 == false ) {
				vec1.push_back(proot);
				if (proot == pnode2)
					find_flag2 = true;
			}


			if (find_flag1 == true && find_flag2 == true)//如果都已找到，则退出
				break;

			st.push(proot);
			proot = proot->lchild;
		}


		while (!st.empty()) {
			proot = st.top();
			st.pop();
			proot = proot->right;

			if (findflag1 == false)//没有找到全部路径节点时，就需要将错误路径节点退出
				vec1.pop_back();

			if(findflag2 == false)
				vec2.pop_back();
		}
		if (findflag1 == true && findflag2 == true)//如果都已找到，则退出
			break;
	}

	if (findflag1 == true && findflag2 == true) {//在两个遍历路径上查找最后一个相同的节点，就是最低公共祖先节点(最近公共父节点)
		vector< BinTree *> ::iterator iter1 = vec1.begin();
		vector< BinTree *> ::iterator iter2 = vec2.begin();
		while (iter1 != vec1.end() && iter2 != vec2.end()) {
			if (*iter1 == *iter2)
				common_parent = *iter1;
			else
				break;
			++iter1;
			++iter2;
		}
	}

	vec1.clear();
	vec2.clear();
	st.clear();

	return common_parent;
}

/*
 * 二叉树中任意两个节点之间的距离
 * 根本上是求二叉树中任意两个节点的最近祖先节点（最近公共父节点），求出最近祖先节点之后，由最近祖先节点到这两个节点的距离之和就是。
 * （1）递归方式
 * 首先根据递归方式求出最近祖先节点；
 * 然后根据递归方式，从最近祖先节点通过前序遍历方式遍历到给定节点，找到路径，同时计算出距离即可（本处距离可以认为是两节点之间的边可以看成是单位1）
 * （2）非递归方式
 * */
int bintree_length_between_nodes(BinTree *proot, BinTree *pnode1, BinTree *pnode2)
{
	vector <BinTree *>  vec1;
	vector <BinTree *>  vec2;
	stack <BinTree *>  st;

	bool find_node1 = false;
	bool find_node2 = false;
	int len = 0;

	if (proot == NULL || pnode1 == NULL || pnode2 == NULL)
		return 0;
	if (pnode1 == pnode2)
		return 0;

	while (!st.empty() || proot != NULL) {//前序遍历，找到从根节点到给定节点的路径
		while (proot != NULL) {
			if (find_node1 == false) {
				vec1.push_back(proot);
				if (proot == pnode1)
					find_node1 = true;
			}
			if (find_node2 == false) {//没有找到完整路径，就增加节点
				vec2.push_back(proot);
				if (proot == pnode2)
					find_node1 = true;
			}

			if (find_node1 && find_node2)//都已找到，退出查找
				break;

			st.push(proot);
			proot = proot->lchild;
		}

		if (!st.empty() ) {
			proot = st.top();
			st.pop();
			proot = proot->rchild;
			if (find_node1 == false)//路径错误，则删除节点
				vec1.pop_back();
			if (find_node2 == false)
				vec2.pop_back();
		}
		if (find_node1 && find_node2)//都已找到，退出查找
			break;
	}

	if (find_node1 && find_node2) {
		vector <BinTree *> :: iterator  iter1 = vec1.begin();
		vector< BinTree *> :: iterator iter2 = vec2.begin();
		BinTree *common_parent = NULL;
		int common_size = 0;
		while (iter1 != vec1.end() && iter2 != vec2.end()) {//同时从根节点开始，遍历两个路径，找到最低祖先节点，并记录从根节点到最低祖先节点的长度
			if (*iter1 == *iter2 ) {
				common_parent = *iter1;
				++common_size;
			} else
				break;
		}
		len = vec1.size() + vec2.size() - 2 * common_size;//两个路径长度-两个共同长度，就是最终距离
	}

	vec1.clear();
	vec2.clear();
	st.clear();

	return len;
}

#endif
