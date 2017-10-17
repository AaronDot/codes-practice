/*
 *Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 1. 将整形数组转化为结构体数组,将数组下标作为结构体成员,这样方便对数组下标的访问和不易混淆;
 * 2. 对结构体数组,使用函数qsort进行从小到大的快速排序;
 * 3. 对排序后的结构体数组进行二分法查找,查找可能满足等于target的目标区间.
 * 	关键:若array[mid]>target，则继续缩放区间;否则break;
 * 4. 在缩放后的区间里,进行首尾的查找.若找到,则存放下标;
 * 5. 返回下标值.
 * */
struct array_node {
	int value;
	int index;
};

struct index {
	int index1;
	int index2;
};

static int cmp(const void *a,const void *b)
{
	return ((struct array_node*)a)->value - ((struct array_node*)b)->value;
}

void BinaryResearch(struct Node *array, int target,struct index *c_index,int length)
{
    int low, high,mid;
//  int length=sizeof(array)/sizeof(struct Node);
    low=0;
    high=length-1;
    while(low<high)
    {

        mid=(low+high)/2;
        if(array[mid].value>target)
        {
            if((mid-1)==low)
            {
                break;
            }
            high=mid-1;
        }
        else if(array[mid].value<=target)
        {
            break;
        }

    }

    c_index->index1=low;
    c_index->index2=high;
//  return c_index;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {

    int i,j;
    int sum;
    int *index_return=(int *)malloc(2*sizeof(int));

    struct index *c_index=(struct index*)malloc(sizeof(struct index));
    struct Node *array;
    array=(struct Node*)malloc(numsSize*sizeof(struct Node));
    //convert nums to struct array
    for(i=0; i<numsSize; i++)
    {

        array[i].value=nums[i];
        array[i].index=i+1;
    }

    qsort(array,numsSize,sizeof(struct Node),cmp);

    BinaryResearch(array,target,c_index,numsSize);


    i=c_index->index1;
    j=c_index->index2;

    while(i<j)
    {
        sum=array[i].value+array[j].value;
        if(sum==target)
        {
            *index_return=array[i].index<array[j].index ? array[i].index : array[j].index;
            *(index_return+1)=array[i].index>=array[j].index ? array[i].index : array[j].index;
            break;
        }
        else if(sum>target)
        {
            j--;
        }
        else if(sum<target)
        {
            i++;
        }

    }

    return index_return;
}


/*
 * Note: The returned array must be malloced, assume caller calls free().
 * */
int* twoSum(int* nums, int numsSize, int target) {

}
