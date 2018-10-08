// matrixCreation function that takes in a file pointer
// to a tm file and parses the data contained inside
// to create and return a TransitionMatrix structure
// Author - Grayson Hassell

// matrixCreation header file with needed definitions and includes
#include "matrixCreation.h"
#include "classes.h" // used for N_CC int

struct TransitionMatrix matrixCreation( FILE* fp){

    char * ptr, buf[256]; // character pointer and buffer

    // ints to represent values in tm to be created
    int states;
    int start;
    int accept;

    //reads tm files first three lines to find the states, start, and accept numbers
    for(int i = 0; i < 3; i++){
        if( (ptr = fgets(buf,256, fp)) != NULL) // checks that there is a word to pull and that it fits in buffer
            ptr = strtok(ptr, " "); // pulls word from the files first three lines
        ptr = strtok(NULL, "\n"); // replaces found word with associated value
        // converts char numbers to their integer values and initializes respective variables
        int a = atoi(ptr);
        if(i == 0)
            states = a;
        if(i == 1)
            start = a;
        if(i == 2)
            accept = a;
    }

    //initializes instance of TransitionMatrix structure with all NULL values in matrix cells
    tm tmat = {states, start, accept, {{0}}};

    //puts state numbers in correct row within TM
    int iterableStart = start;
    for(int i = 0; i < states; i++){
        char * ptr = malloc(20);
        sprintf(ptr, "%d", iterableStart);
        tmat.matrix[i][0] = ptr;
        iterableStart++;
    }

    //inputs correct actions into TM matrix cells
    for(int i = 0; i < states; i++){
        if( (ptr = fgets(buf, 256, fp)) != NULL)
            ptr = strtok(ptr, " "); // gets the state we are finding actions for
        else
            break;
        int state;
        sscanf(ptr, "%d", &state); // assigns state value
        char ch = '\n'; // character to check line endings with
        while((ptr = strtok(NULL, " ")) != NULL ){ // splits line into tokens by ' '
            int cclass, toState;
            char action;
            sscanf( ptr, "%d/%d%c", &cclass, &toState, &action);  // parses tokens into character class, next state, and action values
            char * mal = malloc(20);
            sprintf(mal, "%d%c", toState, action); // assigns values
            // gets row and column values for corresponding action and assigns value
            int y = state;
            int x = cclass+1;
            tmat.matrix[y][x] = mal;
            // checks to see that we haven't reached the end of the line and breaks if we have
            if(strchr(ptr, ch) != NULL)
                break;
        }
    }

    //Fills in "99d" for all values left null
    for(int y = 0; y < states; y++){
        for(int x = 0; x < N_CC+1; x++){
            if(tmat.matrix[y][x] == NULL)
                tmat.matrix[y][x] = "99d";
        }
    }

    //Prints found TM in correct formatting
    printf("Scanning using the following matrix:\n");
    printf("     0    1    2    3    4    5    6    7    8    9   10   11\n");
    for(int y = 0; y < states; y++){
        printf("%2s", tmat.matrix[y][0]);
        for(int x = 1; x < N_CC+1; x++){
            printf("  %3s", tmat.matrix[y][x]);
        }
        printf("\n");
    }

    // closes file pointer
    fclose( fp );

    //returns created TM struct
    return tmat;
}
