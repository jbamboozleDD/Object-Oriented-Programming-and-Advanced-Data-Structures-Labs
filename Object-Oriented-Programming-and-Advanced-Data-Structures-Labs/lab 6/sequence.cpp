//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init(){
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence::sequence(){
        init();
    }

    //Copy Constructor
    //uses = operator since you are making the new object the same as the one given
    sequence::sequence(const sequence& source){
        init();
        *this = source;
    }

    //deconstructor
    sequence::~sequence(){
        list_clear(head_ptr);
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void sequence::start(){
        if(many_nodes == 0){    //edge case when no nodes
            cursor = NULL;
            precursor = NULL;
        }else{
            cursor = head_ptr;  //normal case
            precursor = NULL;
        }
        return;
    }

    void sequence::end(){
        if(many_nodes == 0){    //edge case when no nodes
            cursor = NULL;
            precursor = NULL;
        }else if(many_nodes == 1){  //edge case when only one node
            cursor = head_ptr;
            precursor = NULL;
        }else{
            cursor = tail_ptr;  //normal case
            precursor = list_locate(head_ptr, many_nodes - 1);
        }
        return;
    }

    void sequence::advance(){
        assert(is_item());
        if(cursor == tail_ptr){     //edge case if cursor already at end of list
            cursor = NULL;
            precursor = tail_ptr;
        }else{
            precursor = cursor;     //normal case
            cursor = cursor->link();
        }
        return;
    }

    void sequence::insert(const value_type& entry){
        if(!is_item() || cursor == head_ptr){   //if list is empty or you are at beginning of list
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            many_nodes++;
            if(many_nodes == 1)     //if you just created a new list, tail is initialized
                tail_ptr = head_ptr;

        }else{
            list_insert(precursor, entry);
            cursor = precursor->link();
            many_nodes++;
            if(cursor->link() == NULL)      //if item was inserted at end of list, make it the new tail
                tail_ptr = cursor;
        }
        return;
    }

    void sequence::attach(const value_type& entry){
        if(is_item()){                     //normal case
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = precursor->link();
            many_nodes++;
            if(cursor->link() == NULL)  //if item was attached at end of list, make it the new tail
                tail_ptr = cursor;
        }else if(many_nodes == 0){      //empty list case
            list_head_insert(head_ptr, entry);
            tail_ptr = head_ptr;
            cursor = head_ptr;
            many_nodes++;
        }else{                      //if no there is no current item, attach on back
            precursor = tail_ptr;
            list_insert(precursor, entry);
            cursor = precursor->link();
            tail_ptr = cursor;
            many_nodes++;
        }
        return;
    }

    void sequence::operator =(const sequence& source){
        if(many_nodes != 0)
            list_clear(head_ptr);
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;
        int pos = 1;
        node* temp = source.head_ptr;
        if(temp == source.cursor){      //this if and else copy over the cursor and precursor from source
            precursor = NULL;
            cursor = head_ptr;
        }else{
            while(temp->link() != source.cursor){
                pos++;
                temp = temp->link();
            }
            precursor = list_locate(head_ptr, pos);
            cursor = precursor->link();
        }
    }

    void sequence::remove_current(){
        assert(is_item());
        if(cursor == head_ptr){     //if item is at beginning of list
            list_head_remove(head_ptr);
            cursor = head_ptr;
            many_nodes--;
            if(many_nodes == 0){    //if list is now empty
                tail_ptr = NULL;
                cursor = NULL;
                precursor = NULL;
            }
        }else{
            list_remove(precursor);
            many_nodes--;
            if(precursor->link() == NULL){      //if item removed was last in list then make cursor and tail equal to new last item
                tail_ptr = precursor;
                cursor = precursor;
                precursor = list_locate(head_ptr, many_nodes - 1);
            }else
                cursor = precursor->link();
        }
        return;
    }

    // CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size() const{
        return list_length(head_ptr);
    }

    bool sequence::is_item() const{
        if(cursor != NULL)
            return true;
        return false;
    }

    sequence::value_type sequence::current() const{
        assert(is_item());
        return cursor->data();
    }
}