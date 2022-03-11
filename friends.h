
#ifndef PROGRAMMING_ASSIGNMENT_1_FRIENDS_H
#define PROGRAMMING_ASSIGNMENT_1_FRIENDS_H

typedef struct friend_node_struct FriendNode;

#include "Node.h"

struct friend_node_struct {
    FriendNode *next;
    Node *friend;
};

void unsafeDeleteFriendsList(Node *self);
void safeDeleteFriendsList(Node *self);
void insertFriend(FriendNode *head, Node *friend);
FriendNode *searchForFriend(FriendNode *head, Node *friend);
void deleteFriend(FriendNode *head, Node *friend);

#endif //PROGRAMMING_ASSIGNMENT_1_FRIENDS_H
