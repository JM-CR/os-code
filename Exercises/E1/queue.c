// See queue.h for more info
// Author: Josue Mosiah Contreras Rocha
// File: queue.c
// Date: 05/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


// -----------------------------
// Public elements
// -----------------------------

// Public functions

/**
 * Gets the next node.
 *
 * @param item Element to traverse.
 * @return Pointer to the next element.
 */
Number_t *next( Number_t *item ) {
    return item->next;
}

/**
 * Creates a new node that is ready to insert.
 *
 * @param number Node's element.
 * @return New node.
 */
Number_t *create( int number ) {
    // Initialize
    Number_t *current = malloc(sizeof(Number_t));
    current->element = number;
    current->next = NULL;

    return current;
}

/**
 * Inserts a new node in the queue.
 *
 * @param ppRoot Pointer to the first node.
 * @param item Node to insert.
 */
void insert( Number_t **ppRoot, Number_t *item ) {
    // First item
    Number_t *pRoot = *ppRoot;
    if ( pRoot == NULL ) {
        *ppRoot = item;
        return;
    }

    // Traverse queue
    Number_t *currentNode = pRoot;
    while ( hasNext(currentNode) ) {
        currentNode = currentNode->next;
    }

    // Insert element
    currentNode->next = item;
}


/**
 * Prints the whole queue.
 *
 * @param pRoot Pointer to the first node.
 */
void printQueue( Number_t *pRoot ) {
    // Initialize
    printf("Elements: ");
    Number_t *node = pRoot;

    // Traverse
    while ( node != NULL ) {
        printf("%d ", node->element);
        node = node->next;
    }
}

/**
 * Checks if there is a node after the item.
 *
 * @param item Node to check.
 * @return True if there is the next element exists.
 */
bool hasNext( Number_t *item ) {
    return item->next == NULL ? false : true;
}

/**
 * Deletes the first node.
 * 
 * @param ppRoot Pointer to the first element
 */
void erase( Number_t **ppRoot ) {
    // Validation
    Number_t *pRoot = *ppRoot;
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
