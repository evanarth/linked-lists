/*
 *  Sort Linked Lists - March 10, 2015
 *  
 *  this program makes a linked list, then executes mergeSort to sort it
 */


#include <stdio.h>
#include <stdlib.h>
#include <vector>


#define NUM_ELEM  10

// declare the format of a node in the linked list
struct node {
    int x;
    char c;
    struct node *next;
};

// -----------------------------------------------------------------------------
// the merge-sort

// part 2: split a linked list into two smaller lists
void frontBackSplit (struct node* root, struct node** a, struct node** b) {
    
    struct node *fast, *slow;
    
    // check if root has length 0 or 1
    if ( root == NULL || root -> next == NULL ) {
        *a = root;
        *b = NULL;
        
    } else {
        
        // to split the linked list, we advance one list twice (fast) while we
        // advance the other once (slow). the result is two evenly-split lists
        slow = root;
        fast = root -> next;
        
        while ( fast != NULL ) {
            
            fast = fast -> next; // fast advance
            if ( fast != NULL ) {
                
                slow = slow -> next; // slow advance
                fast = fast -> next; // fast advance
            }
        }
    }

    // by now, slow is at the midway point. use that info, and output split lists
    *a = root;
    *b = slow -> next;
    slow -> next = NULL; // don't forget to chop the list in two!
}

// part 3: merge 2 lists that are sorted. merge recursively
struct node* mergeTwoSortedLists ( struct node* a, struct node* b ) {
    
    struct node* nodeOut = NULL;
    
    // check if node a or b are of length 0
    if ( a == NULL ) return b;
    if ( b == NULL ) return a;
    
    // append one node element at a time, based on (a->x <= b->x)
    if ( a->x <= b->x ) {
        nodeOut = a;
        nodeOut->next = mergeTwoSortedLists( a->next, b );
    } else {
        nodeOut = b;
        nodeOut->next = mergeTwoSortedLists( a, b->next );
    }
    
    return nodeOut;
}


// part 1: recursively bifurcate the list into pairs or single elements for sorting
void mergeSortLinkedList (struct node ** root) {
    
    struct node* firstNode = *root, *a, *b;
    
    // if length 0 or 1, then just return
    if ( firstNode == NULL || firstNode -> next == NULL )
        return;
    
    // split the linked list into two smaller lists, sort recursively
    frontBackSplit(firstNode, &a, &b); 
    mergeSortLinkedList(&a);
    mergeSortLinkedList(&b);
    
    // now merge the sorted arrays
    *root = mergeTwoSortedLists(a, b);
}

// -----------------------------------------------------------------------------

// append data to the beginning of the list
void push (struct node ** root, int newData) {
    struct node* newNode = (struct node *)malloc( sizeof(struct node) );
    newNode -> x = newData;
    newNode -> next = *root;
    *root = newNode;
}


// convert an input number to a linked list (forwards)
struct node * array2linkedList (int *a, int n) {
    
    if ( n < 1 )
        return NULL;
    
    int i = 0;
    struct node *root, *current, *nextNode;
    
    root = (struct node *)malloc( sizeof(struct node) );
    current = root;
    current -> x = a[i++];
    
    while ( i < n ) {
        
        // incriment nodes
        nextNode = (struct node *)malloc( sizeof(struct node) );
        current -> next = nextNode;
        current = nextNode;
        
        // input information
        current -> x = a[i++];
    }
    current -> next = NULL;
    
    return root;
}

// function for printing the contents of a linked list
void printlinkedlist ( struct node *root ) {
    
    struct node *current = root;
    while( current != NULL ) {
        printf( "%d  ", current -> x );
        current = current -> next ;
    }
}

//==============================================================================
int main( ) { // run the program
//==============================================================================
    
    struct node *root;
    
    // make input array
    int b[] = { 7, 7, 6, -7, -7, 12, 1, -2, 0, 15, 4, 11, 9, 100};
	printf("\n\nUnsorted array is:  ");
	for(int i = 0; i < 14; ++i)
		printf(" %d ", b[i]);
    printf(" %d ", 13);
    
    // convert array to linked list
    root = array2linkedList(b, 14);
    push(&root, 13);
    
    // sort
    mergeSortLinkedList(&root);
    
    // print output
	printf("\n\nSorted array is:  ");
	printlinkedlist(root);
    printf("\n\n");
    
    return 0;
}




