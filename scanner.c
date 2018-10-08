/*
 * implements Scanner function which parses tokens one at a time
 * and prints their output given if it is recognized by the
 * transition matrix or not
 */

//includes header file
#include "scanner.h"

// Preforms steps necessary to read and recognize one token
char* scanner(struct TransitionMatrix tmat){
    size_t size = 64; // tokens will never be longer than 63 characters, +1 for NUL terminator
    size_t tlen = 0; // transitions array length
    char c; // charater to get input with
    int transitions[size*4]; // transitions array to keep track of transition states, 4 times size because ints are 4*sizeof(char)
    size_t len = 0; // length of token
    int currState = tmat.start; // current state tracker, initialized to tmat.start for first state
    int nextState = 0; // keeps track of the state to go to next given character
    transitions[tlen++] = currState; // puts transitions[0] = tmat.start and increments tlen
    char* save = "s"; // keeps track of the action given by matrix cell
    int class; // stores c's character class returned by classification(c)
    char *token = malloc(sizeof(char)*size); // token defined with a size = max token size
    // main loop that parses tokens and saves transitions
    while(currState != tmat.accept){ // while token is not accepted
	if(currState == 99){ // if error token
            c = getchar();
            class = classification(c);
            if(class == CC_WS || class == CC_NEWLINE) // get characters until WS or NEWLINE encountered
                break;
            else
                continue;
        }

        c = getchar(); // get next character
        class = classification(c); // classify
        int x = class + 1; // xvalue of TM cell with accounted offset
        int y = currState; // yvalue of TM cell
        char* nextStateStr[sizeof(char)*5]; // defines next state char pointer
	// gets save or discard action from cell
        if(strchr(tmat.matrix[y][x], 'd'))
            save = "d";
        else
            save = "s";
	// Parse next state from cell
        if(strstr(tmat.matrix[y][x], "99"))
            nextState = 99;
        else{
            for(int i = 0; i < 2; i++){
                if(isdigit(tmat.matrix[y][x][i])){
                    nextStateStr[i] = &tmat.matrix[y][x][i];
                }
            }
            nextState = atoi(*nextStateStr); // convert to integer value
        }

        currState = nextState; // change current state value

        transitions[tlen++] = nextState; // put next transition into transition array

	// saves c to token buffer if action is c, breaks while loop if c == EOF
        if(*save == 's' && class != CC_EOF)
            token[len++] = c;
        if(class == CC_EOF)
            break;
    }

    transitions[tlen++] = currState; // adds current state to transitions array

    // prints transitions as they were recorded
    for(size_t i = 0; i < tlen-1; i++){
        printf("%d ", transitions[i]);
    }

    // returns rejected token if error state was encountered
    if(currState == 99){
	char* ntok = malloc(sizeof(char)*size + 20);
       	ntok[0] = ' ';
	char* rejected = "rejected\0";
	strcpy(ntok, rejected);
	free( token );
	return ntok;
    }
    // returns "recognized (token)" if token was accepted and last char wasn't EOF
    if(currState == tmat.accept && class != CC_EOF){
	char* ntok = malloc(sizeof(char)*size+40);
        ntok[0] = ' ';
	token[len] = '\0';
	sprintf(ntok, "recognized '%s'", token);
	free( token );
	return ntok;
    }
    // returns EOF token if token is the EOF class
    if(currState == tmat.accept && class == CC_EOF){
        char* ntok = malloc(sizeof(char)*size + 20);
	ntok[0] = ' ';
	char* eof = "EOF\0";
	strcpy(ntok, eof);
	free( token );
	return ntok;
    }

    return 0;
}

