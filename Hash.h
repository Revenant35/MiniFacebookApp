
#ifndef PROGRAMMING_ASSIGNMENT_1_HASH_H
#define PROGRAMMING_ASSIGNMENT_1_HASH_H

#define MAX_LOAD_FACTOR (1)
#define GROWTH_FACTOR (2)
#define INITIAL_SIZE (1024)

typedef struct hash_table_struct{
    Node **table;
    unsigned long size;
    unsigned long n;
}*HashTable;

HashTable createHashTable(void);
void freeHashTable(HashTable);
Node* hashSearch(HashTable, const char*);
void hashInsert(HashTable, const char*);
unsigned long hash(const char *str);

#endif //PROGRAMMING_ASSIGNMENT_1_HASH_H
