
#include "hash.h"

//  Hash function by Dan Bernstein
unsigned long hash(const char *str){
    unsigned long hash = 5381;
    char c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

