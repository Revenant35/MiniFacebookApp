#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "Node.h"
#include "Hash.h"
#include "Utility.h"
#include "friends.h"

#define MAX_INPUT_SIZE (130)

//  Adds a user to the hash table in O(1) time
void addUser(HashTable ht, const char *name){
    if(!name || !ht){
        fprintf(stderr, "FORMATTING ERROR: p <name>\n");
        return;
    }

    hashInsert(ht, name);
}

//  Deletes a user in approximately O(1) time
//void deleteUser(HashTable ht, char *name){
//    Node *node;
//
//    if(!ht || !name){
//        fprintf(stderr, "FORMATTING ERROR: l <name>\n");
//        return;
//    }
//
//    node = hashSearch(ht, name);
//
//    if(!node)
//        return;
//
//    delNode(&node, name);
//}

//  Prints all users in system in O(n) time where n is
//      the size of the table
void PrintUsers(HashTable ht){
    Node *cursor = NULL;
    for(int i = 0; i < ht->size; i++){
        cursor = ht->table[i];
        while(cursor){
            printf("User %d: %s\n", i, cursor->name);
            cursor = cursor->next;
        }
    }
}

//  Adds a friendship link between two users in O(m) time where
//      m is the sum of the friends of the two users.
//  Note: This can be O(1) time by disabling duplicate user checking
void addFriend(HashTable ht, const char *name1, const char *name2){

    Node *node1, *node2;

    if(!name1 || !name2 || !ht){
        fprintf(stderr, "FORMATTING ERROR: f <name1> <name2>\n");
        return;
    }

    node1 = hashSearch(ht, name1);
    node2 = hashSearch(ht, name2);

    if(!node1 || !node2 || node1==node2)
        return;

    addFriendAtHead(node1->friendList, name2);
    addFriendAtHead(node2->friendList, name1);
}

//  Deletes the friendship-link between two users in O(m) time
//      where m is the sum of the friends of the two users
void delFriend(HashTable ht, const char *name1, const char *name2){
    Node *node1, *node2;

    if(!name1 || !name2 || !ht){
        fprintf(stderr, "FORMATTING ERROR: u <name1> <name2>\n");
        return;
    }

    node1 = hashSearch(ht, name1);
    node2 = hashSearch(ht, name2);

    if(!node1 || !node2 || node1==node2)
        return;

    deleteFriend(node1->friendList, name2);
    deleteFriend(node2->friendList, name1);
}

//  Sees if two users are friends in O(m) time where m is
//      the sum of the friends of the two users
void queryFriend(HashTable ht, const char *name1, const char *name2){

    if(!name1 || !name2 || !ht){
        fprintf(stderr, "FORMATTING ERROR: q <name1> <name2>\n");
        return;
    }

    Node *node1 = hashSearch(ht, name1), *node2 = hashSearch(ht, name2);
    if(!node1)
        printf("Could not locate user %s\n", name1);
    if(!node2){
        printf("Could not locate user %s\n", name2);
    }
    if(!node1 || !node2)
        return;

    printf(searchForFriend(node1->friendList, name2) && searchForFriend(node2->friendList, name1) ? "Yes\n" : "No\n");
}

//  Prints all friends of the specified user in O(m) time where
//      m is the number of friends the user has
void printFriends(HashTable ht, char *name){
    Node *node;
    FriendNode *cursor;

    if(!name || !ht){
        fprintf(stderr, "FORMATTING ERROR: l <name>\n");
        return;
    }

    node = hashSearch(ht, name);

    if(!node || node->friendList->num_of_friends == 0)
        return;

    for(cursor = node->friendList->head; cursor; cursor = cursor->next){
        printf("%s ", formatName(cursor->name));
    }
    printf("\n");

}

//  Frees all memory allocated to the program in O(n) time where
//      n is the size of the table
void terminateProgram(HashTable ht, char *buf){
    freeHashTable(ht);
    free(buf);
}

//  Driver code
void run(){

    //  Allocate memory for a 2^7 byte name string
    char *instruction, *name1, *name2, *buf = malloc(MAX_INPUT_SIZE * sizeof(char));

    //  Create a hashtable to store users in
    HashTable ht = createHashTable();

    //  Delimiter used to parse the string from stdin
    const char delim[2] = " ";

    //  Check for malloc failure
    if(!ht || !buf){
        fprintf(stderr, "ERROR: UNABLE TO ALLOCATE SUFFICIENT MEMORY\n");
        return;
    }

    //  The run loop
    while(true){

        //  Get user-input
        scanf("%[^\n]130s", buf);

        buf = strLower(buf);

        instruction = strtok(buf, delim);
        name1 = formatName(strtok(NULL, delim));
        name2 = formatName(strtok(NULL, delim));

        //  Carry out said input
        switch(*instruction){
            case 'q':
                queryFriend(ht, name1, name2);
                break;
            case 'l':
                printFriends(ht, name1);
                break;
            case 'p':
                addUser(ht, name1);
                break;
            case 'f':
                addFriend(ht, name1, name2);
                break;
            case 'u':
                delFriend(ht, name1, name2);
                break;
            case 'a':
                PrintUsers(ht);
                break;
//            case 'd':
//                deleteUser(ht, name1);
//                break;
            case 'x':
                terminateProgram(ht, buf);
                return;
        }
        //  Flush stdin to help prevent user error
        fflush(stdin);
    }
}

int main() {
    run();
}
