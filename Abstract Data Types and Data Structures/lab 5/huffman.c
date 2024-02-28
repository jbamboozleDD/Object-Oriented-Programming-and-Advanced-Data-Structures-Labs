/* File name: huffman.c
 *
 * Author: Jack DeMeulemeester
 * 
 * Date: 3/8/23
 * 
 * Description: Gathers elements from a file and puts the number of times a character is used in the file 
 * into a priority queue. Then prints out how many bits each character used and the total number of bits.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pack.h"
#include "pqueue.h"
#include <assert.h>
typedef struct node ND;


int counts[257];
ND *nodes[257];

/* Description: Reads file and puts number of occurances of each character into respective spot in ascii array.
 * 
 * Complexity: O(n)
*/
void countElm(char *file)
{
    int c;
	FILE *fp;
	fp = fopen(file, "rb");
	assert(fp != NULL);
 	while((c = getc(fp))!=EOF)
	{
        counts[c]++;
	}
	fclose(fp);
	return;
}

/* Description: Makes a node containing number of occurances of a character and can assign parent pointers when 
 * making huffman tree.
 * 
 * Complexity: O(1)
*/
static ND *mknode(int data, ND *left_node, ND *right_node)
{
    ND *nd;
    nd = malloc(sizeof(ND));
    assert(nd);
    nd->count = data;
    nd->parent = NULL;
    if(left_node != NULL)
        left_node->parent = nd;
    if(right_node != NULL)
        right_node->parent = nd;
    return nd;
}

/* Description: Compares the counts of two different nodes to find if one is smaller than the other or
 * if they equal each other.
 * 
 * Complexity: O(1)
*/
int compare(ND *x1, ND *x2)
{
    assert(x1 != NULL && x2 != NULL);
    return (x1->count < x2->count) ? -1 : (x1->count > x2->count);
}

/* Description: Goes down huffman tree counting how far a node is from the root.
 * 
 * Complexity: O(logn)
*/
int depth(ND *nd)
{
    if(nd->parent == NULL)
        return 0;
    return 1 + depth(nd->parent);
}

/* Description: Combines all functions to peform primary description at top of file
 * 
 * Complexity: O(n)
*/
int main(int argc, char *argv[])
{
    assert(argc == 3 && argv != NULL);
    ND *l, *r;
    int i, j, c;                                            //Declares variables and initializes arrays.
    for(i = 0; i < 257; i++)
    {
        counts[i] = 0;
        nodes[i] = NULL;
    }

    countElm(argv[1]);                                      //Gets number of occurances of each character

    PQ *pq = createQueue(compare);
    for(j = 0; j < 257; j++)
    {
        if(counts[j] != 0)
        {
            nodes[j] = mknode(counts[j], NULL, NULL);       //makes priority queue and adds elements to it
            addEntry(pq, nodes[j]);
        }
    }
    ND *eofile = malloc(sizeof(ND));                        //adds marker for end of file to priority queue
    assert(eofile);
    eofile->count = counts[256];
    eofile->parent = NULL;
    nodes[256] = eofile;
    addEntry(pq, nodes[256]);

    while(numEntries(pq) > 1)
    {
        l = removeEntry(pq);
        r = removeEntry(pq);
        addEntry(pq, mknode(l->count + r->count, l, r));       //goes through priority queue making a huffman tree
    }

    for(c = 0; c < 257; c++)
    {
        if(nodes[c] != NULL)                                    //prints out all characters used in file and shows how many bits
        {                                                       //they used up when saved
            printf(isprint(c) ? "%c" : "%03o", c);
            printf(": %d x %d bits = %d bits\n", counts[c], depth(nodes[c]), (counts[c]*depth(nodes[c])));
        }
    }

    pack(argv[1], argv[2], nodes);                              //sends data to be compressed and saved
    return 0;
}