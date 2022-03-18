
#ifndef PROGRAMMING_ASSIGNMENT_1_USERS_H
#define PROGRAMMING_ASSIGNMENT_1_USERS_H

#include <stdbool.h>
#include "friends.h"

HashTable createFriendTable();
void userInsert(HashTable ht, const char *username);
void userDelete(HashTable ht, const char *username);
void printUsers(HashTable ht);
void freeUserTable(HashTable ht);

#endif //PROGRAMMING_ASSIGNMENT_1_USERS_H
