#include <assert.h>
#include "Hash.h"

//  Hash Function by Dan Bernstein
unsigned long hash(char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % TABLE_SIZE;
}

//  Creates and returns a new node with name = "\0"
Node *createNode(char *name){
    Node *newNode = malloc(sizeof(Node));
    if(newNode) {
        newNode->next = NULL;
        newNode->friends = NULL;
        newNode->name = name;
        newNode->numberOfFriends = 0;
    }
    return newNode;
}

//  Create a new hash table
HashTable *newHashTable(unsigned long size){
    HashTable *newTable = malloc(sizeof(HashTable));

    if(!newTable){
        return NULL;
    }

    newTable->size = size;
    newTable->n = 0;
    newTable->table = malloc(size * sizeof(Node));

    if(!newTable->table){
        free(newTable);
        return NULL;
    }

    return newTable;
}

//  Frees all memory allocated to the hash table
void freeHashTable(HashTable *ht){
    Node *cursor = NULL, *next = NULL;
    for(int i = 0; i < ht->size; i++){
        cursor = ht->table[i];
        do {
            next = cursor->next;
            free(cursor);
            cursor = next;
        } while (cursor != NULL);
    }
    free(ht->table);
    free(ht);
}

// Resize the memory allocated to name to the minimum amount
//  Saves time and space
void resize(char *name){
    int len = strlen(name);
    name = realloc(name, (len+1) * sizeof(char));
}

bool isNullNode(HashTable *ht, unsigned long index){
    if(ht->table[index]->name == NULL)
        return true;
    return false;
}

//  NOTE: the node pointed to cannot equal null or program will segfault
bool userExists(HashTable *ht, char *name, unsigned long index){

    // if the hash index isnt NULL, there are two possibilities:
    //  A user with the same name already exists
    //  A user with a different name was hashed to the same index
    if(strcmp(ht->table[index]->name, name) == 0){
        return true;
    }

    return false;
}

//  Inserts a new user at the head position
bool handleCollision(HashTable *ht, char *name, unsigned long index){
    Node *new_Node = createNode(name);
    if(new_Node) {
        new_Node->next = ht->table[index];
        ht->table[index] = new_Node;
        return true;
    }
    return false;
}

bool insertFriend(HashTable *ht, Node *f1, Node *f2){
    f1->numberOfFriends++;
    f2->numberOfFriends++;
    f1->friends = realloc(f1->friends, f1->numberOfFriends * sizeof(Node*));
    f2->friends = realloc(f2->friends, f2->numberOfFriends *  sizeof(Node*));
    f1->friends[f1->numberOfFriends-1] = f2;
    f2->friends[f2->numberOfFriends-1] = f1;
    return  (f1->friends[f1->numberOfFriends-1] == f2) && (f2->friends[f2->numberOfFriends-1] == f1);
}

bool hasFriend(HashTable *ht, Node *target, Node *query){
    unsigned long num_of_friends = sizeof(target->friends)/sizeof(Node*);
    for(int i = 0; i < num_of_friends; i++){
        if(target->friends[i] == query)
            return true;
    }
    return false;
}