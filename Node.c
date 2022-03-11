
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Node.h"

//  Creates and returns a new node
Node *createNode(const char *name){
    Node *newNode = malloc(sizeof(Node));
    if(newNode) {
        newNode->next = NULL;
        newNode->head = NULL;
        if(name) {
            newNode->name = malloc(sizeof(char) * strlen(name) + 1);
            strcpy(newNode->name, name);
        } else
            newNode->name = NULL;
    }
    return newNode;
}

//  Frees node pointed to by target, returns character pointer pointing to address occupied by the name
const char *freeNode(Node *target){
    char *temp;

    if(!target){
        fprintf(stderr, "ERROR: NULL INPUT TO FUNCTION freeNode\n");
        return NULL;
    }

    temp = target->name;
    safeDeleteFriendsList(&temp);
    free(target);
    return temp;
}

const char *deleteNode(Node **head, const char *name){

    Node *temp = *head, *prev;

    if(!name){
        fprintf(stderr, "ERROR: NULL INPUT TO FUNCTION deleteNode\n");
        return NULL;
    }

    if(temp && !strcmp(temp->name, name)){
        *head = temp;
        safeDeleteFriendsList(temp);
        return freeNode(temp);;
    }

    while(temp && strcmp(temp->name, name) != 0){
        prev = temp;
        temp = temp->next;
    }

    if(temp){
        prev->next = temp->next;
        safeDeleteFriendsList(temp);
        return freeNode(temp);
    }

    return NULL;
}

void addNode(Node **head, const char *name){

    if(!name){
        fprintf(stderr, "ERROR: NULL INPUT TO FUNCTION addNode\n");
        return;
    }

    Node *newNode = createNode(name);

    newNode->next = *head;
    *head = newNode;
}
