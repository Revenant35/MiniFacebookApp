
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "Node.h"
#include "friends.h"

//  Creates and returns a new node
Node *createNode(const char *name){
    Node *newNode = malloc(sizeof(Node));
    if(newNode) {
        newNode->next = NULL;
        newNode->friendList = createList();
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
    freeFriendsList(target->friendList);
    free(target);
    return temp;
}

const char *delNode(Node **head, char *name){

    Node *temp = *head;
    FriendNode *fr = (*head)->friendList->head;

    if(temp && !strcmp(temp->name, name)){
        *head = temp->next;
        return (freeNode(temp));
    }

    return NULL;

}

void addNode(Node **head, Node *newNode){

    if(!newNode){
        fprintf(stderr, "ERROR: NULL INPUT TO FUNCTION addNode\n");
        return;
    }

    newNode->next = *head;
    *head = newNode;
}
