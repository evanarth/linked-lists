/*
 *  Linked list test code
 *      written by Evan Arthur, Sept 24, 2014
 *  
 *  This program runs simple examples of using and handling linked
 *  lists with three main parts:
 *  
 *      create and read a linked list
 *  
 *      reverse the order of nodes in a linked list
 *  
 *      load memory addresses into an array for convenient out-of-order
 *      accessing of data in each element/node
 *  
 *  
 */


#include <stdio.h>
#include <stdlib.h>
#include <vector>


#define NUM_ELEM  10

// declare the format of a node in the linked list
struct node {
    int x;
    struct node *next;
};

// function for printing the contents of a linked list
//     set the current node to the root, then iteratively step 
//     through the list printing the contents of "x"
void printlinkedlist ( struct node *root ) {
    
    struct node *current = root;
    while( current != NULL ) {
        printf( "%d\n", current -> x );
        current = current -> next ;
    }
}


int main( ) {
    
    //--------------------------------------------------------------------------
    
    // 2 nodes are allocated:
    //     "root" is the first node of the list
    //     "current" is the current node we are observing
    struct node *root, *current;
    
    // create linked list:
    //     allocate new first node in list, define "x", 
    //     point the root to the new first node
    root = NULL;
    for ( int i = 0; i < NUM_ELEM; i++ ) {
        
        current = (struct node *)malloc( sizeof(struct node) );
        current -> x = NUM_ELEM - i;
        current -> next = root;
        root = current;
    }
    
    printf("\noriginal linked list data\n");
    printlinkedlist ( root );
    
    //--------------------------------------------------------------------------
    
    // reverse the order of the linked list:
    //     load up next, current, and previous nodes, swap
    //     the next and previous memory addresses, then step through the list.
    struct node *previousNode, *nextNode;
    previousNode = NULL;
    current = root;
    while( current != NULL ) {
        
        nextNode = current -> next; // incriment next
        current -> next = previousNode; // address swap
        previousNode = current;     // incriment previous
        current = nextNode;         // incriment current
    }
    root = previousNode;
    
    printf("\nreversed linked list data\n");
    printlinkedlist ( root );
    
    //--------------------------------------------------------------------------
    
    // make the linked list random-access by making a vector of pointers:
    //     cast each linked list node address as an *int
    std::vector< struct node * > pointer_list;
    current = root;
    while ( current != NULL ) {
        
        pointer_list.push_back ( current );
        current = current -> next ;
    }
    
    // print every other node's "x" in reverse order to display out-of-order
    // accessing of the data
    printf("\nreversed-order, every other node of linked list data\n");
    for ( int i = pointer_list.size()-1; i > 0; i -= 2 ) {
        printf( "%d\n", pointer_list[i] -> x );
    }
    
    return 0;
}




