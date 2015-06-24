/*
 *  Adding Linked Lists - March 10, 2015
 *  
 *  this program makes two linked lists each containing a number (one digit 
 *  per node). then it adds them, thereby generating a third linked list
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
// adding the lists

// add 2 linked lists
struct node * addLinkedLists1 (struct node * inRoot1, struct node * inRoot2) {
    
    int carry = 0, thisDigit;
    struct node *rootOut, *nextNode, *root1 = inRoot1, *root2 = inRoot2;
    
    rootOut = NULL;
    
    while (root1 != NULL || root2 != NULL || carry != 0) {
        
        // here we avoid "atoi" because it needs an input string 
        // run through all addition possibilities
        if ( root1 != NULL && root2 != NULL )
            thisDigit = root1->c - '0' + root2->c - '0' + carry;
        else if ( root1 != NULL && root2 == NULL)
            thisDigit = root1->c - '0' + carry;
        else if ( root1 == NULL && root2 != NULL)
            thisDigit = root2->c - '0' + carry;
        else if ( root1 == NULL && root2 == NULL)
            thisDigit = carry;
        
        // address the carry-the-one integer
        if (thisDigit > 9) {
            thisDigit -= 10;
            carry = 1;
        } else {
            carry = 0;
        }
        
        // add information to the output linked list and advance it
        nextNode = (struct node *)malloc( sizeof(struct node) );
        nextNode -> c = thisDigit + '0';
        nextNode -> next = rootOut;
        rootOut = nextNode;
        
        // advance the input linked lists
        if ( root1 != NULL )
            root1 = root1 -> next;
        if ( root2 != NULL )
            root2 = root2 -> next;
    }
    
    return rootOut;
}

// add 2 linked lists
struct node * addLinkedLists2 (struct node * inRoot1, struct node * inRoot2) {
    
    int carry = 0, thisDigit, root1Digit, root2Digit;
    struct node *rootOut, *nextNode, *root1 = inRoot1, *root2 = inRoot2;
    
    rootOut = NULL;
    
    while (root1 != NULL || root2 != NULL || carry != 0) {
        
        // here we avoid "atoi" because it needs an input string 
        // first deal with the two input nodes
        if ( root1 != NULL ) {
            root1Digit = root1->c - '0'; // convert to integer for addition
            root1 = root1 -> next;       // advance the node
        } else {
            root1Digit = 0;              // no contribution if node is a NULL
        }
        if ( root2 != NULL ) {
            root2Digit = root2->c - '0';
            root2 = root2 -> next;
        } else {
            root2Digit = 0;
        }
        
        // add the digits
        thisDigit = root1Digit + root2Digit + carry;
        
        // address the carry-the-one integer
        if (thisDigit > 9) {
            thisDigit -= 10;
            carry = 1;
        } else {
            carry = 0;
        }
        
        // add information to the output linked list and advance it
        nextNode = (struct node *)malloc( sizeof(struct node) );
        nextNode -> c = thisDigit + '0';
        nextNode -> next = rootOut;
        rootOut = nextNode;
    }
    
    return rootOut;
}

// -----------------------------------------------------------------------------

// function for printing the contents of a linked list
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
    
    root3 = addLinkedLists1(root1, root2);
    printlinkedlist(root3);
    
    printf("\n");
    
    root3 = addLinkedLists2(root1, root2);
    printlinkedlist(root3);
    
    return 0;
}




