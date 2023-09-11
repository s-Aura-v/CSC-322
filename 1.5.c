//
// Created by Saurav Lamichhane on 9/11/23.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct Creature {
    int creatureNum;
    int type;
    int location;
};

struct Room {
    int roomNum;
    int state;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    int northNum;
    int southNum;
    int eastNum;
    int westNum;
    struct Creature creatures[10];
};

// Global variables
int respect = 40;
struct Room *rooms = NULL;
struct Creature *creatures = NULL;

//functions
void createRooms(int numOfRooms);

int main() {
    // Setup (Adding User Input)
    int numOfRooms;
    int numOfCreatures;

    //Inputting the Rooms
    printf("# of rooms: ");
    scanf("%d", &numOfRooms);

    rooms = (struct Room *) malloc(sizeof(struct Room) * numOfRooms);

    int north, south, east, west;
    for (int i = 0; i < numOfRooms; i++) {
        printf("rooms: ");
        scanf("%d %d %d %d %d", &rooms[i].state, &rooms[i].northNum, &rooms[i].southNum, &rooms[i].eastNum, &rooms[i].westNum);
    }
    createRooms(numOfRooms);

    for (int i = 0; i < 10; i++) {
        printf("%d %d %d %d %d\n", rooms[i].state, rooms[i].northNum, rooms[i].southNum, rooms[i].eastNum, rooms[i].westNum);
    }
}

void createRooms(int numOfRooms) {
    for (int i = 0; i < numOfRooms; i++) {
        if (rooms[i].northNum != -1) {

        }
    }
}