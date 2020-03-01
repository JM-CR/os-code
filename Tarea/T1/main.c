// Author: Hector Jair Hernandez Cortes
// File: main.c
// Date: 22/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

#define TOTAL 5

int main(void) {
    // Create root nodes
    Node_t *process[TOTAL];
    for ( int i = 0; i < TOTAL; i++ )  
        process[i] = create_cnode('c', true, i+1);

    // Add remaining nodes
    for( int i = 0; i < TOTAL; i++ ) {
        for ( int j = 0; j < 1; j++ ) {
            insert(&process[i], create_cnode('e', false, i+1));
            insert(&process[i], create_cnode('c', false, i));
        } 
    }

    // Create queues
    initializeQueues(TOTAL);
    start(process);
    
    return 0;
}
