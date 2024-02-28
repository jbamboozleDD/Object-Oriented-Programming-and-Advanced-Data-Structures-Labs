/* file name: table.c
 *
 * author: Jack DeMeulemeester
 * 
 * date: 2/8/2023
 * 
 * description: Demonstrates an generic abstract data type by allowing the user add, remove, find, and get generic data.
 * Uses a hash function to speed up the process of searching for generic data.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>


struct set{
	int length;
	int count;
    void **data;
    char *flags;
    int (*compare)();
    unsigned (*hash)();
};

/* Description: Creates a set and gives it memory. It then creates memory for the generic array
 * in the set and gives all values in the set default values.
 *
 * Complexity: O(1)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	int i;
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp);
	sp->data = malloc(sizeof(void*)*maxElts);
	assert(sp->data);
	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->flags);
	for(i=0; i < maxElts; i++){
		sp->flags[i] = 'E';
	}
    sp->compare = compare;
    sp->hash = hash;
	sp->length = maxElts;
	sp->count = 0;
	return sp;
}

/* Description: frees all allocated memory in the set and then frees the set.
 *
 * Complexity: O(1)
 */
void destroySet(SET *sp){
	assert(sp != NULL);
	free(sp->flags);
	free(sp->data);
	free(sp);
}

/* Description: Gives the number of elements in the array.
 *
 * Complexity: O(1)
 */
int numElements(SET *sp){
	assert(sp != NULL);
    return sp->count;
}

/* Description: Recieves a hash value. Then loops through the array looking
 * for a spot where either a value can be inserted or where a value already exists, returns the 
 * the index of what is found.
 *
 * Complexity: best case O(1), worst case O(n)
 */
static int search(SET *sp, void *elt, bool *found){
	assert(sp != NULL && elt != NULL);
	int locn, i;
    int hash = (*sp->hash)(elt) % sp->length;
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
		} else if((*sp->compare)(sp->data[locn], elt) == 0){
			*found = true;
			return locn;
		}
	}
	*found = false;
	return dflag;
}

/* Description: Searches for a duplicate where the element should be inserted. If there
 * is no duplicate then the element is inserted where the hash value tells it to insert.
 *
 * Complexity: best case O(1), worst case O(n)
 */
void addElement(SET *sp, void *elt){
	int locn;
	bool found;
	assert(sp != NULL && elt != NULL);
	locn = search(sp, elt, &found);
	if(!found){
		assert(sp->count < sp-> length);
		sp->data[locn] = elt;
		sp->flags[locn] = 'F';
		sp->count++;
	}
}

/* Description: Finds element to be removed, once index is found then flag is marked as deleted.
 *
 * Complexity: best case O(1), worst case O(n)
 */
void removeElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
	int locn;
	bool found;
	locn = search(sp, elt, &found);
	if(found){
		sp->flags[locn] = 'D';
		sp->count--;
	}
	return;
}

/* Description: Searches for an element in the array, if it is found then it is returned.
 *
 * Complexity: best case O(1), worst case O(n)
 */
void *findElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
    int locn;
	bool found;
	locn = search(sp, elt, &found);
	if(found){
		return sp->data[locn];
	}
	return NULL;
}

/* Description: Returns a copy of all the spots in the orginial array that have elements in them.
 *
 * Complexity: O(n)
 */
void *getElements(SET *sp){
	assert(sp != NULL);
	void **copy;
	int i;
	int c = 0;
	copy = malloc(sizeof(void*)*sp->count);
	assert(copy);
	for(i = 0; i < sp->length; i++){
		if(sp->flags[i] == 'F'){
			copy[c++] = sp->data[i];
		}
	}
	return copy;
}
