// Specific functions to create and handle a queue.
// Author: Josue Mosiah Contreras Rocha
// File: queue.h
// Date: 17/02/20

#ifndef QUEUE_H
#define QUEUE_H

// -----------------------------
// System headers
// -----------------------------
#include <stdbool.h>
#include "burst.h"


// -----------------------------
// Public interface
// -----------------------------

/* Function prototypes */

/**
 * Gets the next node.
 *
 * @param item Element to traverse.
 * @return Pointer to the next element.
 */
Node_t *next( Node_t *item );

/**
 * Inserts a new node in the queue.
 *
 * @param ppRoot Pointer to the first node.
 * @param item Node to insert.
 */
void insert( Node_t **ppRoot, Node_t *item );

/**
 * Prints the whole queue.
 *
 * @param pRoot Pointer to the first node.
 */
void printQueue( Node_t *pRoot );

/**
 * Checks if there is a node after the item.
 *
 * @param item Node to check.
 * @return True if there is the next element exists.
 */
bool hasNext( Node_t *item );

/**
 * Deletes the first node.
 * 
 * @param ppRoot Pointer to the first element
 */
void erase( Node_t **ppRoot );

#endif
