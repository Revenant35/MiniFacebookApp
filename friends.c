
#include "friends.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

FriendList createList(){
    FriendList list = malloc(sizeof(FriendList*));
    list->head = NULL;
    list->num_of_friends = 0;
    return list;
}

static FriendNode *createFriendNode(const char *name){
    FriendNode *newNode = malloc(sizeof(FriendNode));
    if(newNode) {
        newNode->next = NULL;
        newNode->name = malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(newNode->name, name);
    }
    return newNode;
}

static const char *freeFriendNode(FriendNode **node){
    const char *name = (*node)->name;
    free(*node);
    return name;
}

void freeFriendsList(FriendList fl){
    FriendNode *curr;

    while(fl->head){
        curr = fl->head;
        fl->head = fl->head->next;
        freeFriendNode(&curr);
    }
}

void addFriendAtHead(FriendList fl, const char *name){

    if(!fl || !name){
        fprintf(stderr, "ERROR: INVALID INPUT TO FUNTION internalAddFriendAtHead\n");
        return;
    }

    if(searchForFriend(fl, name) != NULL){
        fprintf(stderr, "ERROR: USER ALREADY EXISTS IN THIS FRIENDLIST\n");
        return;
    }

    FriendNode *newNode = createFriendNode(name);

    if(!newNode)
        return;

    newNode->next = fl->head;
    fl->head = newNode;
    fl->num_of_friends++;
}

FriendNode *searchForFriend(FriendList fl, const char *name){
    FriendNode *cursor = fl->head;

    while(cursor){
        if(!strcmp(cursor->name, name))
            return cursor;
        cursor = cursor->next;
    }

    return NULL;
}

const char *deleteFriend(FriendList fl, const char *name){
    FriendNode *temp = fl->head, *prev;

    if(temp && !strcmp(temp->name, name)){
        fl->head = temp->next;
        fl->num_of_friends--;
        return (freeFriendNode(&temp));
    }

    while(temp && strcmp(temp->name, name) != 0){
        prev = temp;
        temp = temp->next;
    }

    if(temp){
        prev->next = temp->next;
        fl->num_of_friends--;
        return (freeFriendNode(&temp));
    }

    return NULL;
}