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
static int random(int n) {
    int number;
    srand(0);
    number = rand()%n;
    return number;
}

// -----------------------------
// Public elements
// -----------------------------

// Public functions

Node_t *create_cnode(char type, bool isFirst) {
    struct node process;
    if (isFirst){
        process.createdAt = random(19);
    }
    else{
        process.createdAt = 0;
    }
    //var Type only could be C for CPU and E for Entries.
    if (strcmp(type, "C") == 0){
        process.lifeTime = random(9);
    }
    else if (strcmp(type, "E") == 0){
        process.lifeTime = random(24);
    }
    process.type = type;
    process.next = NULL;
    return &process;
}