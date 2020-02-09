/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API.
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * Most Unix/Linux/OS X users
 * gcc thrd.c -lpthread
 *
 * Solaris users must enter
 * gcc thrd.c -lpthreads
 *
 * Figure 4.9
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// ------------------------------------------
// Shared variables
// ------------------------------------------
int sum, *arr;

// Prototypes
void *runner(void *param);

/**
 * Main thread.
 */
int main(int argc, char *argv[])
{
    // Validate console arguments
    if ( argc != 2 ) {
        fprintf(stderr, "usage: a.out <integer value>\n");
        exit(EXIT_FAILURE);
    }

    if ( atoi(argv[1]) < 0 ) {
        fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
        exit(EXIT_FAILURE);
    }

    // Populate array with random numbers
    int size = atoi(argv[1]);
    int par[] = { 0, size };
    arr = malloc(sizeof(int) * size);

    srand(0);
    for( int i=0; i < size; i++ )
        arr[i] = rand() % 50;

    // Initialize thread
    pthread_t tid;        // Thread identifier
    pthread_attr_t attr;  // Attributes

    // Start timer
    clock_t start = clock();

    // Create thread
    pthread_attr_init(&attr);   // Default attributes
    pthread_create(&tid, &attr, runner, par);
    pthread_join(tid, NULL);    // Wait thread to exit

    // Stop timer
    clock_t end = clock();

    // Results
    double seconds = (double)(end-start) / CLOCKS_PER_SEC;
    printf("Time = %lf", seconds);
    printf("\nSum = %d\n", sum);
}

/**
 * The thread will begin control in this function.
 *
 * @param params Thread's attributes.
 */
void *runner( void *params ) {
    // Initial set up for the thread
    int *param = (int *)params;
    int i, lower = param[0], upper = param[1];
    sum = 0;

    // Operations
    if ( upper > 0 )
        for ( i = lower; i <= upper; i++ )
            sum += arr[i];
    pthread_exit(0);
}
