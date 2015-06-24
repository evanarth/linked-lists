/*
 *  exploring binary trees - March 14, 2015 (pi day!)
 *  
 *  this program makes a binary tree and then checks if it's balanced
 *  
 */


#include <stdio.h>
#include <stdlib.h>
#include <vector>

struct tree {
    float val;
    struct tree *left, *right;
};

typedef struct tree node;

// -----------------------------------------------------------------------------
// make the tree

void insertNodes( node ** tree, node * item ) {
    if ( *tree == NULL ) {
        *tree = item;
        return;
    }
    if ( item->val < (*tree)->val )
        insertNodes( &(*tree)->left, item );
    else if( item->val > (*tree)->val )
        insertNodes( &(*tree)->right, item );
}

void printTree(node * tree) {
    if(tree->left) {
        printf("l -  ");
        printTree(tree->left);
    }
    printf(" %f\n",tree->val);
    if(tree->right) {
        printf("r -  ");
        printTree(tree->right);
    }
}

// -----------------------------------------------------------------------------
// check if it's balanced

int checkHeight ( node * tree ) {
    
    // null case
    if ( tree == NULL )
        return 0;
    
    // check left side
    int leftHeight = checkHeight( tree->left );
    if ( leftHeight == -1 )
        return -1; // not balenced
    
    // check right side
    int rightHeight = checkHeight( tree->right );
    if ( rightHeight == -1 )
        return -1; // not balenced
    
    // is current node balenced?
    int heightDifference = abs(leftHeight - rightHeight);
    if ( heightDifference > 1 )
        return -1; // not balenced
    else
        return std::max(leftHeight, rightHeight) + 1;
}

//==============================================================================
int main( ) { // run the program
//==============================================================================
    
    node *root, *current;
    int i;
    
    root = NULL;
    
    for ( i = 0; i < 10; i++ ) {
        current = (node *)malloc( sizeof(node) );
        current -> left = current -> right = NULL;
        current -> val = 0.001 * (float)rand();
        printf("%f\n", current -> val);
        insertNodes( &root, current );
    }
    
    printTree(root);
    
    int treeHeight = checkHeight(root);
    if ( treeHeight == -1 )
        printf("not balanced\n");
    else
        printf("tree height is %d\n", treeHeight);
    
    return 0;
}




