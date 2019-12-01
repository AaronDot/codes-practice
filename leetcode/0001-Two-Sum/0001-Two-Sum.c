/*
 * TAG: 
 *      array
 *      hash
 *
 * Input: numbers={2, 7, 11, 15},
 *        target=9
 * Output: index1=1, index2=2
 *
 * LeetCode:
 *
 * 提交时间 提交结果 执行用时 内存消耗 语言
 * 几秒前	通过	216 ms	7.6 MB	C
 * */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int *returnId = (int *) malloc(sizeof(int) * 2);

    *returnSize = 0;

    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                returnId[0] = i;
                returnId[1] = j;
                *returnSize = 2;

                return returnId;
            }
        }
    }

    return returnId;
}

int main(int *argc, char *argv[])
{
	int i, j;
	int index1 = 0, index2 = 0;
	int numbers[] = {2, 7 ,11, 15};
	int target;

    int *returnId = NULL;
    int returnSize = 2;

	printf("Please input the target:");
	scanf("%d", &target);


    returnId = twoSum(numbers, sizeof(numbers), target, &returnSize);

	if (returnId[1] == 0)
		printf("Can not find\n");
	else
		printf("The index=%d and the index2=%d\n", returnId[0], returnId[1]);

    free(returnId);
    return 0;
}

