// See burst.h for more info
// Author: Hector Jair Hernandez Cortes
// File: burst.c
// Date: 05/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "burst.h"


// -----------------------------
// Private elements
// -----------------------------

/* Private functions */

/**
 * Generates a random number from 0 to n.
 * 
 * @param n Maximum number.
 * @return Random value.
 */
static int randomNumber(int n) {
    return rand() % n;;
}


// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */

Node_t *create_cnode( char type, bool isFirst ) {
    // Initializate
    Node_t *process = malloc(sizeof(Node_t));

    // Verify root node
    if ( isFirst ) 
        process->createdAt = randomNumber(19);
    else
        process->createdAt = 0;

    // Crate other type
    if ( type == 'c' )
        process->lifeTime = randomNumber(19);
    else if ( type == 'e' )
        process->lifeTime = randomNumber(24);

    process->type = type;
    process->next = NULL;
    return process;
}
