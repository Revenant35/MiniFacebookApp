
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "friends.h"

#define MAX_LOAD_FACTOR (1)
#define GROWTH_FACTOR (2)
#define INITIAL_SIZE (4)

static void internalInsert(FriendTable ht, FriendNode *friendNode){
    unsigned long h;

    h = hash(friendNode->friend->name) % ht->size;

    friendNode->next = ht->table[h];
    ht->table[h] = friendNode;

    ht->n++;
}

static void internalDelete(FriendTable ht, Node *friend){
    unsigned long h;
    FriendNode *curr, *prev;

    h = hash(friend->name) % ht->size;
    curr = ht->table[h];

    if(curr && curr->friend == friend){
        ht->table[h] = curr->next;
        free(curr);
        curr = NULL;
    }

    while(curr && curr->friend != friend){
        prev = curr;
        curr = curr->next;
    }

    if(curr){
        prev->next = curr->next;
        free(curr);
    }
}

static bool internalSearch(FriendTable ht, Node *friend){
    unsigned long h;
    FriendNode *curr;

    h = hash(friend->name) % ht->size;
    curr = ht->table[h];

    while(curr && curr->friend != friend){
        curr = curr->next;
    }

    return ((!curr) ? false : true);
}

static FriendTable internalCreateTable(unsigned long size){
    FriendTable ht;
    int i;
    ht = malloc(sizeof(*ht));

    if(!ht)
        return NULL;

    ht->size = size;
    ht->n = 0;
    ht->table = malloc(ht->size * sizeof(FriendNode));

    if(!ht->table){
        free(ht);
        return NULL;
    }

    for(i = 0; i < ht->size; i++){
        ht->table[i] = NULL;
    }

    return ht;
}

static void internalGrowTable(FriendTable ht){
    FriendTable ht2;
    struct friend_table_struct swap;
    int i;
    FriendNode *cursor = NULL;

    ht2 = internalCreateTable(ht->size * GROWTH_FACTOR);

    if(!ht2)
        return;

    for(i = 0; i < ht->size; i++){
        for(cursor = ht->table[i]; cursor; cursor = cursor->next) {
            internalInsert(ht2, cursor);
        }
    }

    swap = *ht;
    *ht = *ht2;
    *ht2 = swap;

//    freeFriendTable(ht2);
}

static FriendNode *internalCreateNode(Node *node){
    FriendNode *newFriendNode = malloc(sizeof(FriendNode));

    if(!newFriendNode)
        return NULL;

    newFriendNode->next = NULL;
    newFriendNode->friend = node;

    return newFriendNode;
}



FriendTable extCreateFriendTable(){
    return internalCreateTable(INITIAL_SIZE);
}

void extInsertFriend(Node *self, Node *friend){
    if(!self || !self->friends || !friend)
        return;

    internalInsert(self->friends, internalCreateNode(friend));

    if(self->friends->n >= self->friends->size * MAX_LOAD_FACTOR)
        internalGrowTable(self->friends);
}

void extDeleteFriend(Node *self, Node *friend){
    if(!self || !self->friends || !friend)
        return;

    internalDelete(self->friends, friend);
}

bool extSearchFriend(Node *self, Node *friend){
    if(!self || !self->friends || !friend)
        return false;

    return internalSearch(self->friends, friend);
}

void extPrintFriends(Node *self){
    FriendNode *curr;
    int i;

    for(i = 0; i < self->friends->size; i++){
        curr = self->friends->table[i];
        if(curr) {
            while (curr) {
                printf("%s ", curr->friend->name);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

void extUnsafeDeleteFriendsList(Node *self){
    FriendNode *curr, *prev;
    int i;

    if(!self || !self->friends)
        return;

    for(i = 0; i < self->friends->size; i++){
        curr = self->friends->table[i];
        while(curr){
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }
}

void extSafeDeleteFriendsList(Node *self){
    FriendNode *curr, *prev;
    int i;

    if(!self || !self->friends)
        return;

    for(i = 0; i < self->friends->size; i++){
        curr = self->friends->table[i];
        while(curr){
            prev = curr;
            curr = curr->next;
            internalDelete(prev->friend->friends, self);
            free(prev);
        }
    }
}
