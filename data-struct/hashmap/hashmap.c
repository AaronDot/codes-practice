/*
 *	Created on:	2017-04-13
 *	    Author:	Aaron Chou
 *
 * http://blog.csdn.net/swwlqw/article/details/22666705
 * */

#include <stdio.h>
#include <stdlib.h>
#include "equal.h"
#include "hashcode.h"
#include "hashmap.h"

#define S	10

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


int main(int *argc, char **argv)
{
	int *data, *value;
	int i;
	Entry *pp;
	char *key;

	data = malloc(sizeof(int)* S);
	for (i=0; i<S; i++)
		data[i] = i;

	//创建映射需要指定两个函数，hashCode函数和equal函数。
	MyHashMap * map = createMyHashMap(hash_code_string, equal_string);

	//插入数据
	for (i=0; i<S; i++)
		myHashMapPutData(map, strs[i], &data[i]);

	//输出大小
	printf("size=%d\n", myHashMapGetSize(map));

	//测试删除
	myHashMapRemoveDataByKey(map, "qq");
	myHashMapRemoveDataByKey(map, "ab");
	myHashMapRemoveDataByKey(map, "qwert");

	//输出大小
	printf("after remove size=%d\n", myHashMapGetSize(map));

	//遍历
	MyHashMapEntryIterator * it = createMyHashMapEntryIterator(map);
	while (myHashMapEntryIteratorHasNext(it)) {
		pp= myHashMapEntryIteratorNext(it);
		key = pp-> key;
		value = pp->value;
		printf("%s(%d)\n", key, *value);
	}

	//释放遍历器
	freeMyHashMapEntryIterator(it);

	//释放映射
	freeMyHashMap(map);

	//释放数据
	free(data);

	return 0;
}
