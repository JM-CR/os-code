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
static Node_t **readyQueue;
static Node_t **ioQueue;
static size_t TOTAL;

static unsigned int totalTime = 0;


/* Private functions */

/**
 * 
 */
static void cpuQ( void ) {
    
}

/**
 * 
 */
static void ioQ( void ) {

}

/**
 *
 */
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
static void shiftReadyQ( void ) {
    for ( int i = 0; i < TOTAL - 1; ++i )
        readyQueue[i] = readyQueue[i + 1];
    readyQueue[TOTAL - 1] = NULL;
}

/**
 * 
 */
static void readyQ( Node_t *process[] ) {
    // Check arrive time
    static unsigned int position = -1;
    for ( int i = 0; i < TOTAL; ++i )
        if ( checkEntryTime(process[i]) )
            readyQueue[++position] = process[i];
    // for( int i = 0; i < TOTAL; i++ ) {
    //      printProcess(process[i]);
    // }
    if(cpuQueue == NULL && position!= -1) {
        cpuQueue = readyQueue[0];
        cpuQ();
    }
    
    // Increase timer
    totalTime++;
    // cpuQueue->lifeTime--;
    // if(cpuQueue->lifeTime==0){
    //     printf("cola IO\n");
    // }

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
    while (true) {
        readyQ(process);
        for( int i = 0; i < TOTAL; i++ ) {
         printProcess(process[i]);
        }
        sleep(1);
    }
}