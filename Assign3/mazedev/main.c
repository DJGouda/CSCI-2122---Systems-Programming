/* @Duren Gouda */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linkedlist.h"

typedef struct Room {
    char *name;
    linked_list_t doors;  // list of connected rooms
} Room;

Room *findRoom(linked_list_t rooms, const char *name);
void maze();

int main() {
    maze();
    return 0;
}

// method to find room in the linked list
Room *findRoom(linked_list_t rooms, const char *name) {
    ll_iterator_t iter = ll_iterator_new(rooms);
    while (ll_has_next(iter)) {
        Room *room = (Room *) ll_next(iter);
        if (strcmp(room->name, name) == 0) {
            ll_iterator_destroy(iter);
            return room;
        }
    }
    ll_iterator_destroy(iter);
    return NULL;
}

// main maze method for the input and to validate moves
void maze() {
    linked_list_t rooms = ll_new();

    // read rooms
    char buffer[50];
    while (scanf("%s", buffer) && strcmp(buffer, "END") != 0) {
        Room *room = malloc(sizeof(Room));
        room->name = strdup(buffer);
        room->doors = ll_new();
        ll_add_back(rooms, room);
    }

    // read doors
while (scanf("%s", buffer) && strcmp(buffer, "END") != 0) {
    char dest[50];
    
    // check if source room exists
    Room *sourceRoom = findRoom(rooms, buffer);
    if (!sourceRoom) {
        printf("Oops: Cannot find room %s.\n", buffer);
        
        // read the destination room name anyway
        scanf("%s", dest);
        
        // check if destination room exists
        Room *finalRoom = findRoom(rooms, dest);
        if (!finalRoom) {
            printf("Oops: Cannot find room %s.\n", dest);
        }
        
        continue;
    }
    
    // read destination room name
    scanf("%s", dest);
    Room *finalRoom = findRoom(rooms, dest);
    if (!finalRoom) {
        printf("Oops: Cannot find room %s.\n", dest);
        continue;
    }
    
    // adding a oneway door
    ll_add_back(sourceRoom->doors, finalRoom);
}

    // read the next moves
    Room *currentRoom = NULL;
    int firstMove = 1;

    while (scanf("%s", buffer) && strcmp(buffer, "END") != 0) {
        Room *nextRoom = findRoom(rooms, buffer);

        if (!nextRoom) {
            printf("Oops: Cannot find room %s.\n", buffer);
            return;
        }

        if (firstMove) {
            currentRoom = nextRoom;
            printf("Entering room %s.\n", currentRoom->name);
            firstMove = 0;
        } else {
            // check fro door exists
            int validMove = 0;
            ll_iterator_t iter = ll_iterator_new(currentRoom->doors);
            while (ll_has_next(iter)) {
                Room *door = (Room *) ll_next(iter);
                if (strcmp(door->name, nextRoom->name) == 0) {
                    validMove = 1;
                    break;
                }
            }
            ll_iterator_destroy(iter);

            if (!validMove) {
                printf("Oops: Room %s does not connect to room %s.\n", currentRoom->name, nextRoom->name);
                return;
            }

            // go to next room
            currentRoom = nextRoom;
            printf("Entering room %s.\n", currentRoom->name);
        }
    }

    if (currentRoom && firstMove == 0) {  // only print if at least one move was valid
        printf("Ended in room %s.\n", currentRoom->name);
    }

    // free all alloacted memory
    ll_iterator_t iter = ll_iterator_new(rooms);
    while (ll_has_next(iter)) {
        Room *room = (Room *) ll_next(iter);
        free(room->name);
        ll_destroy(room->doors);
        free(room);
    }
    ll_iterator_destroy(iter);
    ll_destroy(rooms);
}