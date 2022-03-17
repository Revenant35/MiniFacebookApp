
#ifndef PROGRAMMING_ASSIGNMENT_1_FRIENDS_H
#define PROGRAMMING_ASSIGNMENT_1_FRIENDS_H

typedef struct friend_node_struct FriendNode;
typedef struct node_struct Node;

#include "hash.h"

struct friend_node_struct {
    FriendNode *next;
    Node *friend;
};

typedef struct friend_table_struct{
    FriendNode **table;
    unsigned long size;
    unsigned long n;
}*FriendTable;

struct node_struct {
    Node *next;
    char *name;
    FriendTable friends;
};

FriendTable extCreateFriendTable();
void extUnsafeDeleteFriendsList(Node *self);
void extSafeDeleteFriendsList(Node *self);
void extInsertFriend(Node *self, Node *friend);
void extDeleteFriend(Node *self, Node *friend);
bool extSearchFriend(Node *self, Node *friend);
void extPrintFriends(Node *self);

#endif //PROGRAMMING_ASSIGNMENT_1_FRIENDS_H
