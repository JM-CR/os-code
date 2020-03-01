// This library simulates a FCFS/FIFO queue.
// Author: Josue Mosiah Contreras Rocha
// File: queue.h
// Date: 17/02/20

#ifndef QUEUE_H
#define QUEUE_H

// -----------------------------
// System headers
// -----------------------------
#include <stdbool.h>
#include "process.h"

// -----------------------------
// Public interface
// -----------------------------

/**
 * Initial set up to run the simulation.
 * This function must be called before start().
 *
 * @param size Number of processes.
 */
void initializeQueues( size_t size );

/**
 * Starts the simulation of a FCFS queue.
 *
 * @param process Processes that will be used to simulate the queues.
 */
void start( Node_t *process[] ); 

#endif
