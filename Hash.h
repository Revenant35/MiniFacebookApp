#ifndef PROGRAMMING_ASSIGNMENT_1_HASH_H
#define PROGRAMMING_ASSIGNMENT_1_HASH_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define TABLE_SIZE (4)
#define MAX_NAME_SIZE (128)

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


Node *createNode(char *name);
HashTable *newHashTable();
void freeHashTable(HashTable *ht);
bool hashInsert(HashTable *ht, char *name);
bool isNullNode(HashTable *ht, unsigned long index);
bool userExists(HashTable *ht, char *name, unsigned long index);
bool handleCollision(HashTable *ht, char *name, unsigned long index);
void resize(char *name);
unsigned long hash(char *str);
bool insertFriend(HashTable *ht, Node *f1, Node *f2);
bool hasFriend(HashTable *ht, Node *target, Node *query);

#endif //PROGRAMMING_ASSIGNMENT_1_HASH_H
