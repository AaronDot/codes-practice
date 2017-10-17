/*
 * Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 *
 * Example:
 * 	Given nums = [2, 7, 11, 15], target = 9,
 * 	Because nums[0] + nums[1] = 2 + 7 = 9,
 * 	return [0, 1].
 * */

/*
 * Note: The returned array must be malloced, assume caller calls free().
 * */
int* twoSum(int* nums, int numsSize, int target)
{
	int i, j, temp;
	int* result = malloc(2 * sizeof(int));
	result[0] = result[1] = 0;

	for(i = numsSize -1 ; i > -1; i--) {
		if(nums[i] <= target || target < 0) {
			for(j = 0 ; j< numsSize; j++) {
				if(i ^ j) {
					temp = nums[i] + nums[j];
					if(temp == target) {
						result[0] = i > j ? j + 1 : i + 1;
						result[1] = j > i ? j + 1 : i + 1;

						return result;
					}
				}
			}
		}
	}

	return result;
}
