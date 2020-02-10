// See compressor.h for more info
// Author: Josue Mosiah Contreras Rocha
// File: thrd-posix.c
// Date: 05/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdlib.h>
#include "thrd-posix.h"


// -----------------------------
// Public elements
// -----------------------------

// Public functions

/**
 * Get the number of cores the system has.
 *
 * @return Number of cores.
 */
unsigned int getCores( void ) {
    unsigned int eax = 11, ebx = 0, ecx = 1, edx = 0;
    asm volatile("cpuid"
        : "=a"(eax),
          "=b"(ebx),
          "=c"(ecx),
          "=d"(edx)
        : "0"(eax),"2"(ecx)
        :);

    return eax;
}

/**
 * Get the number of threads the system has.
 *
 * @return Number of threads.
 */
unsigned int getThreads( void ) {
    unsigned int eax = 11, ebx = 0, ecx = 1, edx = 0;
    asm volatile("cpuid"
        : "=a"(eax),
          "=b"(ebx),
          "=c"(ecx),
          "=d"(edx)
        : "0"(eax),"2"(ecx)
        :);

    return ebx;
}

/**
 * Get the current thread in use.
 *
 * @return Actual in use.
 */
unsigned int getCurrentThread( void ) {
    unsigned int eax = 11, ebx = 0, ecx = 1, edx = 0;
    asm volatile("cpuid"
        : "=a"(eax),
          "=b"(ebx),
          "=c"(ecx),
          "=d"(edx)
        : "0"(eax),"2"(ecx)
        :);

    return edx;
}
