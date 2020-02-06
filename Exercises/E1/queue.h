// Specific functions to create and handle a queue.
// Author: Josue Mosiah Contreras Rocha
// File: queue.h
// Date: 05/02/20

// ------------------------------------------
// System specific headers
// ------------------------------------------
#include <stdbool.h>


// -----------------------------
// Public interface
// -----------------------------

// Types
typedef struct Number {
  int element;
  struct Number *next;
} Number_t;

// Functions
Number_t *next( Number_t *item );
Number_t *create( int number );
void insert( Number_t **ppRoot, Number_t *item );
void printQueue( Number_t *pRoot );
bool hasNext( Number_t *item );
void erase( Number_t **ppRoot );