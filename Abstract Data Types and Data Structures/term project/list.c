/* File name: list.c
 *
 * Author: Jack DeMeulemeester
 * 
 * Date: 2/28/23
 * 
 * Description: Creates a data structure with an array in a node. This allows
 * for an array to be extended without reallocating memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <assert.h>
#define HP lp->head
typedef struct node NODE;
int size = 100;

struct node{
    void **data;
    int front;
    int countN;
    int sizeN;
    NODE *next;
    NODE *prev;
};


struct list{
    int count;
    NODE *head;
    int nodesCount;
};


/* Description: creates the linked list and all other associated data.
 *
 * Complexity: O(1)
*/
LIST *createList(void)
{
    LIST *lp;
    NODE *np;
    lp = malloc(sizeof(LIST));
    assert(lp);
    np = malloc(sizeof(NODE));
    assert(np);
    HP = np;
    np->sizeN = 0;
    np->front = 0;
    np->next = np;
    np->prev = np;
    lp->count = 0;
    lp->nodesCount = 0;
    return lp;
}


/* Description: deletes all memory that was allocated for linked list.
 *
 * Complexity: O(n)
*/
void destroyList(LIST *lp)
{
    assert(lp != NULL);
    NODE *temp;
    NODE *node = HP->prev;
    while(node != HP)
    {
        temp = node->prev;
        free(node->data);
        free(node);
	    node = temp;
    }
    free(HP);
    free(lp);
}


/* Description: Gives the number of elements in the data structure.
 *
 * Complexity: O(1)
*/
int numItems(LIST *lp)
{
    assert(lp != NULL);
    return lp->count;
}


/* Description: If there are no nodes or if the array in the next node is full
 * then it creates a new node in the linked list adding the new element to it.
 * Otherwise it adds the data to the next node in the next open spot
 *
 * Complexity: O(1)
*/
void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *np;
    lp->nodesCount++;
    if(lp->count == 0 || HP->next->countN == HP->next->sizeN)
    {
        np = malloc(sizeof(NODE));
        assert(np);
        np->countN = 0;
        np->sizeN = lp->nodesCount * 2;
        np->data = malloc(sizeof(void*)*np->sizeN);
        np->front = 0;
        np->data[np->countN ++] = item;
        np->prev = HP;
        np->next = HP->next;
        HP->next->prev = np;
        HP->next = np;
    }
    else
    {
        HP->next->data[(HP->next->countN + HP->next->front) % HP->next->sizeN] = item;
        HP->next->countN++;
    }
    lp->count++;
}


/* Description: If there are no nodes or if the array in the previous node is full
 * then it creates a new node in the linked list adding the new element to it.
 * Otherwise it adds the data to the previous node in the next open spot.
 *
 * Complexity: O(1)
*/
void addLast(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *np;
    lp->nodesCount++;
    if(lp->count == 0 || HP->prev->countN == HP->prev->sizeN)
    {
        np = malloc(sizeof(NODE));
        assert(np);
        np->countN = 0;
        np->sizeN = lp->nodesCount * 2;
        np->data = malloc(sizeof(void*)*np->sizeN);
        np->front = 0;
        np->data[np->countN ++] = item;
        np->prev = HP->prev;
        np->next = HP;
        HP->prev->next = np;
        HP->prev = np;
    }
    else
    {
        HP->prev->data[(HP->prev->countN + HP->prev->front) % HP->prev->sizeN] = item;
        HP->prev->countN++;
    }
    lp->count++;
}


/* Description: removes the first item in the linked list
 *
 * Complexity: O(n)
*/
void *removeFirst(LIST *lp)
{
    assert(lp != NULL && lp->count > 0 && HP->next != HP);
    void *temp;
    while(HP->next->countN == 0)
    {
	    HP->next = HP->next->next;
    }

	temp = HP->next->data[HP->next->front];
	HP->next->front = (HP->next->front + 1) % HP->next->sizeN;
	HP->next->countN --;
	lp->count--;
    return temp;
}


/* Description: removes the last item from the linked list
 *
 * Complexity: O(n)
*/
void *removeLast(LIST *lp)
{
    assert(lp != NULL && lp->count != 0);
   	NODE *node = HP->prev;
	void *temp;
	while(node->countN == 0)
    {
        node = node->prev;
	}

	temp = node->data[(node->countN + node->front - 1) % node->sizeN];
	node->countN--;
	lp->count--;
	return temp;
}


/* Description: returns the data item at the given index
 *
 * Complexity: O(n)
*/
void *getItem(LIST *lp, int index)
{
    assert(lp != NULL && index >= 0 && index < lp->count);
    NODE *temp = HP->next;
    int i = index;
    while(i > temp->countN - 1)
    {
        i = i - temp->countN;
        temp = temp->next;
    }
    i = (temp->front + i) % temp->sizeN;
    return temp->data[i];
}


/* Description: replaces data at the index given with the item it is given
 *
 * Complexity: O(n)
*/
void setItem(LIST *lp, int index, void *item)
{
    assert(lp != NULL && index >= 0 && index < lp->count);
    NODE *temp = HP->next;
    int i = index;
    while(i > temp->countN - 1)
    {
        i = i - temp->countN;
        temp = temp->next;
    }
    i = (temp->front + i) % temp->sizeN;
    temp->data[i] = item;
}

/* Description: returns first item in linked list
 *
 * Complexity: O(n)
*/
void *getFirst(LIST *lp){
	assert(lp != NULL && lp->count != 0);
	NODE *node = HP->next;
	while(node->countN == 0)
    {
		node = node->next;
	}
	return (node->data[node->front]);
}

/* Description: returns last item in linked list
 *
 * Complexity: O(n)
*/
void *getLast(LIST *lp){
    assert(lp != NULL && lp->count != 0);
	NODE *node = HP->prev;
    while(node->countN == 0)
    {
        node = node->prev;
    }
	return(node->data[(node->countN + node->front - 1) % node->sizeN]);
}