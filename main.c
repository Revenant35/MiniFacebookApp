#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "Hash.h"

#define MAX_INPUT_SIZE MAX_NAME_SIZE+2

// gets index of first whitespace character, returns -1 if none present
char* getNextName(char *str) {
    for (int i = 0; i <= strlen(str); i++) {
        if (str[i] == ' ') {
            str[i] = '\0';
            return str + i + 1;
        }
    }
    return NULL;
}

//  Print all users in the hash table
void PrintUsers(HashTable *ht){
    Node *cursor = NULL;
    for(int i = 0; i < TABLE_SIZE; i++){
        if(ht->table[i]->name != NULL){
            printf("User %d: %s\n", i, ht->table[i]->name);
            cursor = ht->table[i]->next;
            while(cursor != NULL){
                printf("User %d: %s\n", i, cursor->name);
                cursor = cursor->next;
            }
        }

    }
}

// Make all values of the provided string lowercase
//  we dont want duplicate users Lisa and lisa... thats confusing
void strLower(char *string){
    for(int i = 0; i < strlen(string); i++){
        if(isalpha(string[i]))
            string[i] = tolower(string[i]);
    }
}



//bool addFriend(HashTable *ht, char *target, char *friend){
//    int index_t = hash(target), index_f = hash(friend);
//    if(ht->table[index_t])
//}


// Functions to Implement
// Determines if two users are friends
// O(m) time complexity where m is the max friends of either user
//  This is roughly O(1)
bool isFriends(HashTable *ht, char *name1, char *name2){
    unsigned long hash1 = hash(name1), hash2 = hash(name2);
    if(!ht->table[hash1] || !ht->table[hash2])
        return false;
    Node *f1 = ht->table[hash1], *f2 = ht->table[hash2];
    if(hasFriend(ht, f1, f2) && hasFriend(ht, f2, f1))
        return true;
    return false;
}

// Creates a 'link' between two users indicating that they are friends
// O(1) time complexity
bool addFriendshipLink(HashTable *ht, char *name1, char *name2){
    unsigned long hash1 = hash(name1), hash2 = hash(name2);
    if(ht->table[hash1] && ht->table[hash2]){
        insertFriend(ht, ht->table[hash1], ht->table[hash2]);
        return true;
    }
    if(!ht->table[hash1]) {
        fprintf(stderr, "ERROR: USER %s DOES NOT EXIST\n", name1);
    }
    if(!ht->table[hash2]) {
        fprintf(stderr, "ERROR: USER %s DOES NOT EXIST\n", name2);
    }
    return false;
}

//  Inputs a new user with specified name
//  O(1) Time complexity
bool inputUser(HashTable *ht, char *input){

    // get the length of the string
    int name_length = strlen(input)+1;

    // allocate and populate new memory for our string
    char *name = malloc(name_length * sizeof(char));
    strncpy(name, input, name_length);

    // get the index of our name after hashing it
    unsigned long index = hash(name);

    // if the string is null, we fill it with our newly allocated name
    if(isNullNode(ht, index)){
        ht->table[index]->name = name;
        return true;
    }

    // if the string isn't null and the user exists, print error
    if(userExists(ht, name, index)){
        fprintf(stderr, "ERROR: USER %s ALREADY EXISTS\n", name);
        free(name);
        return false;
    }

    // handle the collision. returns whatever value is returned by handleCollision
    return handleCollision(ht, name, index);
}

void run(){
    // allocate memory for a 2^7 byte name string
    char *buf = malloc((MAX_NAME_SIZE + 2) * sizeof(char));
    HashTable *ht = newHashTable();
    buf[0] = '\0';
    while(true){
        scanf("%[^\n]130s", buf);
        strLower(buf);
        char c = buf[0];
        char *name1 = (buf+2);
        char *name2 = getNextName(name1);
        switch(c){
            case 'q':
                if(isFriends(ht, name1, name2)){
                    printf("Yes\n");
                } else {
                    printf("No\n");
                }
                break;
            case 'l':
                break;
            case 'p':
                if(!inputUser(ht, name1)){
                    fprintf(stderr, "ERROR: COULD NOT ADD USER %s!\n", name1);
                }
                break;
            case 'f':
                addFriendshipLink(ht, name1, name2);
                break;
            case 'u':
                break;
            case 'x':
                free(buf);
                freeHashTable(ht);
                return;
        }
        fflush(stdin);
//        PrintUsers(ht);
    }
}


int main() {
    run();
}
