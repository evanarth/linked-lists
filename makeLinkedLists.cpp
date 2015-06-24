/*
 *  Making Linked Lists - March 10, 2015
 *  
 *  this program makes two linked lists each containing a number (one digit 
 *  per node). one method makes them in a forward-manner, the other backwards
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

// function for printing the contents of a linked list
//     set the current node to the root, then iteratively step 
//     through the list printing the contents of "c"
void printlinkedlist ( struct node *root ) {
    
    struct node *current = root;
    while( current != NULL ) {
        printf( "%c\n", current -> c );
        current = current -> next ;
    }
}


// convert an input number to a linked list (forwards)
struct node * linkedList2numberForwards (unsigned long long int input) {
    
    int smallestDigit;
    struct node *root, *current, *nextNode;
    char buffer [33];
    
    // start first node. if input is 0, still make it
    smallestDigit = input % 10;
    input = (input - smallestDigit) / 10;
    
    root = (struct node *)malloc( sizeof(struct node) );
    current = root;
    sprintf(buffer, "%d", smallestDigit);
    current -> c = buffer[0];
    
    // if more digits remain, then input them as well
    while (input != 0) {
        
        smallestDigit = input % 10;
        input = (input - smallestDigit) / 10;
        
        nextNode = (struct node *)malloc( sizeof(struct node) );
        current -> next = nextNode;
        current = nextNode;
        sprintf(buffer, "%d", smallestDigit);
        current -> c = buffer[0];
    }
    current -> next = NULL;
    
    return root;
}

// convert an input number to a linked list (backwards)
struct node * linkedList2numberBackwards (unsigned long long int input) {
    
    int smallestDigit;
    struct node *root, *current, *nextNode;
    char buffer [33];
    
    // start first node. if input is 0, still make it
    smallestDigit = input % 10;
    input = (input - smallestDigit) / 10;
    
    root = NULL;
    current = (struct node *)malloc( sizeof(struct node) );
    sprintf(buffer, "%d", smallestDigit);
    current -> c = buffer[0];
    current -> next = root;
    root = current;
    
    // if more digits remain, then input them as well
    while (input != 0) {
        
        smallestDigit = input % 10;
        input = (input - smallestDigit) / 10;
        
        current = (struct node *)malloc( sizeof(struct node) );
        sprintf(buffer, "%d", smallestDigit);
        current -> c = buffer[0];
        current -> next = root;
        root = current;
    }
    
    return root;
}


int main( ) {
    
    unsigned long long int input;
    struct node *root1, *root2, *root3;
    
    input = 999;
    root1 = linkedList2numberForwards(input);
    printlinkedlist(root1);
    
    printf("\n");
    
    input = 1;
    root2 = linkedList2numberBackwards(input);
    printlinkedlist(root2);
    
    printf("\n");
    
    return 0;
}




