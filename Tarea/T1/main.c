// Author: Hector Jair Hernandez Cortes
// File: main.c
// Date: 22/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

#define TOTAL 20

int main(void) {
    // Create root nodes
    Node_t *process[TOTAL];
    for ( int i = 0; i < TOTAL; i++ )  
        process[i] = create_cnode('c', true);

    // Add remaining nodes
    for( int i = 0; i < TOTAL; i++ ) {
        for ( int j = 0; j < 5; j++ ) {
            insert(&process[i], create_cnode('e', false));
            insert(&process[i], create_cnode('c', false));
        } 
    }

    for( int i = 0; i < TOTAL; i++ )
        printQueue(process[i]);

    return 0;
}
