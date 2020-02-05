// See queue.h for more info
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

// Global variables
typedef struct Number {
  int element;
  struct Number *next;
} Number_t;

Number_t *root;

// Functions
Number_t *next( Number_t *item );
Number_t *create( int number );
void printQueue( void );
bool hasNext( Number_t *item );
void insert( Number_t *item );
void erase(void);