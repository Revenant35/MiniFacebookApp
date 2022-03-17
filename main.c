#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "users.h"

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
    UserTable ut = createUserTable();

    //  Delimiter used to parse the string from stdin
    const char delim[2] = " ";

    //  Check for malloc failure
    if(!ut || !buf){
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
                printf(queryFriendship(ut, name1, name2) ? "Yes\n" : "No\n");
                break;
            case 'l':
                printFriends(ut, name1);
                break;
            case 'p':
                insertUser(ut, name1);
                break;
            case 'f':
                createFriendship(ut, name1, name2);
                break;
            case 'u':
                deleteFriendship(ut, name1, name2);
                break;
            case 'a':
                printUsers(ut);
                break;
            case 'd':
                deleteUser(ut, name1);
                break;
            case 'x':
                freeUserTable(ut);
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
