/*
 * implements Scanner function which parses tokens one at a time
 * and prints their output given if it is recognized by the 
 * transition matrix or not
 */

#include "scanner.h"

// Preforms steps necessary to read and recognize one token
char* scanner(struct TransitionMatrix tmat){
    size_t size = 64;
    size_t tlen = 0;
    char c;
    int transitions[size+2];
    size_t len = 0;
    int currState = tmat.start;
    int nextState = 0;
    transitions[tlen++] = currState;
    int x;
    int y;
    char* save = "s";
    int class;
    char *token = malloc(sizeof(char)*size);
    char* eof = "EOF\0";
    char* rejected = "rejected\0";
    while(currState != tmat.accept){
	if(currState == 99){
            c = getchar();
            class = classification(c);
            if(class == CC_WS || class == CC_NEWLINE)
                break;
            else
                continue;
        }

        c = getchar();
        class = classification(c);
        x = class + 1;
        y = currState-tmat.start;
        char* nextStateStr[sizeof(char)*5];
        if(strchr(tmat.matrix[y][x], 'd'))
            save = "d";
        else
            save = "s";
        if(strstr(tmat.matrix[y][x], "99"))
            nextState = 99;
        else{
            for(int i = 0; i < 2; i++){
                if(isdigit(tmat.matrix[y][x][i])){
                    nextStateStr[i] = &tmat.matrix[y][x][i];
                }
            }
            nextState = atoi(*nextStateStr);
        }
        currState = nextState;

        transitions[tlen++] = nextState;

        if(*save == 's' && class != CC_EOF)
            token[len++] = c;
        if(class == CC_EOF)
            break;
    }

    transitions[tlen++] = currState;

    for(size_t i = 0; i < tlen-1; i++){
        printf("%d ", transitions[i]);
    }

    if(currState == 99){
	char* ntok = malloc(sizeof(char)*size + 20);
       	ntok[0] = ' ';
	strcpy(ntok, rejected);
	free( token );
	return ntok;
    }
    if(currState == tmat.accept && class != CC_EOF){
	char* ntok = malloc(sizeof(char)*size+40);
        ntok[0] = ' ';
	token[len] = '\0';	
	sprintf(ntok, "recognized '%s'", token);
	free( token );
	return ntok;
    }
    if(currState == tmat.accept && class == CC_EOF){
        char* ntok = malloc(sizeof(char)*size + 20);
	ntok[0] = ' ';
	strcpy(ntok, eof);
	free( token );
	return ntok;
    }

    return 0;
}

