
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "Utility.h"

//  Make all values of the provided string lowercase
char *strLower(char *str){
    if(!str)
        return NULL;

    unsigned int len = strlen(str);

    for(int i = 0; i < len; i++){
        str[i] = (signed char) tolower(str[i]);
    }

    return str;
}

//  Make the first character of the string uppercase
char *formatName(char *name){
    if(!name)
        return NULL;

    name[0] = (signed char) toupper(name[0]);

    return name;
}

//  Print all users in the hash table
