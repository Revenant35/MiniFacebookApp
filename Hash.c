
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Node.h"
#include "Hash.h"

//  Hash function by Dan Bernstein
unsigned long hash(const char *str){
    unsigned long hash = 5381;
    char c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

//  internal function to create a hash table
static HashTable internalCreateHashTable(const unsigned long size){
    HashTable ht;
    int i;
    ht = malloc(sizeof(*ht));

    if(!ht){
        return NULL;
    }

    ht->size = size;
    ht->n = 0;
    ht->table = malloc(ht->size * sizeof(Node));

    if(!ht->table){
        free(ht);
        return NULL;
    }

    for(i = 0; i < ht->size; i++){
        ht->table[i] = NULL;
    }

    return ht;
}

//  internal insert function
static void internalHashInsert(HashTable ht, Node *node){
    Node *cursor;
    unsigned long h;

    if(!node || !ht || !node->name){
        fprintf(stderr, "ERROR: INVALID INPUT TO FUNCTION internalHashInsert\n");
        return;
    }

    h = hash(node->name) % ht->size;

    for(cursor = ht->table[h]; cursor; cursor = cursor->next){
        if(strcmp(node->name, cursor->name) == 0){
            fprintf(stderr, "ERROR: USER %s ALREADY EXISTS\n", node->name);
            return;
        }
    }

    node->next = ht->table[h];
    ht->table[h] = node;

    ht->n++;
}

//  grow the table by the GROWTH_FACTOR
static void grow(HashTable ht){
    HashTable ht2;
    struct hash_table_struct swap;
    int i;
    Node *cursor = NULL;

    ht2 = internalCreateHashTable(ht->size * GROWTH_FACTOR);
    if(!ht2){
        fprintf(stderr, "ERROR: RAN OUT OF MEMORY!\n");
        return;
    }
    for(i = 0; i < ht->size; i++){
        for(cursor = ht->table[i]; cursor; cursor = cursor->next) {
            internalHashInsert(ht2, cursor);
        }
    }

    swap = *ht;
    *ht = *ht2;
    *ht2 = swap;

    freeHashTable(ht2);
}

//  Allows the user to create a new hashtable with size INITIAL_SIZE
HashTable createHashTable(void){
    return internalCreateHashTable(INITIAL_SIZE);
}

//  Frees all memory allocated to the hash table
void freeHashTable(HashTable ht){
    int i;
    Node *cursor = NULL, *next = NULL;
    for(i = 0; i < ht->size; i++){
        for(cursor = ht->table[i]; cursor!= 0; cursor = next){
            next = cursor->next;
            unsafeDeleteFriendsList(cursor);
            freeNode(cursor);
        }
    }
    free(ht->table);
    free(ht);
}

//  Searches for a specific key within the table
Node *hashSearch(HashTable ht, const char *key){
    for (Node *cursor = ht->table[hash(key) % ht->size]; cursor; cursor = cursor->next) {
        if (!strcmp(cursor->name, key)) {
            return cursor;
        }
    }
    return NULL;
}

//  Inserts a provided name into the hash table
void hashInsert(HashTable ht, const char *name){

    if(hashSearch(ht, name)) {
        fprintf(stderr, "ERROR: USER ALREADY EXISTS\n");
        return;
    }

    internalHashInsert(ht, createNode(name));

    if(ht->n >= ht->size * MAX_LOAD_FACTOR) {
        grow(ht);
    }
}
