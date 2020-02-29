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


/* Private functions */
/**
 *
 */
static void shiftReadyQ( void ) {
    //MARK: Have a mistake cause give a segmentation fault
    for ( int i = 0; i < TOTAL - 1; ++i )
        readyQueue[i] = readyQueue[i + 1];
    readyQueue[TOTAL - 1] = NULL;
    position--;
}
/**
 * 
 */
static void ioQ( void) {
    printf("I/O Queue:\n");
    if(readyQueue!=NULL){
        printf("process with their lifetime in I/o");
    }
    printf("\n\n\n");
}

/**
 * 
 */
static void cpuQ( void) {
    printf("CPU Queue: \n");
    if(cpuQueue!=NULL){
        printf("[0] LF: %d\n", cpuQueue->lifeTime);
        cpuQueue->lifeTime--;
        if(cpuQueue->lifeTime <=0){
            //Erase node
            //When shitfKey works cpuposition will be 0
            cpuQueue = readyQueue[cpuPosition];
            shiftReadyQ(); 
            cpuPosition++;
        }
    }
    printf("\n");
    ioQ();
    
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
static void readyQ( Node_t *process[] ) {
    // Check arrive time
    for ( int i = 0; i < TOTAL; ++i ){
        if ( checkEntryTime(process[i]) ){
            readyQueue[position] = process[i];
            if(cpuQueue==NULL){
                cpuQueue=process[i];
                shiftReadyQ(); 
            }
            position++;
        } 
    }
    printf("Ready Queue:\n");
    if(readyQueue!=NULL){
        for (int c=position-1; c>=0;c--){
            printf("[%d] LF: %d\n", c,readyQueue[c]->lifeTime); 
        }
    }
    printf("\n");   
    
    // Increase timer
    totalTime++;
    //printing CPU Queue
    cpuQ();
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
        
        printf("Time elapsed: %d\n\n", totalTime);
        readyQ(process);
        // for(int i=0;i<TOTAL;i++){
        //     printProcess(process[i]);
        //     printf("\n");
        // }
        sleep(1);
    }
}