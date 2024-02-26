// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6 {
    size_t list_length(const node* head_ptr){
    // Library facilities used: cstdlib
    
	    const node *cursor;
	    size_t answer;

	    answer = 0;
	    for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	        ++answer;

	    return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry) {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
        if (start_ptr==NULL || start_ptr==end_ptr) {
            head_ptr=NULL;
            tail_ptr=NULL;
            return;
        }
        head_ptr = new node(start_ptr-> data(), NULL);
        tail_ptr = head_ptr;
        while(start_ptr->link() != end_ptr){
            start_ptr=start_ptr->link();
            //make next node->
            tail_ptr->set_link(new node(start_ptr->data(), NULL));
            tail_ptr = tail_ptr->link();
        }
        return;
    }

    size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		size_t count = 0;
		const node* current = head_ptr;
		// go through list, see if the node we r on is target, ++
        while(current != NULL) {
			if (current->data() == target) { 
				count++;
			}
			current = current->link();
		}
		return count;
	}
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		assert(position > 0 && position <= list_length(head_ptr) + 1);
		if (position == 1) {
			// insert at head (supa easy)
            list_head_remove(head_ptr);
            list_head_insert(head_ptr, entry); 
		} else {
			node *prev = head_ptr;
            //start at 1 cuz we checked head!!!
			for (int i = 1; i < position - 1; ++i) {
				prev = prev->link(); 
			}
			list_insert(prev, entry); 
			position++;
		}
		return;
	}

    node::value_type list_remove_at(node*& head_ptr, size_t position) {
		assert(position > 0 && position <= list_length(head_ptr));
		node::value_type data; // have to do this twice!!!
		if (position == 1) {
			data = head_ptr->data();
			list_head_remove(head_ptr); 
		} else {
			node *prev = head_ptr;
            //head is already checked!!!!!
			for (int i = 1; i < position - 1; ++i) {
				prev = prev->link(); 
			} // get to where the target is via loop
			node *remove_ptr = prev->link();
			data = remove_ptr->data(); 
    		prev->set_link(remove_ptr->link( ));
			// no memerie leaks!!!
            delete remove_ptr;
		}
        //return the saved byt deleted data!!!
		return data;
	}

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		assert (start <= finish && 1 <= start && finish <= list_length(head_ptr)); 
		for (int i = 1; i < start; ++i) {
			head_ptr = head_ptr->link(); 
		} // find first node w/ while loop!
		node *headNew = NULL;
		node *cursor = NULL;
		for (int i = start; i <= finish; ++i) {
			// check to see if list has a head!
            if (headNew == NULL) {
				headNew = new node(head_ptr->data(), NULL); 
				cursor = headNew;
			} else {
				// amke 1 new node for the new list
                cursor->set_link(new node(head_ptr->data(),NULL)); 
				cursor = cursor->link(); 
			}
			head_ptr = head_ptr->link(); 
		}
		return headNew;
	}

    void list_print (const node* head_ptr) {
		//std::cout << head_ptr->data
		while (head_ptr != NULL) {
			std::cout << head_ptr->data() << ", " ;
            //if(head_ptr->link() == NULL){
				//break;
			//}
			head_ptr = head_ptr->link();
		} // go through list, print em all!
		//std::cout<< '\b \b \b';
		//std::cout << head_ptr->data();
		std::cout<< "\n";
        //std::cout << std::endl; 
		return;
	}

    void list_remove_dups(node* head_ptr) {
		//for loop, but using the fr nodes!!
        for (node* i = head_ptr; i != NULL; i = i->link()) {
			node::value_type target = i->data(); 
			node *prev = i; 
			while (prev->link() != NULL) {
				if (prev->link()->data() == target) {
					list_remove(prev); 
				}
				else {
					prev = prev->link();
				}
			}
		}
		return;
	}
    
    //using floyd stuff *eyeroll*
    node* list_detect_loop (node* head_ptr) {
		node* slow = head_ptr;
		node* fast = head_ptr;
        //make the slow walker and gast one!!

		while (fast != NULL && fast->link() != NULL) {
            //check that next isnt null too!!
			slow = slow->link(); 
			fast = fast->link()->link(); // double step!!
			if (fast == slow) {
				break; // uh oh loop! unless they r null!
			}
		}
	    if (fast == NULL || fast->link() == NULL) {
			return NULL;
            //woohoo!! no loop!
		}
		
		// Find start of loop
		slow = head_ptr;
		while (slow != fast) {
			slow = slow->link(); 
			fast = fast->link();
		}
        //they meet at the start of the loop!!!!
		return slow;
	}
}