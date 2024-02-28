/* file name: unsorted.c
 *
 * author: Jack DeMeulemeester
 * 
 * date: 1/18/2023
 * 
 * description: Allows user to create or destroy a set of sorted data. Allows the
 * user to maniplate the data by adding data and removing data in a sorted manner.
 * Also lets the user look through the data for specific words or the whole array of words.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>


struct set{
	char **elts;
	int length;
	int count;
};

/* Description: Creates a set and gives it memory. It then creates memory for the array
 * in the set and gives all values in the set default values.
 *
 * Complexity: O(1)
 */
SET *createSet(int maxElts){
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp);
	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts);
	sp->length = maxElts;
	sp->count = 0;
	return sp;
}

/* Description: Loops through the entire array freeing all the memory and the
 * set itslef at the end.
 *
 * Complexity: O(n)
 */
void destroySet(SET *sp){
	while(sp->count > 0){
		free(sp->elts[sp->count]);
		sp->count--;
	}
	free(sp);
	return;
}

/* Description: Gives the number of words in the array.
 *
 * Complexity: O(1)
 */
int numElements(SET *sp){
	return sp->count;
}

/* Description: Conducts a binary search through the array looking for the target.
 * if the target is found then the boolean is true and if not then the boolean is
 * false. Either way the index where it was found or where it should be inserted
 * is returned.
 *
 * Complexity: O(log(n))
 */
static int search(SET *sp, char *elt, bool *found){
	int bot = 0;
	int mid;
	int top = sp->count - 1;
	int c;

	while(bot <= top){
		mid = (bot + top)/2;
		c = strcmp(sp->elts[mid], elt);
		if(c == 0){
			*found = true;
			return mid;
		}else if(c > 0){
			top = mid-1;
		}else if(c < 0){
			bot = mid+1;
		}
	}
	*found = false;
	return bot;
}

/* Description: Searches for duplicate words and where the word should be inserted.
 * Before inserting the word all elements after it's insertion point are shifted
 * back one. Word is inserted in sorted order.
 *
 * Complexity: O(n)
 */
void addElement(SET *sp, char *elt){
	int i, j;
	bool found;
	i = search(sp, elt, &found);
	if(!found && sp->count < sp->length){
		for(j = sp->count; j > i; j--){
			sp->elts[j] = sp->elts[j-1];
		}
		sp->elts[i] = strdup(elt);
		assert(sp->elts[i]);
		sp->count++;
	}
	return;
}

/* Description: Finds index where element is to be removed. then frees the index of its' pointer
 * and moves all following elements down one index.
 *
 * Complexity: O(n)
 */
void removeElement(SET *sp, char *elt){
	int i, j;
	bool found;
	i = search(sp, elt, &found);
	if(found){
		free(sp->elts[i]);
		for(j = i; j < sp->count; j++){
			sp->elts[j] = sp->elts[j+1];
		}
		sp->count--;
	}
	return;
}

/* Description: Searches through array for specific element, if it is in the array,
 * then it is returned.
 *
 * Complexity: O(log(n))
 */
char *findElement(SET *sp, char *elt){
	int i;
	bool found;
	i = search(sp, elt, &found);
	if(found){
		return sp->elts[i];
	}
	return NULL;
}

/* Description: Creates a copy of the array in the set to return for the user to see.
 *
 * Complexity: O(1)
 */
char **getElements(SET *sp){
	char **copy;
	copy = malloc(sizeof(char*)*sp->count);
	assert(copy);
	memcpy(copy, sp->elts, sizeof(char*)*sp->count);
	return copy;
}
