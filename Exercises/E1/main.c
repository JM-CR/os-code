// Author: Josue Mosiah Contreras Rocha
// File: main.c
// Date: 05/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

// Main prototypes
void waitForEnter(void);
bool evaluate( int option );

// Private variables
static Number_t *root = NULL;

int main(void) {

    // Initialize
    int option;

    // User's logic
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


// Prototypes' implementation

/**
 * Pauses the program until the user presses [Enter].
 */
void waitForEnter(void) {
    printf("\n\n[Enter] to continue...");
    while( getchar() != '\n' );
    getchar();
}

/**
 * Executes a command based on the option from the menu.
 *
 * @param option Chosen option.
 * @return True if the option was valid.
 */
bool evaluate( int option ) {
    switch (option) {
    case 1: {
        int value;
        printf("\nNumber to insert: ");
        scanf("%d", &value);
        insert(&root, create(value));
        waitForEnter();
        break;
    }

    case 2:
        erase(&root);
        waitForEnter();
        break;

    case 3:
        printQueue(root);
        waitForEnter();
        break;
    
    default: 
        return false;
    }

    return true;
}
