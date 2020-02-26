// Author: Hector Jair Hernandez Cortes
// File: main.c
// Date: 22/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include "process.h"

#define TOTAL 5

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

/*
FIFO(process, TOTAL);
 FIFO{
     Node_t *node;
     int end, iterator;
     bool first = TRUE;
     do{
         node = process[iterator];
         if(node != NULL){//existing proc
            if(first){
                exectime += node->lifeTime;
                node->lifetime = 0;
                first = FALSE;
                erase(node);
            }
            if(node == NULL){//end of proc
                end++;
                erase(node);
            }
            else{// type 'e'
                do{
                    node->lifetime--;
                }while(node->lifeTime != 0);
            }
            do{//type 'c'
                
            }while(node->lifeTime != 0);
            node = node->next;
            
            if(iterator > TOTAL){
                iterator = 0;
            }
        }
        iterator++;
     }while(end!=TOTAL);
 */
    return 0;
}
