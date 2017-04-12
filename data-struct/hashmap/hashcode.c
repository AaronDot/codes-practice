/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 * */

#include "hashcode.h"

//默认的hashCode
int hash_code_default(void *a)
{
	return (int)a;
}

//int类型hashCode
int hash_code_int(void *a)
{
	int * aa;

	aa = (int *)a;

	return *aa;
}

//char类型的hashCode
int hash_code_char(void *a)
{
	char *aa;

	aa = (char *)a;

	return *aa;
}

//string类型的hashCode
int hash_code_string(void *a)
{
	int re = 0;
	char *aa = (char *)a;

	while (*aa) {
		re += HASHCODE_MULT * *aa;
		aa++;
	}

	return re;
}
