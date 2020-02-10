/**
 * A pthread program illustrating how to create multiple
 * threads and some of the pthread API.
 * This program implements the quicksort algorithm where
 * the operation is run by multiples threads.
 *
 * Most Unix/Linux/OS X users
 * gcc quicksort.c thrd-posix.c -lpthread -lrt
 *
 * @author Josue Mosiah Contreras Rocha
 * @file quicksort.c
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
static int *arr;
static sem_t mutex;

// Prototypes
void *runner( void *params );
void swap( int *a, int *b );
int partition( int lower, int upper );
void quickSort( int lower, int upper );

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

	printf("Unsorted array:\n");
	for ( int i = 0; i < arraySize; ++i )
		printf("%d%s", arr[i], i == (arraySize - 1) ? "\n\n" : " ");


	// Initialize threads
	const unsigned int THREADS = 1;
	// const unsigned int THREADS = getThreads();   // This approach is faulty
	
	pthread_t *tid = (pthread_t *) malloc(sizeof(pthread_t) * THREADS);
	pthread_attr_t attr;

	// Sort's range for each thread
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

	// Create threads
	sem_init(&mutex, 0, 1);   /* Create semaphore */
	pthread_attr_init(&attr);   /* Default attributes */

	for( int i = 0; i < THREADS; ++i ) {
		pthread_create(&tid[i], &attr, runner, &range[i * 2]);
		pthread_join(tid[i], NULL);   /* Wait for threads */
    }

	// Results
	sem_destroy(&mutex);   /* Destroy semaphore */
	printf("Sorted array:\n");
	for ( int i = 0; i < arraySize; ++i )
		printf("%d%c", arr[i], i == (arraySize - 1) ? '\n' : ' ');
}

/**
 * The thread will begin control in this function.
 *
 * @param params Range for each thread.
 */
void *runner(void *params) {
	// Initial set up for the thread
	int *param = (int *)params;
	int lower = param[0], upper = param[1];
	
  	// Operations
	quickSort(lower, upper);
	pthread_exit(0);
}

/**
 * Swap two elements at memory level.
 * 
 * @param a First element.
 * @param b Second element.
 */
void swap( int *a, int *b ) { 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

/**
 * Sorts a file-scope array with the quicksort algorithm.
 *
 * @param lower Starting index.
 * @param upper Ending index.
 * @return Position of the first element in the next partition.
 */
int partition( int lower, int upper ) {
	// Initialize
	int pivot = arr[upper];  
	int i = lower - 1;  // Index of smaller element

	// Operations
    for ( int j = lower; j <= upper - 1; ++j ) {
        if ( arr[j] < pivot ) {
            // Increment index of smaller element
			i++; 

			// Critical section
			sem_wait(&mutex);
			swap(&arr[i], &arr[j]);
			sem_post(&mutex);
        }
    }
    
	// Critical section
	sem_wait(&mutex);
	swap(&arr[i + 1], &arr[upper]);
	sem_post(&mutex);
    
	return (i + 1);
}
  
/**
 * Implements the QuickSort algorithm.
 * 
 * @param lower Starting index.
 * @param upper Ending index.
 */
void quickSort( int lower, int upper ) { 
    if ( lower < upper ) { 
		// Partitioning index
        int pi = partition(lower, upper);
  
        // Sort elements before and after partition 
        quickSort(lower, pi - 1); 
        quickSort(pi + 1, upper); 
    } 
} 
