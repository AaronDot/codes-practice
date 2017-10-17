#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* hash table */
typedef struct HashNode {
	int val;
	int key;
	struct HashNode * next;
} HashNode;

static inline int hash (int val, int n) {
	int index = val % n;
	return (index > 0) ? (index) : (-index);
}

int *twoSum(int numbers[], int n, int target) {
    static int ret[2] = { 0, 0 };
    int i;

    HashNode **hashtable = (HashNode **)calloc(n, sizeof(HashNode *));

    int idx;
    HashNode *p, *tail;
    for (i = 0; i < n; i++) {
        idx = hash(numbers[i], n);
        //get tail
        p = hashtable[idx];
        tail = NULL;
        while (p != NULL) {
            tail = p;
            p = p->next;
        }
        HashNode *new_node = (HashNode *)calloc(1, sizeof(HashNode));
        new_node->val = numbers[i];
        new_node->key = i;
        new_node->next = NULL;

        if (tail) {
            tail->next = new_node;
        }
        else {
            hashtable[idx] = new_node;
        }
    }

    for (i = 0; i < n; i++) {
        int diff = target - numbers[i];
        idx = hash(diff, n);
        p = hashtable[idx];
        while (p != NULL) {
            if (p->val == diff && p->key != i) {
                ret[0] = p->key + 1;
                ret[1] = i + 1;
