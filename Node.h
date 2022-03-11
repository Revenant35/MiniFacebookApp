
#ifndef PROGRAMMING_ASSIGNMENT_1_NODE_H
#define PROGRAMMING_ASSIGNMENT_1_NODE_H

typedef struct node_struct Node;

#include "friends.h"

struct node_struct {
    Node *next;
    char *name;
    FriendNode *head;
};


Node *createNode(const char *);
const char *freeNode(Node *target);
const char *deleteNode(Node **, const char *);
void addNode(Node **, const char *);

#endif //PROGRAMMING_ASSIGNMENT_1_NODE_H
