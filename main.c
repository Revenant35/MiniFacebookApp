#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Hash.h"
#include "Utility.h"

#define MAX_INPUT_SIZE (130)
#define INITIAL_TABLE_SIZE (256)




//bool addFriend(HashTable *ht, char *target, char *friend){
//    int index_t = hash(target), index_f = hash(friend);
//    if(ht->table[index_t])
//}


//// Functions to Implement
//// Determines if two users are friends
//// O(m) time complexity where m is the max friends of either user
////  This is roughly O(1)
//bool isFriends(HashTable *ht, char *name1, char *name2){
//    unsigned long hash1 = hash(name1), hash2 = hash(name2);
//    if(!ht->table[hash1] || !ht->table[hash2])
//        return false;
//    Node *f1 = ht->table[hash1], *f2 = ht->table[hash2];
//    if(hasFriend(ht, f1, f2) && hasFriend(ht, f2, f1))
//        return true;
//    return false;
//}
//
//// Creates a 'link' between two users indicating that they are friends
//// O(1) time complexity
//bool addFriendshipLink(HashTable *ht, char *name1, char *name2){
//    unsigned long hash1 = hash(name1), hash2 = hash(name2);
//    if(ht->table[hash1] && ht->table[hash2]){
//        insertFriend(ht, ht->table[hash1], ht->table[hash2]);
//        return true;
//    }
//    if(!ht->table[hash1]) {
//        fprintf(stderr, "ERROR: USER %s DOES NOT EXIST\n", name1);
//    }
//    if(!ht->table[hash2]) {
//        fprintf(stderr, "ERROR: USER %s DOES NOT EXIST\n", name2);
//    }
//    return false;
//}
//
////  Inputs a new user with specified name
////  O(1) Time complexity
//bool inputUser(HashTable *ht, char *input){
//
//    // get the length of the string
//    int name_length = strlen(input)+1;
//
//    // allocate and populate new memory for our string
//    char *name = malloc(name_length * sizeof(char));
//    strncpy(name, input, name_length);
//
//    // get the index of our name after hashing it
//    unsigned long index = hash(name);
//
//    // if the string is null, we fill it with our newly allocated name
//    if(isNullNode(ht, index)){
//        ht->table[index]->name = name;
//        return true;
//    }
//
//    // if the string isn't null and the user exists, print error
//    if(userExists(ht, name, index)){
//        fprintf(stderr, "ERROR: USER %s ALREADY EXISTS\n", name);
//        free(name);
//        return false;
//    }
//
//    // handle the collision. returns whatever value is returned by handleCollision
//    return handleCollision(ht, name, index);
//}

void terminateProgram(HashTable *ht, char *buf){
    freeHashTable(ht);
    free(buf);
}

void run(){

    // allocate memory for a 2^7 byte name string
    char *buf = malloc(MAX_INPUT_SIZE * sizeof(char));
    HashTable *ht = createHashTable(INITIAL_TABLE_SIZE);
    const char delim[2] = " ";


    if(!ht || !buf){
        fprintf(stderr, "ERROR: UNABLE TO ALLOCATE SUFFICIENT MEMORY\n");
        return;
    }


    while(true){
        scanf("%[^\n]130s", buf);

        buf = strLower(buf);

        char *instruction = strtok(buf, delim);
        char *name1 = strtok(NULL, delim);
        char *name2 = strtok(NULL, delim);

        switch(*instruction){
            case 'q':
                printf(queryFriend(ht, name1, name2) ? "Yes\n" : "No\n");
                break;
            case 'l':
                break;
            case 'p':
                hashInsert(ht, name1);
                break;
            case 'f':
                addFriend(ht, name1, name2);
                break;
            case 'u':
                break;
            case 'x':
                terminateProgram(ht, buf);
                return;
        }
        fflush(stdin);
        PrintUsers(ht);
    }
}


int main() {
    run();
}
