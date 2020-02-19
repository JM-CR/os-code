// Specific functions to create and handle a queue.
// Author: Hector Jair Hernandez Cortes
// File: burst.h
// Date: 05/02/20

// ------------------------------------------
// System specific headers
// ------------------------------------------
#include <stdbool.h>
#include <time.h>

// -----------------------------
// Public interface
// -----------------------------

// Types
typedef struct node {
    int createdAt;
    int lifeTime;  
    char type;
    Node_t *next;
} Node_t;

// Functions

/**
 * 
 */
Node_t *create_cnode(void);