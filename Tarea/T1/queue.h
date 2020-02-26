// Template to create C libraries.
// Author: Josue Mosiah Contreras Rocha
// File: library.h
// Date: 17/02/20

#ifndef LIBRARY_H
#define LIBRARY_H

// -----------------------------
// System headers
// -----------------------------
#include <stdbool.h>
#include "process.h"

// -----------------------------
// Public interface
// -----------------------------

/* Constants */

/* Types declarations */

/* Global variables */

/* Function prototypes */

/**
 * Function's documentation.
 */
void initializeQueues( size_t size );

/**
 * Function's documentation.
 */
void start( Node_t *process[] ); 

#endif