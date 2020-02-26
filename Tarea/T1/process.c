// See process.h for more info
// Author: Josue Mosiah Contreras Rocha
// File: process.c
// Date: 17/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include "process.h"


// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */

Node_t *next( Node_t *item ) {
    return item->next;
}

void insert( Node_t **ppRoot, Node_t *item ) {
    // First item
    Node_t *currentNode = *ppRoot;
    if ( currentNode == NULL ) {
        *ppRoot = item;
        return;
    }

    // Traverse queue
    while ( hasNext(currentNode) )
        currentNode = currentNode->next;

    // Insert item
    currentNode->next = item;
}

void printQueue( Node_t *pRoot ) {
    // Initialize
    printf("Elements: ");
    Node_t *node = pRoot;

    // Traverse
    while ( node != NULL ) {
        printf("(%c, %2d) ", node->type, node->lifeTime);
        node = node->next;
    }
    printf("\n");
}

bool hasNext( Node_t *item ) {
    return item->next == NULL ? false : true;
}

void erase( Node_t **ppRoot ) {
    // Validation
    Node_t *pRoot = *ppRoot;
    if ( pRoot == NULL )
        return;

    // Check next
    if ( !hasNext(pRoot) ) {
        free(pRoot);
        *ppRoot = NULL;
    } else {
        *ppRoot = (*ppRoot)->next;
        free(pRoot);
    }
}
