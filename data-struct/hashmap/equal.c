/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 * */

#include "equal.h"

//默认的相等的方法
int equal_default(void *a, void *b)
{
	return a == b;
}

//int类型相等的方法
int equal_int(void *a, void *b)
{
	int *aa, *bb;

	aa = (int *)a;
	bb = (int *)b;

	return *aa == *bb;
}

//char类型相等的方法
int equal_char(void *a, void *b)
{
	char *aa, *bb;

	aa = (char *)a;
	bb = (char *)b;

	return *aa = *bb;
}

//string类型相等的方法
int equal_string(void *a, void *b)
{
    char *aa, *bb;

    aa = (char *)a;
    bb = (char *)b;

    return strcmp(aa, bb) == 0;
}
