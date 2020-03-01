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

/* Private global variables */

static Node_t *cpuQueue;
static Node_t **readyQueue;
static Node_t **ioQueue;
static size_t TOTAL;

static unsigned int ioIndex = 0;
static unsigned int readyIndex = 0;
static unsigned int totalTime = 0;

/* Private functions */

/**
 *
 */
static void printNode( char type, int id ) {
    switch (type) {
    case 'c':
        printf("[%d] LF: %2d\n", id, cpuQueue->lifeTime);
        break;
    
    case 'e':
        printf("[%d] LF: %2d\tT: %c\n", id, ioQueue[id]->lifeTime, ioQueue[id]->type); 
        break;

    default:
        printf("[%d] LF: %2d\tT: %c\n", id, readyQueue[id]->lifeTime, readyQueue[id]->type); 
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
static void shiftReady( void ) {
    // Move processes
    for ( int i = 0; i < TOTAL - 1; ++i )
        readyQueue[i] = readyQueue[i + 1];
    readyQueue[readyIndex--] = NULL;
}

/**
 * 
 */
static void readyQ( Node_t *process[] ) {
    // Check arrive time
    for ( int i = 0; i < TOTAL; ++i )
        if ( checkEntryTime(process[i]) )
            readyQueue[readyIndex++] = process[i];

    // Check CPU
    if ( cpuQueue == NULL && readyIndex > 0 ) {
        cpuQueue = readyQueue[0];
        shiftReady(); 
    }

    // Print queue
    printf("Ready Queue:\n");
    if ( readyQueue != NULL )
        for ( int c = readyIndex - 1; c >= 0; c-- )
            printNode(' ', c);
    printf("\n");   
}

/**
 *
 */
static void shiftIO( int from ) {
    // Move processes
    ioIndex--;
    ioQueue[from] = NULL;
    for ( int i = from; i < TOTAL; ++i )
        ioQueue[i] = ioQueue[i + 1];
}

/**
 * 
 */
static void ioQ( void ) {
    printf("I/O Queue:\n");
    if ( ioQueue != NULL ) {
        // Print queue
        for ( int c = ioIndex - 1; c >= 0; c-- )
            printNode('e', c);

        // Values for next run
        for ( int c = 0; c < ioIndex ; c++ ) {
            // Decrease time
            ioQueue[c]->lifeTime--;

            // Check life
            if ( ioQueue[c]->lifeTime <= 0 ) {
                readyQueue[readyIndex++] = ioQueue[c]->next; /* Move */
                erase(&ioQueue[c]);   /* Clean */
                shiftIO(c);
            } 
        }
    }
    printf("\n");
}

/**
 * 
 */
static void cpuQ( void) {
    printf("CPU Queue: \n");
    if ( cpuQueue != NULL ) {
        // Print queue
        printNode('c', 0);

        // Values for next run
        cpuQueue->lifeTime--;

        // Check IO
        if( cpuQueue->lifeTime <= 0 ) {
            ioQueue[ioIndex++] = cpuQueue->next;  /* Move */
            erase(&cpuQueue);  /* Clean */
            cpuQueue = NULL;
        }
    }
    printf("\n\n\n");
}


// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */

void initializeQueues( size_t size ) {
    // Create queues
    TOTAL = size;
    cpuQueue = NULL;
    readyQueue = calloc(size, sizeof(Node_t));
    ioQueue = calloc(size, sizeof(Node_t));

    // Fill arrays
    for ( int i = 0; i < size; ++i )
        readyQueue[i] = ioQueue[i] = NULL;
}

void start( Node_t *process[] ) {
    // Print processes
    printf("Initial processes:\n\n");
    for ( int i = 0; i < TOTAL; ++i ) 
        printProcess(process[i]);
    printf("\n\n");

    while (true) {
        // Run queues
        printf("Time elapsed: %d\n\n", totalTime);
        readyQ(process);
        ioQ();
        cpuQ();

        // Values next run
        totalTime++;
        sleep(1);
    }
}
