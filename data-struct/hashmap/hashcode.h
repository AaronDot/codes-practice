/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 * */

#ifndef __HASHCODE_H__
#define __HASHCODE_H__

#include <string.h>

#define HASHCODE_MULT	31

//默认的hashCode
int hash_code_default(void *a);

//int类型hashCode
int hash_code_int(void *a);

//char类型的hashCode
int hash_code_char(void *a);

//string类型的hashCode
int hash_code_string(void *a);

#endif
