/*
 * Author - Grayson Hassell
 * Header file for matrix and matrixTransition definitions
 */

#ifndef MATRIX_H
#define MATRIX_H

// includes the C libraries needed for 
// matrixCreation functionality
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATRIXX 15 // x-axis length, there are only 12 character classes as given by N_CC
#define MATRIXY 80 // y-axis length, no more than 75 states possible in the matrix

// defines the structure TransitionMatrix which represents the values in the tm file
typedef struct TransitionMatrix{
    int states; // number of states given in tm file
    int start; // number of start state given in tm file
    int accept; // number of accept state given in tm file
    char * matrix[MATRIXY][MATRIXX]; // 2-D matrix to represent the transition matrix cell values

} tm;

#endif
