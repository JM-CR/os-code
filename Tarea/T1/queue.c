// See library.h for more info
// Author: hector Jair Hernandez Cortes
// File: library.c
// Date: 17/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"


// -----------------------------
// Private elements
// -----------------------------


/* Private macros and constants */

/* Private types */

/* Private global variables */

static Node_t *cpuQueue;
static Node_t *readyQueue;
static Node_t *ioQueue;
static size_t TOTAL;

static unsigned int totalTime = 0;


/* Private functions */

/**
 * 
 */
static bool cpuQ( void ) {
    return false;
}

/**
 * 
 */
static void ioQ( void ) {

}

static bool checkEntryTime( Node_t *process ) {
    if ( process->createdAt == totalTime ) {
        return true;
    } else {
        return false;
    }
}

/**
 * 
 */
static void readyQ( Node_t *process[] ) {
    for ( int i = 0, j = 0; i < TOTAL ; ++i ) {
        if ( checkEntryTime(process[i]) ) {
            for ( int j = 0; j < TOTAL; ++j ) {

            }

            // while ( readyQueue[j] == NULL ) {
            //     ++j;
            // }
        }
    }
    totalTime++;

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
}


// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */

void initializeQueues( size_t size ) {
    // Create queues
    readyQueue = calloc(size, sizeof(Node_t));
    ioQueue = calloc(size, sizeof(Node_t));
    cpuQueue = NULL;
    TOTAL = size;
}

void start( Node_t *process[] ) {
    for( int i = 0; i < TOTAL; i++ )
        printQueue(process[i]);

    while (true) {
        readyQ(process);
    }
}