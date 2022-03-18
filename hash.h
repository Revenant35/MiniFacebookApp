
#ifndef PROGRAMMING_ASSIGNMENT_1_HASH_H
#define PROGRAMMING_ASSIGNMENT_1_HASH_H

#define MAX_LOAD_FACTOR (.5)
#define GROWTH_FACTOR (2)

#include <stddef.h>

typedef struct node_struct Node;
typedef struct hash_table_struct *HashTable;

struct node_struct{
    Node *next;
    const char *key;
    void *data;
};

struct hash_table_struct{
    Node **table;
    size_t dataSize;
    unsigned long len;
    unsigned long n;
};

HashTable createTable(size_t dataSize, unsigned long size);
void hashInsert(HashTable ht, const char *key, void *data);
void hashDelete(HashTable ht, const char *key);
Node *hashSearch(HashTable ht, const char *key);
void freeHashTable(HashTable ht);

#endif //PROGRAMMING_ASSIGNMENT_1_HASH_H
