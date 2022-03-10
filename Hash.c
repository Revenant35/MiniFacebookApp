#include <assert.h>
#include "Hash.h"

//  grow the table by the GROWTH_FACTOR
static void grow(HashTable *ht){
    HashTable *ht2, swap;

    ht2 = createHashTable(ht->size * GROWTH_FACTOR);
    for(int i = 0; i < ht->size; i++){
        hashInsert(ht2, ht->table[i]->name);
    }

    swap = *ht;
    *ht = *ht2;
    *ht2 = swap;

    freeHashTable(ht2);
}

//  Hash function by Dan Bernstein
static unsigned long hash(const char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

//  Creates and returns a new node
static Node *createNode(const char *name){
    Node *newNode = malloc(sizeof(Node));
    if(newNode) {
        newNode->next = NULL;
        newNode->friends = NULL;
        newNode->name = malloc(sizeof(char) * strlen(name)+1);
        strcpy(newNode->name, name);
        newNode->numberOfFriends = 0;
    }
    return newNode;
}

//  Create a new hash table
HashTable *createHashTable(const unsigned long size){
    HashTable *newTable = malloc(sizeof(HashTable));

    if(!newTable){
        return NULL;
    }

    newTable->size = size;
    newTable->n = 0;
    newTable->table = malloc(newTable->size * sizeof(Node*));

    if(!newTable->table){
        free(newTable);
        return NULL;
    }

    for(int i = 0; i < newTable->size; i++){
        newTable->table[i] = NULL;
    }

    return newTable;
}

//  Frees all memory allocated to the hash table
void freeHashTable(HashTable *ht){
    Node *cursor = NULL, *next = NULL;
    for(int i = 0; i < ht->size; i++){
        cursor = ht->table[i];
        while (cursor != NULL){
            next = cursor->next;
            free(cursor);
            cursor = next;
        }
    }
    free(ht->table);
    free(ht);
}

//  Searches for a specific key within the table
Node *hashSearch(HashTable *ht, const char *key){
    for (Node *cursor = ht->table[hash(key) % ht->size]; cursor != NULL; cursor = cursor->next) {
        if (!strcmp(cursor->name, key)) {
            return cursor;
        }
    }
    return NULL;
}

//  Inserts a provided name into the hash table
void hashInsert(HashTable *ht, const char *name){
    Node *newNode;
    unsigned long h;

    assert(name);

    if(hashSearch(ht, name)){
        return;
    }

    newNode = createNode(name);

    assert(newNode);

    h = hash(name) % ht->size;

    newNode->next = ht->table[h];
    ht->table[h] = newNode;

    ht->n++;

    if(ht->n >= ht->size * MAX_LOAD_FACTOR)
        grow(ht);
}

void addFriend(HashTable *ht, const char *name1, const char *name2){
    Node *node1 = hashSearch(ht, name1), *node2 = hashSearch(ht, name2);
    if(!node1 || !node2)
        return;

    node1->numberOfFriends++;
    node2->numberOfFriends++;

    node1->friends = realloc(node1->friends, node1->numberOfFriends * sizeof(Node*));
    node2->friends = realloc(node2->friends, node2->numberOfFriends *  sizeof(Node*));

    node1->friends[node1->numberOfFriends-1] = node2;
    node2->friends[node2->numberOfFriends-1] = node1;
}

bool queryFriend(HashTable *ht, const char *name1, const char *name2){
    Node *node1 = hashSearch(ht, name1), *node2 = hashSearch(ht, name2);
    if(!node1 || !node2)
        return false;
    for(int i = 0; i < node1->numberOfFriends; i++){
        if(node1->friends[i] == node2){
            for(int j = 0; j < node2->numberOfFriends; j++){
                if(node2->friends[j] == node1)
                    return true;
            }
            break;
        }
    }
    return false;
}
