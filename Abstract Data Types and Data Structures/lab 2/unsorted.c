/* file name: unsorted.c
 *
 * author: Jack DeMeulemeester
 *
 * date: 1/18/2023
 *
 * description: Allows user to create or destroy a set of unsorted data. Allows the user to
 * manipulate the data by adding data and removing data. Also lets the user look through
 * the data for specfic words or the whole array of words.i
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>

struct set{
	char **elts;
	int length;
	int count;
};

/*Description: Creates a set and gives it memory. It then creates memory for the array in
 * the set and gives all values in the set default values.
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

/*Description: Loops through the entire array freeing all the memory and the set itself at the end.
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

/*Description: Gives the number of words in the array.
 *
 * Complexity: O(1)
 */

int numElements(SET *sp){
	return sp->count;
}

/*Description: Loops through the set looking for the target word. If it is found then the
 * index is returned.
 *
 * Complexity: O(n)
 */
static int search(SET *sp, char *elt){
	int i;
	for(i=0;i<sp->count;i++){
		if(strcmp(sp->elts[i], elt) == 0){
			return i;
		}
	}
	return -1;
}

/*Description: Makes sure that a duplicate word is not added to the set. Then creates memory
 * space for the new word and puts the new word at the end of the array
 *
 * Complexity: O(n)
 */
void addElement(SET *sp, char *elt){
	int i;
	i = search(sp, elt);
	if(i == -1){
		sp->elts[sp->count] = malloc(sizeof(char)*strlen(elt)+1);
		assert(sp->elts[sp->count]);
		strcpy(sp->elts[sp->count++], elt);
	}
	return;
}

/*Description: Finds index where element is to be removed. Then frees the index of its' pointer
 * and moves last element in the array to where the previous element was just removed.
 *
 * Complexity: O(n)
 */
void removeElement(SET *sp, char *elt){
	int i;
	i = search(sp, elt);
	if(i > -1){
		free(sp->elts[i]);
		sp->elts[i]=sp->elts[--sp->count];
	}
	return;
}

/*Description: Looks to see if a specific element is in the array, if it is then it is returned.
 *
 * Complexity: O(n)
 */
char *findElement(SET *sp, char *elt){
	int i;
	i = search(sp, elt);
	if(i > -1){
		return sp->elts[i];
	}
	return NULL;
}

/*Description: Creates a copy of the array in the set to return for the user to see.
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
