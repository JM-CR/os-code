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
#include <unistd.h>
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
static unsigned int position = 0;
static unsigned int cpuPosition = 0;
static unsigned int ioPosition = 0;

/* Private functions */

/**
 *
 */
static void printNode( char type, int id ) {
    switch (type) {
    case 'c':
        printf("[%d] LF: %d\n", id, cpuQueue->lifeTime);
        break;
    
    case 'e':
        printf("[%d] LF: %d. T: %c\n", id, ioQueue[id]->lifeTime, ioQueue[id]->type); 
        break;

    default:
        printf("[%d] LF: %d.\tT: %c\n", id, readyQueue[id]->lifeTime, readyQueue[id]->type); 
    }
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
    // Move processes
    for ( int i = 0; i < TOTAL - 1; ++i )
        readyQueue[i] = readyQueue[i + 1];
    readyQueue[TOTAL - 1] = NULL;

    // Free last position
    position--;
}

/**
 * 
 */
static void readyQ( Node_t *process[] ) {
    // Check arrive time
    for ( int i = 0; i < TOTAL; ++i ){
        if ( checkEntryTime(process[i]) ){
            readyQueue[position] = process[i];
            if (cpuQueue == NULL){
                cpuQueue = process[i];
                shiftReadyQ(); 
            }
            position++;
        } 
    }

    // Print queue
    printf("Ready Queue:\n");
    if ( readyQueue != NULL )
        for ( int c = position - 1; c >= 0; c-- )
            printNode(' ', c);
    printf("\n");   
}

/**
 * 
 */
static void ioQ( void ) {
    printf("I/O Queue:\n");
    if ( ioQueue != NULL ) {
        // Print queue
        for ( int c = ioPosition - 1; c >= 0; c-- )
            printNode('e', c);

        // Values for next run
        for ( int c = ioPosition - 1; c >= 0 ; c-- ) {
            // Decrease
            ioQueue[c]->lifeTime--;

            // Check and clean
            if ( ioQueue[c]->lifeTime <= 0 ) {
                erase(&ioQueue[c]);
            } 
        }
    }
    printf("\n\n\n");
}

/**
 * 
 */
static void cpuQ( void) {
    printf("CPU Queue: \n");
    if ( cpuQueue != NULL ) {
        printNode('c', 0);

        // Values for next run
        cpuQueue->lifeTime--;

        // Check and clean
        if( cpuQueue->lifeTime <=0 ) {
            erase(&cpuQueue);
            ioQueue[ioPosition] = cpuQueue;
            ioPosition++;
            cpuQueue = readyQueue[cpuPosition];
            shiftReadyQ();
            cpuPosition++;
        }
    }
    printf("\n");
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
        // Run queues
        printf("Time elapsed: %d\n\n", totalTime);
        readyQ(process);
        cpuQ();
        ioQ();

        // Values next run
        totalTime++;
        sleep(1);
    }
}