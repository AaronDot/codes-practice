/*
 * Given a string, find the length of the longest substring without repeating characters.
 *
 * Examples:
 *
 * Given "abcabcbb", the answer is "abc", which the length is 3.
 * Given "bbbbb", the answer is "b", with the length of 1.
 * Given "pwwkew", the answer is "wke", with the length of 3.
 * Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 * */

int lengthOfLongestSubstring(char* s)
{
	int hash[256];
	char *p = s;
	char *q = s;
	int ret = 0;

	memset(hash, 0, 256*sizeof(int));

	while(*q != '\0') {
		if (hash[*q] != 0) {
			while(p<q) {
				if ((*p)==(*q)) {
					p++;
					q++;
					break;
				}
				hash[*p] = 0;
				p++;
			}
		} else {
		hash[*q] = 1;
		q++;
		if (q-p > ret) ret = q-p;
		}
	}
	return ret;
}
