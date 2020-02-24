// Specific functions to create and handle a queue.
// Author: Hector Jair Hernandez Cortes
// File: burst.h
// Date: 05/02/20

#ifndef BURST_H
#define BURST_H

// ------------------------------------------
// System specific headers
// ------------------------------------------
#include <stdbool.h>


// -----------------------------
// Public interface
// -----------------------------

/* Types declarations */

typedef struct Node {
    int createdAt; 
    int lifeTime;    
    char type;
    struct Node *next;
} Node_t;

/* Function prototypes */

/**
 * Creates a new node ready to insert in the queue.
 *
 * @param type Node's type: 'c' = CPU or 'e' = I/O.
 * @param isFirst True for the root node; otherwise, false.
 * @return Pointer to the new node.
 */
Node_t *create_cnode( char type, bool isFirst );

#endif
