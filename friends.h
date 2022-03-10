
#ifndef PROGRAMMING_ASSIGNMENT_1_FRIENDS_H
#define PROGRAMMING_ASSIGNMENT_1_FRIENDS_H


typedef struct friend_node_struct FriendNode;
struct friend_node_struct {
    FriendNode *next;
    char *name;
};

typedef struct friend_list_struct {
    FriendNode *head;
    int num_of_friends;
} *FriendList;

FriendList createList();
void freeFriendsList(FriendList fl);
void addFriendAtHead(FriendList fl, const char *name);
FriendNode *searchForFriend(FriendList fl, const char *name);
const char *deleteFriend(FriendList fl, const char *name);

#endif //PROGRAMMING_ASSIGNMENT_1_FRIENDS_H
