/**
 * A pthread program illustrating how to create multiple 
 * threads and some of the pthread API.
 * This program implements the summation function where
 * the summation operation is run in multiple threads.
 *
 * Most Unix/Linux/OS X users
 * gcc multi-thrd.c thrd-posix.c -lpthread -lrt
 *
 * @author Josue Mosiah Contreras Rocha
 * @file multi-thrd.c
 * @date 09/02/2020
 */

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "thrd-posix.h"

// ------------------------------------------
// Shared variables
// ------------------------------------------
int sum = 0;
int *arr;
sem_t mutex;

// Prototypes
void *runner( void *params );

/**
 * Main thread.
 */
int main(int argc, char *argv[]) {
	// Validate console arguments
	if ( argc != 2 ) {
		fprintf(stderr, "usage: a.out <integer value>\n");
        exit(EXIT_FAILURE);
	}

	if ( atoi(argv[1]) < 0 ) {
		fprintf(stderr, "Argument %d must be non-negative\n", atoi(argv[1]));
        exit(EXIT_FAILURE);
	}


	// Fill array with random numbers
	int arraySize = atoi(argv[1]);	
	arr = malloc(sizeof(int) * arraySize);

	srand(0);   /* Seed */
	for( int i = 0; i < arraySize; ++i )
		arr[i] = rand() % 50;

	// Initialize threads
	const unsigned int THREADS = getThreads();
	
	pthread_t *tid = (pthread_t *) malloc(sizeof(pthread_t) * THREADS);
	pthread_attr_t attr;

	// Summmation range for each thread
	int rangeSize = arraySize / THREADS;
	int range[THREADS * 2];

	int first = 0, second = rangeSize - 1;
	for( int i = 0; i < THREADS; ++i ) {
		// Fill
		range[i * 2] = first;
		range[(i * 2) + 1] = i == (THREADS - 1) ? arraySize - 1 : second;

		// Update
		first += rangeSize; 
		second += rangeSize;
	}


	// Start timer
	sem_init(&mutex, 0, 1);   /* Create semaphore */
	clock_t start = clock();

	// Create threads
	pthread_attr_init(&attr);   /* Default attributes */

	for( int i = 0; i < THREADS; ++i ) {
		pthread_create(&tid[i], &attr, runner, &range[i * 2]);
		pthread_join(tid[i], NULL);   /* Wait for threads */
    }

	// Stop timer
    clock_t end = clock();
	sem_destroy(&mutex);   /* Destroy semaphore */

	// Results
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Time = %lf", seconds);
	printf("\nSum = %d\n", sum);
}

/**
 * The thread will begin control in this function.
 *
 * @param params Range for each thread.
 */
void *runner(void *params) {
	// Initial set up for the thread
	int *param = (int *)params;
	int i, lower = param[0], upper = param[1];
	
  	// Operations
	if ( upper > 0 )
		for ( i = lower; i <= upper; i++ ) {
    	    sem_wait(&mutex);
			sum += arr[i];
			sem_post(&mutex);
		}
	pthread_exit(0);
}
