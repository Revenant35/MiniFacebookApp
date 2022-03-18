
#ifndef PROGRAMMING_ASSIGNMENT_1_FRIENDS_H
#define PROGRAMMING_ASSIGNMENT_1_FRIENDS_H

#include "hash.h"

void insertFriend(HashTable ht, char *username1, char *username2);
bool searchFriend(HashTable ht, char *username1, char *username2);
void deleteFriend(HashTable ht, char *username1, char *username2);
void printFriends(HashTable ht, char *username);

#endif //PROGRAMMING_ASSIGNMENT_1_FRIENDS_H
