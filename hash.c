
#include <stdlib.h>
#include <string.h>

#include "hash.h"

static void internalGrowTable(HashTable ht);
static void internalHashInsert(HashTable ht, const char *key, void *data);
static void internalFreeHashTable(HashTable ht);

//  Hash function by Dan Bernstein
static unsigned long hash(const char *str){
    unsigned long hash = 5381;
    char c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

static Node *internalCreateNode(const char *key){
    Node *newNode = malloc(sizeof(Node));

    if(!newNode)
        return NULL;

    newNode->next = newNode->data = NULL;
    newNode->key = key;

    return newNode;
}

static HashTable internalCreateHashTable(size_t dataSize, unsigned long size){
    HashTable ht;
    int i;
    ht = malloc(sizeof(*ht));

    if(!ht)
        return NULL;

    ht->len = size;
    ht->dataSize = dataSize;
    ht->n = 0;
    ht->table = malloc(ht->len * (sizeof(Node) + ht->dataSize));

    if(!ht->table){
        free(ht);
        return NULL;
    }

    for(i = 0; i < ht->len; i++){
        ht->table[i] = NULL;
    }

    return ht;
}

static void internalGrowTable(HashTable ht){
    HashTable ht2;
    struct hash_table_struct swap;
    int i;
    Node *cursor = NULL;

    ht2 = internalCreateHashTable(ht->len * GROWTH_FACTOR, ht->dataSize);

    if(!ht2)
        return;

    for(i = 0; i < ht->len; i++){
        for(cursor = ht->table[i]; cursor; cursor = cursor->next){
            internalHashInsert(ht2, cursor->key, cursor->data);
        }
    }

    swap = *ht;
    *ht = *ht2;
    *ht2 = swap;

    internalFreeHashTable(ht2);
}

static void internalHashInsert(HashTable ht, const char *key, void *data){

    Node *newNode = internalCreateNode(key);

    if(!newNode)
        return;

    unsigned long h = hash(key) % ht->len;

    newNode->data = data;

    newNode->next = ht->table[h];
    ht->table[h] = newNode;

    ht->n++;

    if(ht->n >= ht->len * MAX_LOAD_FACTOR)
        internalGrowTable(ht);
}

static void internalHashDelete(HashTable ht, const char *key){
    unsigned long h;
    Node *curr, *prev;

    h = hash(key) % ht->len;
    curr = ht->table[h];

    if(curr && !strcmp(curr->key, key)){
        ht->table[h] = curr->next;
        free(curr);
        curr = NULL;
    }

    while(curr && strcmp(curr->key, key) != 0){
        prev = curr;
        curr = curr->next;
    }

    if(curr){
        prev->next = curr->next;
        free(curr);
    }

    ht->n--;
}

static Node *internalHashSearch(HashTable ht, const char *key){
    unsigned long h;
    Node *curr;

    h = hash(key) % ht->len;
    curr = ht->table[h];

    while(curr && strcmp(curr->key, key) != 0)
        curr = curr->next;

    return curr;
}

static void internalFreeHashTable(HashTable ht){
    int i;
    Node *cursor, *next;
    for(i = 0; i < ht->len; i++){
        for(cursor = ht->table[i]; cursor; cursor = next){
            next = cursor->next;
            free(cursor);
            cursor = NULL;
        }
    }
    free(ht->table);
    free(ht);
}

HashTable createTable(size_t dataSize, unsigned long size){
    return internalCreateHashTable(dataSize, size);
}

void hashInsert(HashTable ht, const char *key, void *data){
    if(internalHashSearch(ht, key))
        return;

    internalHashInsert(ht, key, data);
}

void hashDelete(HashTable ht, const char *key){
    internalHashDelete(ht, key);
}

Node *hashSearch(HashTable ht, const char *key){
    return internalHashSearch(ht, key);
}

void freeHashTable(HashTable ht){
    internalFreeHashTable(ht);
}

