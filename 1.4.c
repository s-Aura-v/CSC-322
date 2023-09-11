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

//functions *add later*
struct Room createRoom(int roomNum, int state);
void assignRoom(int numOfRooms);


int main() {
    // Setup (Adding User Input)
    int numOfRooms;
    int numOfCreatures;

    //Inputting the Rooms
    printf("# of rooms: ");
    scanf("%d", &numOfRooms);

    rooms = (struct Room *) malloc(sizeof(struct Room) * numOfRooms);

    int state, north, south, east, west;    //hold values temporarily
    for (int i = 0; i < numOfRooms; i++) {
        printf("rooms: ");
        scanf("%d %d %d %d %d", &state, &rooms[i].northNum, &rooms[i].southNum, &rooms[i].eastNum, &rooms[i].westNum);
        rooms[i] = createRoom(i, state);
    }
    assignRoom(numOfRooms);

    //test code

//    for (int i = 0; i < numOfRooms; i++) {
//        printf("%d %d %d %d %d", *rooms[i].north, &rooms[i].south, &rooms[i].east, &rooms[i].west);
//    }
//
    //free memory
    free(rooms);

}

struct Room createRoom(int roomNum, int state) {
    rooms->roomNum = roomNum;
    rooms->state = state;
    rooms->north = NULL;
    rooms->south = NULL;
    rooms->east = NULL;
    rooms->west = NULL;
}

void assignRoom(int numOfRooms) {
    for (int i = 0; i < numOfRooms; i++) {
        for (int j = 0; j < numOfRooms; j++) {
            if (rooms[i].northNum == rooms[j].roomNum) {
                *rooms[i].north = rooms[j];
            }
            if (rooms[i].southNum == rooms[j].roomNum) {
                *rooms[i].south = rooms[j];
            }
            if (rooms[i].eastNum == rooms[j].roomNum) {
                *rooms[i].east = rooms[j];
            }
            if (rooms[i].westNum == rooms[j].roomNum) {
                *rooms[i].west = rooms[j];
            }
        }
    }
}

