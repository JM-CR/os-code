// See queue.h for more info
// Author: Hector Jair Hernandez Cortes
// File: burst.c
// Date: 05/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include "burst.h"


// -----------------------------
// Private elements
// -----------------------------

// Private functions

/**
 * 
 */
static int random(int n) {

}


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
 * 
 */
Node_t *create_cnode(void) {

}

Node_t *create_inode(void) {

}