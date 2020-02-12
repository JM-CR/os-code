// Specific functions to create and handle a queue.
// Author: Josue Mosiah Contreras Rocha
// File: queue.h
// Date: 05/02/20

// ------------------------------------------
// System specific headers
// ------------------------------------------
#include <stdbool.h>
#include <time.h>

// -----------------------------
// Public interface
// -----------------------------

// Types
struct IO;

typedef struct CPU {
    date_t createdAt;
    int lifeTime;  
    IO_t *next;
} CPU_t;

typedef struct IO {
    date_t createdAt;
    int lifeTime;  
    CPU_t *next;
} IO_t;

// Functions
CPU_t *create_cnode(void);
IO_t *create_inode(void);

