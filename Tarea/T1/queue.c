// See queue.h for more info
// Author: Hector Jair Hernandez Cortes
// Author: Josue Mosiah Contreras Rocha
// Author: Bruno Valerio Fernandez
// File: queue.c
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

static int **responseTime;   // TR
static int **waitTime;       // TE

static size_t TOTAL;     // Total of processes
static int DEATHS = 0;   // Finished processes

static unsigned int ioIndex = 0;      // Last free position in ioQueue
static unsigned int readyIndex = 0;   // Last free position in readyQueue
static unsigned int totalTime = 0;
static unsigned int rtCont = 0;

/* Private functions */

/**
 * Prints the current state of a burst.
 *
 * @param type Node's type.
 * @param id Position in the queue.
 */
static void printNode( char type, int id ) {
    switch (type) {
    case 'c':
        printf("P[%02d] LF: %2d\n", cpuQueue->id, cpuQueue->lifeTime);
        break;
    
    case 'e':
        printf("P[%02d] LF: %2d\n", ioQueue[id]->id, ioQueue[id]->lifeTime); 
        break;

    default:
        printf("P[%02d] LF: %2d\n", readyQueue[id]->id, readyQueue[id]->lifeTime); 
    }
}

/**
 * Checks if a process has arrived to the ready queue.
 *
 * @param process Process to check.
 * @return True if a new process has come; otherwise, false;
 */
static bool checkEntryTime( Node_t *process ) {
    if ( process->createdAt == totalTime ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Once a process has left the readyQueue the remainig processes are
 * moved forward one position.
 */
static void shiftReady( void ) {
    // Move processes
    for ( int i = 0; i < TOTAL - 1; ++i )  /* Shift */
        readyQueue[i] = readyQueue[i + 1];
    readyQueue[readyIndex--] = NULL;  /* Clean */
}

/**
 * Implements the functionality of the ready queue, it includes:
 *   1. Check if a new process has arrived.
 *   2. Move a process to the cpu queue once it is free.
 *   3. Print the current state of the queue.
 *
 * @param process Array of processes.
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

        // Fill responseTime array
        if(rtCont<TOTAL) {
            responseTime[rtCont][0] = cpuQueue->id;
            responseTime[rtCont][1] = totalTime-cpuQueue->createdAt;
            rtCont++;
        }
    }

    // Print queue
    printf("Ready Queue:\n");
    if ( readyQueue != NULL )
        for ( int c = readyIndex - 1; c >= 0; c-- )
            printNode(' ', c);
    printf("\n");   
}

/**
 * Once a process has left the ioQueue the remainig processes are
 * moved forward one position.
 *
 * @param from Position of the process in the ioQueue.
 */
static void shiftIO( int from ) {
    // Move processes
    ioIndex--;
    ioQueue[from] = NULL;  /* Clean */
    for ( int i = from; i < TOTAL; ++i )  /* Shift */
        ioQueue[i] = ioQueue[i + 1];
}

/**
 * Implements the functionality of the input/output queue, it includes:
 *   1. Check if a new process has arrived.
 *   2. Move a process to the ready queue once it is ENDED_P.
 *   3. Print the current state of the queue.
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
                readyQueue[readyIndex++] = ioQueue[c]->next; /* Move to ready */
                erase(&ioQueue[c]);   /* Clean */
                shiftIO(c);
            } 
        }
    }
    printf("\n");
}

/**
 * Implements the functionality of the cpu queue, it includes:
 *   1. Check if a new process has arrived.
 *   2. Move a process to the input/output queue once it has ENDED_P.
 *   3. Print the current state of the queue.
 */
static void cpuQ( void ) {
    printf("CPU Queue: \n");
    if ( cpuQueue != NULL ) {
        // Print queue
        printNode('c', 0);

        // Values for next run
        cpuQueue->lifeTime--;

        // Check life
        if( cpuQueue->lifeTime <= 0 ) {
            if ( cpuQueue->next != NULL ) {
                ioQueue[ioIndex++] = cpuQueue->next;   /* Move to IO */
            } else {
                DEATHS++;   /* Process has ended */
            }
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
    // Create queues & time arrays
    TOTAL = size;

    cpuQueue = NULL;
    readyQueue = calloc(TOTAL, sizeof(Node_t));
    ioQueue = calloc(TOTAL, sizeof(Node_t));

    responseTime = malloc(TOTAL * sizeof(int *));
    waitTime = malloc(TOTAL * sizeof(int *)); 

    // Fill queues & time arrays
    for ( int i = 0; i < TOTAL; ++i ) {
        readyQueue[i] = ioQueue[i] = NULL;
		responseTime[i] = (int *)malloc(2 * sizeof(int)); 
    }
}

void start( Node_t *process[] ) {
    // Print processes
    printf("Initial processes:\n\n");
    for ( int i = 0; i < TOTAL; ++i ) 
        printProcess(process[i]);
    printf("\n\n");

    while ( true ) {
        // Run queues
        printf("\n\nTime elapsed: %d\n\n", totalTime);
        readyQ(process);
        ioQ();
        cpuQ();

        // Values for the next run
        totalTime++;
        sleep(1);

        // Check missing processes
        if ( DEATHS == TOTAL )
            break;

        // Print responseTime array.
        for (int i=0; i<TOTAL; i++) { 
		    printf("\n"); 
		    for (int j=0; j<2; j++) 
			    printf("\t%d", responseTime[i][j]); 
	    } 
    }
}
