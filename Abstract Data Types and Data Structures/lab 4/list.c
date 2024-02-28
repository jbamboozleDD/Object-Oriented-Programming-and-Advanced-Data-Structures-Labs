/* File name: list.c
 *
 * Author: Jack DeMeulemeester
 * 
 * Date: 2/15/23
 * 
 * Description: Acts as an abstract data type for set.c. It takes calls from set.c to manipulate data.
 * It manipulates data by creating a circularly linked list to hold data, deleteing these lists,
 * finding the data, and getting the data.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <assert.h>
#define NODE struct node

struct node{
    void *data;
    NODE *next;
    NODE *prev;
};

struct list{
    int count;
    NODE *head;
    int (*compare)();
};

/* Description: Creates a circularly linked list with a dummy node which is where the head pointer points to.
 * 
 * Complexity: O(1)
*/
LIST *createList(int (*compare)())
{
    LIST *lp;
    NODE *np;
    lp = malloc(sizeof(LIST));
    assert(lp);
    np = malloc(sizeof(NODE));
    assert(np);
    lp->head = np;
    np->next = np;
    np->prev = np;
    lp->count = 0;
    lp->compare = compare;
    return lp;
}

/* Description: Loops through the circularly linked list freeing each node. Then frees rest of allocated memory.
 * 
 * Complexity: O(n)
*/
void destroyList(LIST *lp)
{
    assert(lp != NULL);
    NODE *temp;
    while(lp->head->prev != lp->head)
    {
        temp = lp->head->prev;
        lp->head->prev = lp->head->prev->prev;
        lp->head->prev->next = lp->head;
        free(temp);
    }
    free(lp->head);
    free(lp);
}

/* Description: Returns how many nodes are in the circularly linked list.
 * 
 * Complexity: O(1)
*/
int numItems(LIST *lp)
{
    assert(lp != NULL);
    return lp->count;
}

/* Description: Adds a new node at front of circularly linked list, next from the dummy node. Appoints pointers.
 * 
 * Complexity: O(1)
*/
void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *np;
    np = malloc(sizeof(NODE));
    assert(np);
    np->data = item;
    np->next = lp->head->next;
    np->prev = lp->head;
    lp->head->next->prev = np;
    lp->head->next = np;
    lp->count++;
}

/* Description: Adds a new node at back of circularly linked list, previous from the dummy node. Appoints pointers.
 * 
 * Complexity: O(1)
*/
void addLast(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *np;
    np = malloc(sizeof(NODE));
    assert(np);
    np->data = item;
    np->next = lp->head;
    np->prev = lp->head->prev;
    lp->head->prev->next = np;
    lp->head->prev = np;
    lp->count++;
}

/* Description: Frees the first node in the circularly linked list. Moves pointers around the node to be freed.
 * Returns the node that is removed.
 *
 * Complexity: O(1)
*/
void *removeFirst(LIST *lp)
{
    assert(lp != NULL && lp->count != 0);
    void *dt;
    dt = malloc(sizeof(void*));
    assert(dt);
    NODE *temp;
    temp = lp->head->next;
    memcpy(dt, lp->head->next->data, sizeof(void*));
    lp->head->next = lp->head->next->next;
    lp->head->next->prev = lp->head;
    free(temp);
    lp->count--;
    return dt;
}

/* Description: Frees the last node in the circularly linked list. Moves pointers around teh node to be freed.
 * Returns the node that is removed.
 * 
 * Complexity: O(1)
*/
void *removeLast(LIST *lp)
{
    assert(lp != NULL && lp->count != 0);
    void *dt;
    dt = malloc(sizeof(void*));
    assert(dt);
    NODE *temp;
    temp = lp->head->prev;
    memcpy(dt, lp->head->prev->data, sizeof(void*));
    lp->head->prev = lp->head->prev->prev;
    lp->head->prev->next = lp->head;
    free(temp);
    lp->count--;
    return dt;
}

/* Description: Returns data from the first node in circularly linked list.
 * 
 * Complexity: O(1)
*/
void *getFirst(LIST *lp)
{
    assert(lp != NULL);
    void *data;
    data = malloc(sizeof(void*));
    assert(data);
    memcpy(data, lp->head->next->data, sizeof(void*));
    return data;
}

/* Description: Returns data form the last node in circularly linked list.
 * 
 * Complexity: O(1)
*/
void *getLast(LIST *lp)
{
    assert(lp != NULL);
    void *data;
    data = malloc(sizeof(void*));
    assert(data);
    memcpy(data, lp->head->prev->data, sizeof(void*));
    return data;
}

/* Description: Loops through circularly linked list looking for certain data. If the data is found then the node
 * is freed from memory and the pointers around it are adjusted accordingly.
 * 
 * Complexity: O(n)
*/
void removeItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *temp;
    temp = lp->head->next;
    while(temp != lp->head)
    {
        if((*lp->compare)(temp->data, item) == 0)
            break;
        temp = temp->next;
    }
    if(temp != lp->head)
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
        lp->count--;
    }

}

/* Description: Loops through the circularly linked list looking for data. If the data is found
 * then is returned, if not then NULL indicating not found is returned.
 * 
 * Complexity: O(n)
*/
void *findItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *p;
    p = lp->head->next;
    while(p != lp->head)
    {
        if((*lp->compare)(p->data, item) == 0)
            return p->data;
        p = p->next;
    }
    return NULL;
}

/* Description: Returns the data from all the nodes in the circularly linked list.
 * 
 * Complexity: O(n)
*/
void *getItems(LIST *lp)
{
    assert(lp != NULL);
	void **copy;
	int i;
	NODE *p;
    p = lp->head->next;
	copy = malloc(sizeof(void*)*lp->count);
	assert(copy);
	for(i = 0; i < lp->count; i++){
        copy[i] = p->data;
        p = p->next;
	}
	return copy;
}