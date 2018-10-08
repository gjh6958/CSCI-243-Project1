#include "matrix.h"
#include "classes.h"

struct TransitionMatrix matrixCreation( FILE* fp){

    char * ptr, buf[256];
    int states;
    int start;
    int accept;

    //reads tm files first three lines to find the states, start, and accept numbers
    for(int i = 0; i < 3; i++){
        if( (ptr = fgets(buf,256, fp)) != NULL)
            ptr = strtok(ptr, " ");
        ptr = strtok(NULL, "\n");
        int a = atoi(ptr);
        if(i == 0)
            states = a;
        if(i == 1)
            start = a;
        if(i == 2)
            accept = a;
    }

    //initializes instance of TransitionMatrix structure
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
            ptr = strtok(ptr, " ");
        else
            break;
        int state;
        sscanf(ptr, "%d", &state);
        char ch = '\n';
        while((ptr = strtok(NULL, " ")) != NULL ){
            int cclass, toState;
            char action;
            sscanf( ptr, "%d/%d%c", &cclass, &toState, &action);
            char * mal = malloc(20);
            sprintf(mal, "%d%c", toState, action);
            int y = state;
            int x = cclass+1; 
            tmat.matrix[y][x] = mal;
            if(strchr(ptr, ch) != NULL)
                break;
        }
    }

    //Fills in "99d" for all values left null
    for(int y = 0; y < MATRIXY; y++){
        if(y == states)
            break;

        for(int x = 0; x < MATRIXX; x++){
            if(tmat.matrix[y][x] == NULL)
                tmat.matrix[y][x] = "99d";
        }
    }

    //Prints found TM in correct formatting
    printf("Scanning using the following matrix:\n");
    printf("     0    1    2    3    4    5    6    7    8    9   10   11\n");
    for(int y = 0; y < states; y++){
        if(y == states)
            break;
        printf("%2s", tmat.matrix[y][0]);
        for(int x = 1; x < MATRIXX; x++){
            printf("  %3s", tmat.matrix[y][x]);
        }
        printf("\n");
    }

    fclose( fp );

    //returns created TM struct
    return tmat;
}
