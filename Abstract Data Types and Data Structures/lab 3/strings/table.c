/* file name: table.c
 *
 * author: Jack DeMeulemeester
 * 
 * date: 2/1/2023
 * 
 * description: Demonstrates an abstract data type by allowing the user add, remove, find, and get data.
 * Uses a hash function to speed up the process of searching for data.
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
	char *flags;
};

/* Description: Creates a set and gives it memory. It then creates memory for the array
 * in the set and gives all values in the set default values.
 *
 * Complexity: O(1)
 */
SET *createSet(int maxElts){
	int i;
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp);
	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts);
	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->flags);
	for(i=0; i < maxElts; i++){
		sp->flags[i] = 'E';
	}
	sp->length = maxElts;
	sp->count = 0;
	return sp;
}

/* Description: Loops through the entire array freeing where memory was allocated and then
 *  frees the the arrays and the set.
 *
 * Complexity: O(n)
 */
void destroySet(SET *sp){
	int i;
	assert(sp != NULL);
	for(i = 0; i < sp->length; i++){
		if(sp->flags[i] == 'F'){
			free(sp->elts[i]);
		}
	}
	free(sp->flags);
	free(sp->elts);
	free(sp);
}

/* Description: Gives the number of words in the array.
 *
 * Complexity: O(1)
 */
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

/* Description: Runs a char through a hash function and returns the value of the hash.
 *
 * Complexity: O(n)
 */
unsigned strhash(char *s){
	unsigned hash = 0;
	while(*s != '\0'){
		hash = 31 * hash + *s ++;
	}
	return hash;
}

/* Description: Recieves a hash value from the hash function. Then loops through the array looking
 * for a spot where either a value can be inserted or where a value already exists, returns the 
 * the index of what is found.
 * 
 * Complexity: best case O(1), worst case O(n)
 */
static int search(SET *sp, char *elt, bool *found){
	assert(sp != NULL && elt != NULL);
	int locn, i;
	int hash = strhash(elt) % sp->length;
	int dflag = -1;
	for(i = 0; i< sp->length; i++){
		locn = (hash + i) % sp->length;
		if(sp->flags[locn] == 'E'){
			*found = false;
			if(dflag != -1){
				return dflag;
			}
			return locn;
		} else if(sp->flags[locn] == 'D'){
			if(dflag == -1){
				dflag = locn;
			}
		} else if(strcmp(sp->elts[locn], elt) == 0){
			*found = true;
			return locn;
		}
	}
	*found = false;
	return dflag;
}

/* Description: Searches for duplicate strings where the word should be inserted. If there
 * is no duplicate then the string is inserted where the hash value tells it to insert.
 *
 * Complexity: best case O(1), worst case O(n)
 */
void addElement(SET *sp, char *elt){
	int locn;
	bool found;
	char *copy;
	assert(sp != NULL && elt != NULL);
	locn = search(sp, elt, &found);
	if(!found){
		assert(sp->count < sp-> length);
		copy = strdup(elt);
		assert(copy != NULL);
		sp->elts[locn] = copy;
		sp->flags[locn] = 'F';
		sp->count++;
	}
}

/* Description: Finds element to be removed, once index is found then the element is freed.
 *
 * Complexity: best case O(1), worst case O(n)
 */
void removeElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
	int locn;
	bool found;
	locn = search(sp, elt, &found);
	if(found){
		free(sp->elts[locn]);
		sp->flags[locn] = 'D';
		sp->count--;
	}
	return;
}

/* Description: Searches for an element in the array, if it is found then it is returned.
 *
 * Complexity: best case O(1), worst case O(n)
 */
char *findElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
	int locn;
	bool found;
	locn = search(sp, elt, &found);
	if(found){
		return sp->elts[locn];
	}
	return NULL;
}

/* Description: Returns a copy of all the spots in the orginial array that have elements in them.
 *
 * Complexity: O(n)
 */
char **getElements(SET *sp){
	assert(sp != NULL);
	char **copy;
	int i;
	int c = 0;
	copy = malloc(sizeof(char*)*sp->count);
	assert(copy);
	for(i = 0; i < sp->length; i++){
		if(sp->flags[i] == 'F'){
			copy[c++] = sp->elts[i];
		}
	}
	return copy;
}
