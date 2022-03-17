
#ifndef PROGRAMMING_ASSIGNMENT_1_USERS_H
#define PROGRAMMING_ASSIGNMENT_1_USERS_H


#define MAX_LOAD_FACTOR (1)
#define GROWTH_FACTOR (2)
#define INITIAL_USER_SIZE (1024)
#define INITIAL_FRIEND_SIZE (4)

typedef struct friend_node_struct FriendNode;
typedef struct user_struct User;

#include <stdbool.h>

struct friend_node_struct {
    FriendNode *next;
    User *user;
};

typedef struct friend_table_struct{
    FriendNode **table;
    unsigned long size;
    unsigned long n;
}*FriendTable;

struct user_struct {
    User *next;
    char *name;
    FriendTable friends;
};

typedef struct user_table_struct{
    User **table;
    unsigned long size;
    unsigned long n;
}*UserTable;


UserTable createUserTable();
void insertUser(UserTable ut, const char *username);
void deleteUser(UserTable ut, const char *username);
void printUsers(UserTable ut);
void printFriends(UserTable ut, const char *username);
void createFriendship(UserTable ut, const char *username1, const char *username2);
void deleteFriendship(UserTable ut, const char *username1, const char *username2);
void freeUserTable(UserTable ut);
bool queryFriendship(UserTable ut, const char *username1, const char *username2);

#endif //PROGRAMMING_ASSIGNMENT_1_USERS_H
