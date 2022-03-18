
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "friends.h"

static void internalFriendInsert(HashTable ht, char *username1, char *username2){

    Node *user1 = hashSearch(ht, username1);
    Node *user2 = hashSearch(ht, username2);

    if(!user1 || !user2 || hashSearch((HashTable)user1->data, username2))
        return;

    hashInsert(user1->data, user2->key, user2);
    hashInsert(user2->data, user1->key, user2);
}

static void internalFriendDelete(HashTable ht, char *username1, char *username2){

    Node *user1 = hashSearch(ht, username1);
    Node *user2 = hashSearch(ht, username2);

    if(!user1 || !user2)
        return;

    hashDelete((HashTable)user1->data, username2);
    hashDelete((HashTable)user2->data, username1);

}

static bool internalFriendSearch(HashTable ht, char *username1, char *username2){

    Node *user1 = hashSearch(ht, username1);
    Node *user2 = hashSearch(ht, username2);

    if(!user1 || !user2)
        return false;

    return((hashSearch((HashTable)user1->data, username2) == NULL) ? false : true);
}

void insertFriend(HashTable ht, char *username1, char *username2){

    if(!username1 || !username2 || !strcmp(username1, username2))
        return;

    internalFriendInsert(ht, username1, username2);
}

bool searchFriend(HashTable ht, char *username1, char *username2){
    if(!username1 || !username2)
        return false;

    return internalFriendSearch(ht, username1, username2);
}

void deleteFriend(HashTable ht, char *username1, char *username2){
    if(!username1 || !username2)
        return;

    internalFriendDelete(ht, username1, username2);
}

void printFriends(HashTable ht, char *username){

    HashTable friends;
    Node *curr, *temp;
    int i;

    if(!username)
        return;

    temp = hashSearch(ht, username);

    if(!temp)
        return;

    friends = temp->data;

    for(i = 0; i < friends->len; i++){
        curr = friends->table[i];
        if(curr) {
            while (curr) {
                printf("%s ", curr->key);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}
