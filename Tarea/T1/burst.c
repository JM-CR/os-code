// See queue.h for more info
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

// Private functions

/**
 * 
 */
int randomNumber(int n) {
    int number = rand()%n;
    return number;
}

// -----------------------------
// Public elements
// -----------------------------

// Public functions

Node_t *create_cnode(char type, bool isFirst) {
    Node_t *process = malloc(sizeof(Node_t));
    if (isFirst){
        process->createdAt = randomNumber(19);
    }
    else{
        process->createdAt = 0;
    }
    //var Type only could be C for CPU and E for Entries.
    if (type == 'c'){
        process->lifeTime = randomNumber(19);
    }
    else if (type == 'e'){
        process->lifeTime = randomNumber(24);
    }
    process->type = type;
    process->next = NULL;
    return process;
}
