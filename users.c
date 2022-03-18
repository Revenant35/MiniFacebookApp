
#include "users.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_FRIEND_SIZE (64)

static void internalUserInsert(HashTable ht, const char *username){

    if(hashSearch(ht, username))
        return;

    hashInsert(ht, username, createFriendTable());
}

static void internalUserDelete(HashTable ht, const char *username){
    HashTable user;
    Node *curr, *prev, *temp;
    int i;

    temp = hashSearch(ht, username);

    if(!temp)
        return;

    user = temp->data;

    for(i = 0; i < user->len; i++){
        curr = user->table[i];
        while(curr){
            prev = curr;
            curr = curr->next;
            temp = hashSearch(ht, prev->key);
            if(temp){
                hashDelete(temp->data, username);
            }
        }
    }

    freeHashTable(user);
    hashDelete(ht, username);
}

HashTable createFriendTable(){
    return createTable(sizeof(struct hash_table_struct), DEFAULT_FRIEND_SIZE);
}

void userInsert(HashTable ht, const char *username){
    if(!username)
        return;

    char *name = malloc(sizeof(char) * (strlen(username) + 1));
    strcpy(name, username);

    internalUserInsert(ht, name);
}

void userDelete(HashTable ht, const char *username){
    if(!username)
        return;

    internalUserDelete(ht, username);
}

void printUsers(HashTable ht){
    Node *curr;
    int i;

    for(i = 0; i < ht->len; i++){
        curr = ht->table[i];
        if(curr) {
            while (curr) {
                printf("%s ", curr->key);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

void freeUserTable(HashTable ht){
    Node *curr, *prev;
    int i;

    for(i = 0; i < ht->len; i++){
        curr = ht->table[i];
        while(curr){
            prev = curr;
            curr = curr->next;
            freeHashTable(prev->data);
        }
    }

    freeHashTable(ht);
}

