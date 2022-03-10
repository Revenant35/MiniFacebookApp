#include "Utility.h"

//  Resize the memory allocated to name to the minimum amount
void resize(char **name){
    unsigned int len = strlen(*name);
    *name = (char*) realloc(*name, (len+1) * sizeof(char));
}

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

//  Print all users in the hash table
void PrintUsers(HashTable *ht){
    Node *cursor = NULL;
    for(int i = 0; i < ht->size; i++){
        cursor = ht->table[i];
        while(cursor){
            printf("User %d: %s\n", i, cursor->name);
            cursor = cursor->next;
        }
    }
}