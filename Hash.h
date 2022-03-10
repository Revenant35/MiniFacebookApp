#ifndef PROGRAMMING_ASSIGNMENT_1_HASH_H
#define PROGRAMMING_ASSIGNMENT_1_HASH_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LOAD_FACTOR (1)
#define GROWTH_FACTOR (2)

typedef struct node_struct Node;
struct node_struct {
    Node *next;
    char *name;
    Node **friends;
    int numberOfFriends;
};

typedef struct hash_table_struct{
    Node **table;
    unsigned long size;
    unsigned long n;
}HashTable;


HashTable* createHashTable(unsigned long);
void freeHashTable(HashTable*);
Node* hashSearch(HashTable*, const char*);
void hashInsert(HashTable*, const char*);
void addFriend(HashTable*, const char*, const char*);
bool queryFriend(HashTable*, const char*, const char*);

#endif //PROGRAMMING_ASSIGNMENT_1_HASH_H
