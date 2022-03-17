
#include "users.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static void internalInsertFriend(FriendTable ft, FriendNode *friendNode);
static void internalUDeleteFriendsList(User *user);
static void internalInsertUser(UserTable ut, User *user);


static FriendNode *internalCreateFriendNode(User *user){
    FriendNode *newFriendNode = malloc(sizeof(FriendNode));

    if(!newFriendNode)
        return NULL;

    newFriendNode->next = NULL;
    newFriendNode->user = user;

    return newFriendNode;
}

static FriendTable internalCreateFriendTable(unsigned long size){
    FriendTable ft;
    int i;
    ft = malloc(sizeof(*ft));

    if(!ft)
        return NULL;

    ft->size = size;
    ft->n = 0;
    ft->table = malloc(ft->size * sizeof(FriendNode));

    if(!ft->table){
        free(ft);
        return NULL;
    }

    for(i = 0; i < ft->size; i++){
        ft->table[i] = NULL;
    }

    return ft;
}

static void internalFreeFriendTable(FriendTable ft){
    int i;
    FriendNode *cursor, *next;
    for(i = 0; i < ft->size; i++){
        for(cursor = ft->table[i]; cursor; cursor = next){
            next = cursor->next;
            internalUDeleteFriendsList(cursor);
            free(cursor);
        }
    }
    free(ft->table);
    free(ft);
}

static void internalGrowFriendTable(FriendTable ft){
    FriendTable ft2;
    struct friend_table_struct swap;
    int i;
    FriendNode *cursor = NULL;

    ft2 = internalCreateFriendTable(ft->size * GROWTH_FACTOR);

    if(!ft2)
        return;

    for(i = 0; i < ft->size; i++){
        for(cursor = ft->table[i]; cursor; cursor = cursor->next) {
            internalInsertFriend(ft2, cursor);
        }
    }

    swap = *ft;
    *ft = *ft2;
    *ft2 = swap;

    internalFreeFriendTable(ft2);
}



static void internalInsertFriend(FriendTable ft, FriendNode *friendNode){
    unsigned long h;

    h = hash(friendNode->user->name) % ft->size;

    friendNode->next = ft->table[h];
    ft->table[h] = friendNode;

    ft->n++;

    if(ft->n >= ft->size * MAX_LOAD_FACTOR)
        internalGrowFriendTable(ft);
}

static void internalDeleteFriend(FriendTable ft, User *friend){
    unsigned long h;
    FriendNode *curr, *prev;

    h = hash(friend->name) % ft->size;
    curr = ft->table[h];

    if(curr && curr->user == friend){
        ft->table[h] = curr->next;
        free(curr);
        curr = NULL;
    }

    while(curr && curr->user != friend){
        prev = curr;
        curr = curr->next;
    }

    if(curr){
        prev->next = curr->next;
        free(curr);
    }
}

static bool internalSearchFriend(FriendTable ft, User *friend){
    unsigned long h;
    FriendNode *curr;

    h = hash(friend->name) % ft->size;
    curr = ft->table[h];

    while(curr && curr->user != friend){
        curr = curr->next;
    }

    return ((!curr) ? false : true);
}



static void internalUDeleteFriendsList(User *user){
    FriendNode *curr, *prev;
    int i;

    if(!user || !user->friends)
        return;

    for(i = 0; i < user->friends->size; i++){
        curr = user->friends->table[i];
        while(curr){
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }
}

static void internalSDeleteFriendsList(User *user){
    FriendNode *curr, *prev;
    int i;

    if(!user || !user->friends)
        return;

    for(i = 0; i < user->friends->size; i++){
        curr = user->friends->table[i];
        while(curr){
            prev = curr;
            curr = curr->next;
            internalDeleteFriend(prev->user->friends, user);
            free(prev);
        }
    }
}




static User *createUser(const char *name){
    User *newUser = malloc(sizeof(User));

    if(!newUser)
        return NULL;

    newUser->next = NULL;
    newUser->friends = internalCreateFriendTable(INITIAL_FRIEND_SIZE);
    newUser->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(newUser->name, name);

    return newUser;
}

static UserTable internalCreateTable(const unsigned long size){
    UserTable ut;
    int i;
    ut = malloc(sizeof(*ut));

    if(!ut)
        return NULL;

    ut->size = size;
    ut->n = 0;
    ut->table = malloc(ut->size * sizeof(User));

    if(!ut->table){
        free(ut);
        return NULL;
    }

    for(i = 0; i < ut->size; i++){
        ut->table[i] = NULL;
    }

    return ut;
}

static void internalGrowUserTable(UserTable ut){
    UserTable ut2;
    struct user_table_struct swap;
    int i;
    User *cursor = NULL;

    ut2 = internalCreateTable(ut->size * GROWTH_FACTOR);

    if(!ut2)
        return;

    for(i = 0; i < ut->size; i++){
        for(cursor = ut->table[i]; cursor; cursor = cursor->next) {
            internalInsertUser(ut2, cursor);
        }
    }

    swap = *ut;
    *ut = *ut2;
    *ut2 = swap;

//    freeFriendTable(ut2);
}

static void internalFreeTable(UserTable ut){
    int i;
    User *cursor, *next;
    for(i = 0; i < ut->size; i++){
        for(cursor = ut->table[i]; cursor; cursor = next){
            next = cursor->next;
            internalUDeleteFriendsList(cursor);
            free(cursor);
        }
    }
    free(ut->table);
    free(ut);
}


static void internalInsertUser(UserTable ut, User *user){
    unsigned long h;

    h = hash(user->name) % ut->size;

    user->next = ut->table[h];
    ut->table[h] = user;

    ut->n++;
}

static void internalDeleteUser(UserTable ut, const char *username){
    unsigned long h;
    User *curr, *prev;

    h = hash(username) % ut->size;
    curr = ut->table[h];

    if(curr && !strcmp(curr->name, username)){
        ut->table[h] = curr->next;
        internalSDeleteFriendsList(curr);
        free(curr);
        curr = NULL;
    }

    while(curr && strcmp(curr->name, username) != 0){
        prev = curr;
        curr = curr->next;
    }

    if(curr){
        prev->next = curr->next;
        internalSDeleteFriendsList(curr);
        free(curr);
    }
}

static User *internalSearch(UserTable ut, const char *username){
    User *user;
    unsigned long h;

    h = hash(username) % ut->size;

    user = ut->table[h];

    while(user){
        if(!strcmp(user->name, username))
            return user;
        user = user->next;
    }

    return NULL;
}






UserTable createUserTable(){
    return internalCreateTable(INITIAL_USER_SIZE);
}

void insertUser(UserTable ut, const char *username){
    if(!ut || !ut->table || !username)
        return;

    if(internalSearch(ut, username))
        return;

    internalInsertUser(ut, createUser(username));

    if(ut->n >= ut->size * MAX_LOAD_FACTOR)
        internalGrowUserTable(ut);
}

void deleteUser(UserTable ut, const char *username){
    if(!ut || !ut->table || !username)
        return;

    internalDeleteUser(ut, username);
}

void createFriendship(UserTable ut, const char *username1, const char *username2){
    if(!ut || !ut->table || !username1 || !username2)
        return;

    if(!strcmp(username1, username2) || queryFriendship(ut, username1, username2))
        return;

    User *u1 = internalSearch(ut, username1);
    User *u2 = internalSearch(ut, username2);

    if(!u1 || !u2)
        return;

    internalInsertFriend(u1->friends, internalCreateFriendNode(u2));
    internalInsertFriend(u2->friends, internalCreateFriendNode(u1));
}

void deleteFriendship(UserTable ut, const char *username1, const char *username2){
    if(!ut || !ut->table || !username1 || !username2)
        return;

    User *u1 = internalSearch(ut, username1);
    User *u2 = internalSearch(ut, username2);

    internalDeleteFriend(u1->friends, u2);
    internalDeleteFriend(u2->friends, u1);
}

bool queryFriendship(UserTable ut, const char *username1, const char *username2){
    if(!ut || !ut->table || !username1 || !username2)
        return false;

    User *u1 = internalSearch(ut, username1);
    User *u2 = internalSearch(ut, username2);

    if(!u1 || !u2)
        return false;

    return internalSearchFriend(u1->friends, u2) && internalSearchFriend(u2->friends, u1);
}

void printUsers(UserTable ut){
    if(!ut || !ut->table)
        return;
    User *cursor = NULL;
    for(int i = 0; i < ut->size; i++){
        cursor = ut->table[i];
        while(cursor){
            printf("User %d: %s\n", i, cursor->name);
            cursor = cursor->next;
        }
    }
}

void printFriends(UserTable ut, const char *username){
    if(!ut || !ut->table || !username)
        return;

    User *user = internalSearch(ut, username);

    if(!user)
        return;

    FriendNode *curr;
    int i;

    for(i = 0; i < user->friends->size; i++){
        curr = user->friends->table[i];
        if(curr) {
            while (curr) {
                printf("%s ", curr->user->name);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

void freeUserTable(UserTable ut){
    internalFreeTable(ut);
}


