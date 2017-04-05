/*
 *	Created on:	2014-07-10
 *	    Author:	Aaron Chou
 *
 * http://www.cnblogs.com/gaochundong/p/comparison_sorting_algorithms.html#odd_even_sort
 *
 * +--------------------------------------------------------------------------------------------------------------------+
 * |						比较排序算法(Comparison Sorts)						|
 * +--------------------+-----------------------+-------+---------------+---------------+---------------+---------------+
 * | Category		| Name			| Best	| Average	| Worst 	| Memory 	| Stability	|
 * +--------------------+-----------------------+-------+---------------+---------------+---------------+---------------+
 * | 插入排序		|插入排序		| n	| n^2		| n^2		| 1		| Stable	|
 * | (Insertion Sorts)	|(Insertion Sort)	|	|		|		|               |               |
 * |			+-----------------------+-------+---------------+---------------+---------------+---------------+
 * |			|希尔排序		| n	| nlog2n	| nlog2n	| 1		| Not Stable	|
 * |			|(Shell Sort)		|	|		|		|               |               |
 * +--------------------+-----------------------+-------+---------------+---------------+---------------+---------------+
 * |	交换排序	|快速排序		| nlogn	| nlogn		| n^2		| log n		| Not Stable    |
 * | (Exchange Sorts )	|(Quick Sort)		|	|		|		|               |               |
 * |			+-----------------------+-------+---------------+---------------+---------------+---------------+
 * |			|冒泡排序		| n	| n^2		| n^2		| 1		| Stable        |
 * |			|(Bubble Sort)		|	|		|		|               |               |
 * |			+-----------------------+-------+---------------+---------------+---------------+---------------+
 * |			|鸡尾酒排序		| n	| n^2		| n^2		| 1		| Stable        |
 * |			|(Cocktail Sort)	|	|		|		|               |               |
 * |			+-----------------------+-------+---------------+---------------+---------------+---------------+
 * |			|奇偶排序		| n	| n^2		| n^2		| 1		| Stable        |
 * |			|(Odd-Even Sort)	|	|		|		|               |               |
 * +--------------------+-----------------------+-------+---------------+---------------+---------------+---------------+
 * |选择排序		|选择排序		| n^2	| n^2		| n^2		| 1		| Not Stable    |
 * |(Selection Sorts)	|(Selection Sort)	|	|		|		|               |               |
 * |			+-----------------------+-------+---------------+---------------+---------------+---------------+
 * |			|堆排序			| nlogn	| nlogn		| nlogn		| 1		| Not Stable    |
 * |			|(Heap Sort)		|	|		|               |               |               |
 * +--------------------+-----------------------+-------+---------------+---------------+---------------+---------------+
 * |合并排序		|合并排序		| n	| nlogn		| nlogn		| n		| Stable        |
 * |(Merge Sorts)	|(Merge Sort)		|	|		|               |               |               |
 * +--------------------+-----------------------+-------+---------------+---------------+---------------+---------------+
 * |混合排序		|内省排序		| nlogn	| nlogn		| nlogn		| logn		| Not Stable    |
 * |(Hybrid Sorts)	|(Introspective Sort)	|	|		|               |               |               |
 * +--------------------------------------------------------------------------------------------------------------------+
 *
 * Stable 与 Not Stable 的比较
 * 	稳定排序算法会将相等的元素值维持其相对次序.
 * 	如果一个排序算法是稳定的,当有两个有相等的元素值R和S,且在原本的列表中R出现在S之前,那么在排序过的列表中R也将会是在S之前.
 * */

#include "sort.h"

int main(void)
{
	int flag = 1, choice;

	selection_menu();

	while (flag) {
		printf("please input you selction:");
		scanf("%d", &choice);
		select_function(choice, &flag);
	}

	return 0;
}

void selection_menu(void)
{
	printf("|---------------------------------------------------------------|\n");
	printf("|		排序算法的比较----主控模块:			|\n");
	printf("|			0. 创建排序数组				|\n");
	printf("|			1. 冒泡排序				|\n");
	printf("|			2. 直接插入排序				|\n");
	printf("|			3. 快速排序				|\n");
	printf("|			4. 选择排序				|\n");
	printf("|			5. 希尔排序				|\n");
	printf("|			6. 堆排序				|\n");
	printf("|			7. 二路归并排序				|\n");
	printf("|			8. 基数排序				|\n");
	printf("|			9. 桶排序				|\n");
	printf("|			10. 鸡尾酒排序				|\n");
	printf("|			11. 奇偶排序				|\n");
	printf("|			12. 退出				|\n");
	printf("|---------------------------------------------------------------|\n");
}

void select_function(int choice, int *flag)
{
	int timeuse;

	switch (choice) {
	case 0:
		creat_randnum(sort_data, ARRAY_LEN);
		printf("the origin number is\n");
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 1:
		/*冒泡排序(两种)*/
		timeuse = count_time(bubble_sort, sort_data, ARRAY_LEN);
		printf("bubble sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 2:
		/*直接插入排序*/
		timeuse = count_time(insert_sort, sort_data, ARRAY_LEN);
		printf("insert sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 3:
		/*快速排序*/
		timeuse = count_time(quick_sort, sort_data, ARRAY_LEN);
		printf("select sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 4:
		/*选择排序*/
		timeuse = count_time(select_sort, sort_data, ARRAY_LEN);
		printf("select sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 5:
		/*希尔排序*/
		timeuse = count_time(shell_sort, sort_data, ARRAY_LEN);
		printf("shell sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 6:
		/*堆排序*/
		timeuse = count_time(heap_sort, sort_data, ARRAY_LEN);
		printf("heap sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 7:
		/*二路归并排序*/
		timeuse = count_time(merge_sort, sort_data, ARRAY_LEN);
		printf("merge sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 8:
		/*基数排序*/
		timeuse = count_time(radix_sort, sort_data, ARRAY_LEN);
		printf("radix sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 9:
		/*桶排序*/
		timeuse = count_time(bucket_sort, sort_data, ARRAY_LEN);
		printf("bucket sort use time: %d ms\n", timeuse);
		printf_bucket(bucket_table);
		break;
	case 10:
		/*鸡尾酒排序*/
		timeuse = count_time(cocktail_sort, sort_data, ARRAY_LEN);
		printf("bubble sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	case 11:
		/*奇偶排序*/
		timeuse = count_time(odd_even_sort, sort_data, ARRAY_LEN);
		printf("bubble sort use time: %d ms\n", timeuse);
		printf_array(sort_data, ARRAY_LEN);
		break;
	default:
		*flag = 0;
		printf("the program is over ,enter any key to exit\n");
	}
}

void call_sort_func(type_sort fp, int *pdata, int count)
{
	fp(pdata, count);
}

int count_time(type_sort fp, int *pdata, int count)
{
	int timeuse;
	struct timeval start, end;

	gettimeofday(&start, NULL);
	call_sort_func(fp, pdata, count);
	gettimeofday(&end, NULL);
	timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

	return timeuse;
}
