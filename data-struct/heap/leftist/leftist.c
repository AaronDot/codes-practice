/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 *
 * http://www.cnblogs.com/skywang12345/p/3638327.html
 * */

#include "leftist.h"

#define LENGTH(a)	((sizeof(a)) / (sizeof(a[0])))

void main()
{
	int i;
	int a[] = {10,40,24,30,36,20,12,16};
	int b[] = {17,13,11,15,19,21,23};
	int alen = LENGTH(a);
	int blen = LENGTH(b);
	LeftistHeap ha, hb;

	ha = hb = NULL;

	printf("== 左倾堆(ha)中依次添加: ");
	for (i = 0; i < alen; i++) {
		printf("%d ", a[i]);
		ha = insert_leftist(ha, a[i]);
	}
	printf("\n== 左倾堆(ha)的详细信息: \n");
	print_leftist(ha);


	printf("\n== 左倾堆(hb)中依次添加: ");
	for (i = 0; i < blen; i++) {
		printf("%d ", b[i]);
		hb = insert_leftist(hb, b[i]);
	}
	printf("\n== 左倾堆(hb)的详细信息: \n");
	print_leftist(hb);

	// 将"左倾堆hb"合并到"左倾堆ha"中。
	ha = merge_leftist(ha, hb);
	printf("\n== 合并ha和hb后的详细信息: \n");
	print_leftist(ha);

	// 销毁左倾堆
	destroy_leftist(ha);
}
