/* 
 * Author - Grayson Hassell
 * The Mechanics of Programming Project 1
 * Lexical Analysis
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "classes.h"
#include "matrix.h"
#include "matrixCreation.h"
#include "classification.h"
#include "scanner.h"

//Main function that runs all program functionality
//Prompts creation of transition matrix and prints
//Tokens one at a time by calling the scanner function
int main(int argc, char * argv[]){
    
    //checks to see if there is a tm file present
    if(argc != 2){
        printf("usage: ./tokenize tmfile\n");
        return 0;
    }

    //Creates file pointer and checks to see if it
    //can be opened
    FILE *fp;

    if( (fp = fopen( argv[1], "r" )) == NULL ){
	perror( argv[1] );
	exit( EXIT_FAILURE );
    }
    
    //creates the transition matrix
    tm tmat = matrixCreation(fp);
    
    //Scans for tokens one at a time and frees their heap
    //memory allocations
    char* token;
    while(!strstr((token = (char*)realloc(scanner(tmat), sizeof(char)*64 + 80)), "EOF")){
	printf("%s\n", token);
	free( token );
    }

    //Prints EOF token and frees the heap memory
    //allocation
    printf("%s\n", token);
    free(token);

    //Free the memory stored in the heap by the 
    //Transition Matrix
    for(int y = 0; y < tmat.states; y++){
	for(int x = 0; x < N_CC; x++){
            if(!strstr(tmat.matrix[y][x], "99d"))
	        free( tmat.matrix[y][x] );
	}
    }

    return 0;
}
