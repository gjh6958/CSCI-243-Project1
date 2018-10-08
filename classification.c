// Takes in an input charater parameter and returns character class

#include "classification.h"


int classification(char c){
    char ch = c;
    const char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
    if(strchr(" \t", ch))
        return CC_WS;
    if(strchr("\n", ch))
        return CC_NEWLINE;
    if(strchr(alpha, ch))
        return CC_ALPHA;
    if(strchr("0", ch))
        return CC_DIG_0;
    if(strchr("1234567", ch))
        return CC_DIG_1_7;
    if(strchr("89", ch))
        return CC_DIG_8_9;
    if(strchr("/", ch))
        return CC_CHAR_SLASH;
    if(strchr("*", ch))
        return CC_CHAR_STAR;
    if(strchr("+=%", ch))
        return CC_ARITH_OP;
    if(__isascii(ch))
        return CC_OTHER;
    if(ch == EOF)
        return CC_EOF;
    if(!__isascii(ch))
        return CC_ERROR;

    return N_CC;
}

