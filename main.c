#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "hash.h"
#include "users.h"

#define INITIAL_SIZE (1024)
#define MAX_INPUT_SIZE (130)

//  Formats a given name
char *formatName(char *name){

    if(!name)
        return NULL;

    unsigned int len = strlen(name);

    name[0] = (signed char) toupper(name[0]);

    for(int i = 1; i < len; i++){
        (name[i]) = (signed char) tolower(name[i]);
    }

    return name;
}

//  Driver code
void run(){

    //  Allocate memory for a 2^7 byte name string
    char *instruction, *name1, *name2, *buf = malloc(MAX_INPUT_SIZE * sizeof(char));

    //  Create a hashtable to store users in
    HashTable ht = createTable(sizeof(struct hash_table_struct), INITIAL_SIZE);

    //  Delimiter used to parse the string from stdin
    const char delim[2] = " ";

    //  Check for malloc failure
    if(!ht || !buf){
        fprintf(stderr, "ERROR: UNABLE TO ALLOCATE SUFFICIENT MEMORY\n");
        return;
    }

    //  The run loop
    while(true){

        //  Get user-input
        scanf("%[^\n]130s", buf);

        instruction = strtok(buf, delim);
        name1 = strtok(NULL, delim);
        name2 = strtok(NULL, delim);

        *instruction = (signed char) tolower(*instruction);
        formatName(name1);
        formatName(name2);

        //  Carry out said input
        switch(*instruction){
            case 'q':
                printf(searchFriend(ht, name1, name2) ? "Yes\n" : "No\n");
                break;
            case 'l':
                printFriends(ht, name1);
                break;
            case 'p':
                userInsert(ht, name1);
                break;
            case 'f':
                insertFriend(ht, name1, name2);
                break;
            case 'u':
                deleteFriend(ht, name1, name2);
                break;
            case 'a':
                printUsers(ht);
                break;
            case 'd':
                userDelete(ht, name1);
                break;
            case 'x':
                freeUserTable(ht);
                free(buf);
                return;
        }
        //  Flush stdin to help prevent user error
        fflush(stdin);
    }
}

int main() {
    run();
}
