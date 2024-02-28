/* File name: list.c
 *
 * Author: Jack DeMeulemeester
 * 
 * Date: 2/15/23
 * 
 * Description: Is an abstract data type allowing a user to manipulate inputed data. They can
 * manipulat the data by inserting, deleting, finding, and returning the data. Uses chain hashing
 * to efficiently store and access data.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "set.h"
#include <assert.h>

struct set{
	int length;
	int count;
    LIST **lists;
    int (*compare)();
    unsigned (*hash)();
};

/* Description: Creates and allocates memory for a set that includes an array of linked lists 
 * and other data such as length.
 *
 * Complexity: O(n)
*/
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET *sp;
    int i;
	sp = malloc(sizeof(SET));
	assert(sp);
	sp->lists = malloc(sizeof(LIST*)*(maxElts/20));
	assert(sp->lists);
    sp->compare = compare;
    assert(sp->compare);
    sp->hash = hash;
    assert(sp->hash);
	sp->length = (maxElts/20);
	sp->count = 0;
    for(i = 0; i < maxElts/20; i++)
    {
        sp->lists[i] = createList(sp->compare);
    }
	return sp;
}

/* Description: Loops through each index in the array destorying the list that exists there. Then frees the array and set.
 * 
 * Complexity: O(n^2)
*/
void destroySet(SET *sp){
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->length; i++)
    {
        destroyList(sp->lists[i]);
    }
    free(sp->lists);
    free(sp);
}

/* Description: Returns how many elements have been added to the array.
 * 
 * Complexity: O(1)
*/
int numElements(SET *sp){
	assert(sp != NULL);
    return sp->count;
}

/* Description: Uses hash to find insertion index. Then stores the data into the front of the linked list.
 * 
 * Complexity: O(n)
*/
void addElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
    int locn;
    void *data;
    locn = (*sp->hash)(elt) % sp->length;
    data = findItem(sp->lists[locn], elt);
	if(data == NULL){
    	sp->count++;
		addFirst(sp->lists[locn], elt);
	}
}

/* Description: Uses hash to find where element to be deleted is. If the element is found then it is removed.
 * 
 * Complexity: O(n)
*/
void removeElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
	int locn;
    void *data;
	locn = (*sp->hash)(elt) % sp->length;
    data = findItem(sp->lists[locn], elt);
	if(data != NULL){
		removeItem(sp->lists[locn], elt);
        sp->count--;
	}
	return;
}

/* Description: Loops through linked list at index where item should be. If it is found then it is returned.
 * 
 * Complexity: O(n)
*/
void *findElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
    int locn;
    void *data;
	locn = (*sp->hash)(elt) % sp->length;
    data = findItem(sp->lists[locn], elt);
	if(data != NULL){
		return data;
	}
	return NULL;
}

/* Description: Creates a loop to go through each element in the array. At each element
 * the data is obtained from the linked list and put one by one into a new array and the new array is returned.
 * 
 * Complexity: O(n^2)
*/
void *getElements(SET *sp){
	assert(sp != NULL);
	void **copy;
	void **elts;
	int j, k;
	int i = 0;
	copy = malloc(sizeof(void*)*sp->count);
	assert(copy);
	for(j = 0; j < sp->length; j++)
	{
		elts = getItems(sp->lists[j]);
		for(k = 0; k < numItems(sp->lists[j]); k++)
		{
			copy[i + k] = elts[k];
		}
		i += numItems(sp->lists[j]);
	}
	return copy;
}