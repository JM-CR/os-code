// Author: Hector Jair Hernandez Cortes
// File: burst.c
// Date: 05/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "burst.h"

Node_t *create_cnode(char type, bool isFirst);
int randomNumber(int n);
void insert( Node_t **ppRoot, Node_t *item );
void printQueue( Node_t *pRoot);

int main (void){
    //var
    int numberProcess=20;
    //Incializo la semilla
    srand(0);
    //Creation of the root nodes.
    Node_t *process[numberProcess];
    for (int i=0;i<numberProcess;i++){    
        process[i] = create_cnode('c', true);
    }
    for(int i=0;i<numberProcess;i++){
        for (int j=0;j<5;j++){
            insert(&process[i], create_cnode('e', false));
            insert(&process[i], create_cnode('c', false));
        } 
    }
    for(int i=0;i<numberProcess;i++){
        printQueue(process[i]);
    }

    return 0;
    



   

}
