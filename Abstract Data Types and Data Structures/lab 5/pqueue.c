/* File name: pqueue.c
 *
 * Author: Jack DeMeulemeester
 * 
 * Date: 3/1/23
 * 
 * Description: Creates a priority queue with the lowest value being prioritized. Allows the user to add to the queue,
 * remove from the queue, and get the number of elements that are in the queue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"
#include "pack.h"
#include <assert.h>

# define p(x) ((x - 1) / 2)
# define l(x) (x * 2 + 1)
# define r(x) (x * 2 + 2)

struct pqueue
{
    int count;
    int length;
    void **data;
    int (*compare)();
};

/* Description: Creates a priority queue structure. Initializes the queue and additional info in the struct.
 * 
 * Complexity: O(1)
*/
PQ *createQueue(int (*compare)())
{
    PQ *pq;
    pq = malloc(sizeof(PQ));
    assert(pq);
    pq->data = malloc(sizeof(void*)*10);
    assert(pq->data);
    pq->count = 0;
    pq->length = 10;
    pq->compare = compare;
    return pq;
}

/* Description: frees all data that was previously allocated.
 * 
 * Complexity: O(1)
*/
void destroyQueue(PQ *pq)
{
    assert(pq != NULL);
    free(pq->data);
    free(pq);
}

/* Description: Returns number of elements in the queue.
 * 
 * Complexity: O(1)
*/
int numEntries(PQ *pq)
{
    assert(pq != NULL);
    return pq->count;
}

/* Description: Adds an element to the priority queue. If the current queue is full then it creates a new
 * queue with a size of the original size squared. Finds proper spot for element to be inserted in the heap.
 * 
 * Complexity: O(logn)
*/
void addEntry(PQ *pq, void *entry)
{
    assert(pq != NULL && entry != NULL);
    int idx;

    if(pq->count == pq->length)
    {
        pq->length = pq->length*pq->length;
        pq->data = realloc(pq->data, sizeof(void*)*pq->length);
        assert(pq->data);
    }

    idx = pq->count++;
    while(idx > 0 && (*pq->compare)(entry, pq->data[p(idx)]) < 0)
    {
        pq->data[idx] = pq->data[p(idx)];
        idx = p(idx);
    }
    pq->data[idx] = entry;
}

/* Description: Removes top of heap and then loops through heap fixing it so it is balanced. It does this
 * by comparing the children and if the smallest child is smaller than the final item in queue, then it takes
 * the place of it's parent. Once there is no more children to the left, the last item in queue is assigned to 
 * where the last index was.
 * 
 * Complexity: O(logn)
*/
void *removeEntry(PQ *pq)
{
    assert(pq != NULL && pq->count > 0);
    int idx = 0;
    int child;
    void *min = pq->data[0];
    void *entry = pq->data[--pq->count];

    while(l(idx) < pq->count)
    {
        child = l(idx);
        if(r(idx) < pq->count)
        {
            if((*pq->compare)(pq->data[l(idx)], pq->data[r(idx)]) > 0)
                child = r(idx);
        }
        if((*pq->compare)(entry, pq->data[child]) > 0)
        {
            pq->data[idx] = pq->data[child];
            idx = child;
        }
        else
            break;
    }
    pq->data[idx] = entry;
    return min;
}