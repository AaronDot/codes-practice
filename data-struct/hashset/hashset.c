/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 *
 * http://blog.csdn.net/swwlqw/article/details/22664129
 * */

#include <stdio.h>
#include <stdlib.h>
#include "equal.h"
#include "hashcode.h"
#include "hashset.h"

#define S 10

char* strs[S] = {
	"abc",
	"qq",
	"hello",
	"abc",
	"lmy",
	"ab",
	"qq",
	"lqw",
	"sww",
	"lqw"
};

int main(int argc, char **argv)
{
	int i;
	char *pp;

	//创建集合需要指定两个函数，hashCode函数和equal函数
	MyHashSet * set = createMyHashSet(hash_code_string, equal_string);

	//插入数据
	for (i=0; i<S; i++)
		myHashSetAddData(set, strs[i]);

	//输出大小
	printf("size = %d\n", myHashSetGetSize(set));

	//测试删除
	myHashSetRemoveData(set, "qq");
	myHashSetRemoveData(set, "ab");
	myHashSetRemoveData(set, "qwert");

	//输出大小
	printf("after remove size = %d\n", myHashSetGetSize(set));

	//遍历
	MyHashSetIterator * it = createMyHashSetIterator(set);
	while(myHashSetIteratorHasNext(it)) {
		pp= myHashSetIteratorNext(it);
		puts(pp);
	}

	//释放遍历器
	freeMyHashSetIterator(it);

	//释放集合
	freeMyHashSet(set);

	return 0;
}
