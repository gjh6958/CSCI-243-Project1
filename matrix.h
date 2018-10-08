/*
 * Author - Grayson Hassell
 * Header file for matrix and matrixTransition definitions
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATRIXX 15
#define MATRIXY 80

typedef struct TransitionMatrix{
    int states;
    int start;
    int accept;
    char * matrix[MATRIXY][MATRIXX];

} tm;

#endif
