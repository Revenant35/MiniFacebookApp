
#ifndef PROGRAMMING_ASSIGNMENT_1_NODE_H
#define PROGRAMMING_ASSIGNMENT_1_NODE_H

#include <stdbool.h>
#include "friends.h"

typedef struct node_struct Node;
struct node_struct {
    Node *next;
    char *name;
    FriendList friendList;
};

Node *createNode(const char *);

const char *delNode(Node **, char *);
void addNode(Node **, Node *);

#endif //PROGRAMMING_ASSIGNMENT_1_NODE_H
