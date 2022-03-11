
#include <stdlib.h>
#include <stdio.h>
#include "friends.h"

static FriendNode *createFriendNode(Node *friend){
    FriendNode *newNode = malloc(sizeof(FriendNode));
    if(newNode) {
        newNode->next = NULL;
        newNode->friend = friend;
    }
    return newNode;
}

static Node *freeFriendNode(FriendNode **node){
    Node *friend = (*node)->friend;
    free(*node);
    return friend;
}

static void freeFriendsList(FriendNode *head){
    FriendNode *curr;

    while(head){
        curr = head;
        head = head->next;
        freeFriendNode(&curr);
    }
}

void unsafeDeleteFriendsList(Node *self){
    freeFriendsList(self->head);
}

void safeDeleteFriendsList(Node *self){
    FriendNode *curr = self->head;

    while(curr){
        deleteFriend(curr->friend->head, self);
        curr = curr->next;
    }

    freeFriendsList(self->head);
}

static void internalInsert(FriendNode **head, Node *friend){

    FriendNode *newNode = createFriendNode(friend);

    newNode->next = *head;
    *head = newNode;

}

static void internalDelete(FriendNode **head, Node *friend){

    FriendNode *temp = *head, *prev;

    if(temp && temp->friend == friend){
        *head = temp;
        freeFriendNode(&temp);
        return;
    }

    while(temp && temp->friend != friend){
        prev = temp;
        temp = temp->next;
    }

    if(temp){
        prev->next = temp->next;
        freeFriendNode(&temp);
    }

}

void insertFriend(FriendNode *head, Node *friend){

    if(!friend){
        fprintf(stderr, "ERROR: INVALID INPUT TO FUNTION addFriend\n");
        return;
    }

    if(searchForFriend(head, friend) != NULL){
        fprintf(stderr, "ERROR: USER ALREADY EXISTS IN THIS FRIENDLIST\n");
        return;
    }

    internalInsert(&head, friend);
}

FriendNode *searchForFriend(FriendNode *head, Node *friend){
    FriendNode *cursor = head;

    while(cursor){
        if(cursor->friend == friend)
            return cursor;
        cursor = cursor->next;
    }

    return NULL;
}

void deleteFriend(FriendNode *head, Node *friend){

    if(!friend){
        fprintf(stderr, "ERROR: INVALID INPUT TO FUNTION deleteFriend\n");
        return;
    }

    if(searchForFriend(head, friend) != NULL){
        fprintf(stderr, "ERROR: USER ALREADY EXISTS IN THIS FRIENDLIST\n");
        return;
    }

    internalDelete(&head, friend);
}