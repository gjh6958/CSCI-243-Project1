// Takes in an input charater parameter and returns character class
// defined in given file classes.h
// Author - Grayson Hassell

#include "classification.h"

// char c: a character passed in by the scanner() function
// return int: integer value of character class matching char c
// All Character Class values can be found in classes.h
int classification(char c){
    char ch = c; // creates functions own initialized character
    const char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"; // defines alphabetical characters
    if(strchr(" \t", ch))
        return CC_WS; // Returns white-space character class
    if(strchr("\n", ch))
        return CC_NEWLINE; // returns newline cc
    if(strchr(alpha, ch))
        return CC_ALPHA; // returns alphabet cc
    if(strchr("0", ch))
        return CC_DIG_0; // returns digit 0 cc
    if(strchr("1234567", ch))
        return CC_DIG_1_7; // returns dig 1-7 cc
    if(strchr("89", ch))
        return CC_DIG_8_9; // returns dig 8-9 cc
    if(strchr("/", ch))
        return CC_CHAR_SLASH; // returns char slash cc
    if(strchr("*", ch))
        return CC_CHAR_STAR; // returns * cc
    if(strchr("+=%", ch))
        return CC_ARITH_OP; // returns arithmatic operater cc
    if(__isascii(ch))
        return CC_OTHER;  // returns other cc if ch is an ascii character
    if(ch == EOF)
        return CC_EOF; // returns eof cc once end of file is passed in
    if(!__isascii(ch))
        return CC_ERROR; // returns error cc if ch is not ascii

    return N_CC; // returns number of character classes if no other classification fits
}

