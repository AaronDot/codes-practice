/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 * */

#ifndef __EQUAL_H__
#define __EQUAL_H__

#include <string.h>

//默认的相等的方法
int equal_default(void *a, void *b);

//int类型相等的方法
int equal_int(void *a, void *b);

//char类型相等的方法
int equal_char(void *a, void *b);

//string类型相等的方法
int equal_string(void *a, void *b);

#endif
