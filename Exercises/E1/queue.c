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
 * Checks if there are more nodes after the item.
 *
 * @param item Node to check.
 * @return True if there is the next element exists.
 */
bool hasNext( Number_t *item ) {
    return item->next == NULL ? false : true;
}

/**
 * Deletes the first node.
 */
void erase(void) {
    // Validation
    if ( root == NULL )
        return;

    // Check next
    if ( !hasNext(root) ) {
        free(root);
        root = NULL;
    } else {
        Number_t *node = root;
        root = root->next;
        free(node);
    }
}

/**
 * Inserts a new node in the queue.
 *
 * @param item Node to insert.
 */
void insert( Number_t *item ) {
    // First item
    if ( root == NULL ) {
        root = item;
        return;
    }

    // Traverse queue
    Number_t *currentNode = root;
    while ( hasNext(currentNode) ) {
        currentNode = currentNode->next;
    }

    // Insert element
    currentNode->next = item;
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
 * Prints the whole queue.
 */
void printQueue( void ) {
    // Initialize
    printf("Elements: ");
    Number_t *node = root;

    // Traverse
    while ( node != NULL ) {
        printf("%d ", node->element);
        node = node->next;
    }
}
