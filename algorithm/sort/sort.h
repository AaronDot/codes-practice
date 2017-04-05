#ifndef SORT_H_
#define SORT_H_

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_LEN 100
#define BUCKET_SIZE 10
typedef void (*type_sort)(int *, int);

struct bucket_node {
	int key;
	struct bucket_node *next;
};

/*函数声明*/
/***************交换排序****************************/
void bubble_sort(int *pdata, int count);
void bubble_sort_flag(int *pdata, int count);
void quick_sort(int *pdata, int count);
void cocktail_sort(int *pdata, int count);
void odd_even_sort(int *pdata, int count);
/***************插入排序****************************/
void insert_sort(int *pdata, int count);
void shell_sort(int *pdata, int count);
/***************选择排序****************************/
void select_sort(int *pdata, int count);
void heap_sort(int *pdata, int count);
/***************合并排序****************************/
void merge_sort(int *pdata, int count);
/***************分配式排序****************************/
void radix_sort(int *pdata, int count);
void bucket_sort(int *pdata, int count);

void swap_elem(int *a, int *b);

void selection_menu(void);
void select_function(int choice, int *flag);
void creat_randnum(int *pdata, int count);
void printf_array(int *pdata, int count);
void printf_bucket(struct bucket_node **bucket_table);

int count_time(type_sort fp, int *pdata, int count);
void call_sort_func(type_sort fp, int *pdata, int count);

int sort_data[ARRAY_LEN], mem_data[ARRAY_LEN];
struct bucket_node **bucket_table;

#endif
