// Author: Josue Mosiah Contreras Rocha
// File: main.c
// Date: 05/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

// Prototypes
void waitForEnter(void);
bool evaluate( int option );

// Main program
int main(void) {

    int option;
    do {
        printf("\nChoose your option: \n");
        printf(
            " 1. Insert.\n"
            " 2. Erase.\n"
            " 3. Elements.\n"
            " 4. Quit.\n\n"
            " -> "
        );
        scanf(" %d", &option);
    } while( evaluate(option) );

    return 0;
}


// Implementation

/**
 * Pauses the program until the user presses [Enter].
 */
void waitForEnter(void) {
    printf("\n\n[Enter] to continue...");
    while( getchar() != '\n' );
    getchar();
}

/**
 *
 */
bool evaluate( int option ) {
    switch (option) {
    case 1: {
        int value;
        printf("\nNumber to insert: ");
        scanf(" %d", &value);
        insert(create(value));
        waitForEnter();
        break;
    }

    case 2:
        erase();
        waitForEnter();
        break;

    case 3:
        printQueue();
        waitForEnter();
        break;
    
    default: 
        return false;
    }

    return true;
}