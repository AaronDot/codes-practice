/*
 *	Created on:	2015-07-02
 *	    Author:	Aaron Chou
 * */

#include "linklist.h"

struct LNode *list, *list2, *list3, *list_merge;

int main(void)
{
	int choice, flag = 1;

	selection_menu();

	while (flag) {
		printf("please select the function:");
		scanf("%d", &choice);
		select_function(choice, &flag);
	}

	return 0;
}

void selection_menu(void)
{
	printf("本程序实现带头结点单链表的基本操作.\n");
	printf("		可以进行建立链表,查询,删除,反转等操作.\n");
	printf("\n");
	printf("|---------------------------------------------------------------|\n");
	printf("|		链表的基本操作如下:				|\n");
	printf("|			0.创建链表				|\n");
	printf("|			1.根据位置查看元素的值			|\n");
	printf("|			2.根据值查看元素的位置			|\n");
	printf("|			3.查看元素前驱				|\n");
	printf("|			4.查看元素后驱				|\n");
	printf("|			5.插入元素				|\n");
	printf("|			6.根据元素位置删除元素			|\n");
	printf("|			7.反转链表(三种方法)			|\n");
	printf("|			8.合并两个有序链表			|\n");
	printf("|			9.清空链表所有元素,并判断是否为空	|\n");
	printf("|			10.打印链表所有元素			|\n");
	printf("|			11.链表长度				|\n");
	printf("|			12.销毁链表				|\n");
	printf("|			13.退出程序				|\n");
	printf("|---------------------------------------------------------------|\n");
}

void select_function(int choice, int *flag)
{
	struct LNode *p = NULL;
	int pos, e, ret;

	switch (choice) {
	case 0:
		printf("input the elem of list:\n");
		list = create_list(list);
		if (list == NULL)
			printf("Create list fail!\n");
		else
			printf("Create list success!\n");
		break;
	case 1:
		printf("Please input the position you want to find:\n");
		scanf("%d", &pos);

		p = get_elem(list, pos);
		if (p == NULL)
			printf("the position is beyond the list\n");
		else
			printf("the pos elem is %d\n", p->elem);
		break;
	case 2:
		printf("Please input the elem you want to find:\n");
		scanf("%d", &e);

		ret = search_elem(list, e);
		if (ret == -1)
			printf("The elem is not found\n");
		else
			printf("The elem is found, and the position is %d\n", ret);
		break;
	case 3:
		printf("Please input the elem you want to find:\n");
		scanf("%d", &e);

		p = get_privor(list, e);
		if (p == NULL)
			printf("can not find the elem's priv\n");
		else
			printf("find the elem's priv, is %d\n", p->elem);
		break;
	case 4:
		printf("Please input the elem you want to find:\n");
		scanf("%d", &e);

		p = get_next(list, e);
		if (p == NULL)
			printf("can not find the elem's next\n");
		else
			printf("find the elem's next, is %d\n", p->elem);
		break;
	case 5:
		printf("Please input the position you want insert, and the elem:\n");
		scanf("%d, %d", &pos, &e);

		ret = insert_list(list, pos, e);
		if ( ret == -1)
			printf("the priv of the elem is not exist, and insert error\n");
		else
			printf("insert error\n");
		break;
	case 6:
		printf("Please input the position you want to delete:\n");
		scanf("%d", &pos);

		ret = delete_elem(list, pos);
		if (ret == -1)
			printf("can not find the elem or its priv,delete error!\n");
		else
			printf("delete success!\n");
		break;
	case 7:
		p = reserve_list_2(list);
		if (p == NULL)
			printf("the list not exist,please enter 0 to create\n");
		else {
			printf("After reserve, the list is:\n");
			printf_list(p);
		}
		break;
	case 8:
		printf("input the elem of list2 to merge:\n");
		list2 = create_list(list2);
		if (list2 == NULL)
			printf("Create list2 fail!\n");
		else
			printf("Create list2 success!\n");
		printf_list(list2);

		printf("input the elem of list3 to merge:\n");
		list3 = create_list(list3);
		if (list3 == NULL)
			printf("Create list3 fail!\n");
		else
			printf("Create list3 success!\n");
		printf_list(list3);

		list_merge = sorted_merge_2(list2, list3);

		printf_list(list_merge);
		break;
	case 9:
		ret = clear_list(list);
		if (ret == -1)
			printf("the list not exist, please enter 0 to create\n");
		else {
			if (empty_list(list) == 0)
				printf("The list is empty, clear success\n");
			else
				printf("The list is not empty, clear fail\n");
		}
		break;
	case 10:
		printf_list(list);
		break;
	case 11:
		ret = length_list(list);
		printf("the list's length is %d\n", ret);
		break;
	case 12:
		destory_list(&list);
		break;
	default:
		*flag = 0;
		printf("the program is over ,enter any key to exit\n");
	}
}
