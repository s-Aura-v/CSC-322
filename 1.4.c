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
struct Room createRoom(int roomNum);
//void assignRoom(int numOfRooms);


int main() {
    // Setup (Adding User Input)
    int numOfRooms;
    int numOfCreatures;

    //Inputting the Rooms
    printf("# of rooms: ");
    scanf("%d", &numOfRooms);

    rooms = (struct Room *) malloc(sizeof(struct Room) * numOfRooms);

    int state;    //hold values temporarily
    for (int i = 0; i < 3; i++) {
        printf("rooms: ");
        scanf("%d %d %d %d %d", &rooms[i].state, &rooms[i].northNum, &rooms[i].southNum, &rooms[i].eastNum, &rooms[i].westNum);
        rooms[i] = createRoom(i);
    }
//    assignRoom(numOfRooms);

    //test code

    for (int i = 0; i < numOfRooms; i++) {
        printf("%d\n", rooms[i].state);
    }

    //free memory
    free(rooms);

}

struct Room createRoom(int roomNum) {
    rooms[roomNum].roomNum = roomNum;
    rooms[roomNum].north = NULL;
    rooms[roomNum].south = NULL;
    rooms[roomNum].east = NULL;
    rooms[roomNum].west = NULL;
}

//void assignRoom(int numOfRooms) {
//    for (int i = 0; i < numOfRooms; i++) {
//        for (int j = 0; j < numOfRooms; j++) {
//            if (rooms[i].northNum == rooms[j].roomNum) {
//                rooms[i].north = &rooms[j];
//            }
//            if (rooms[i].southNum == rooms[j].roomNum) {
//                rooms[i].south = &rooms[j];
//            }
//            if (rooms[i].eastNum == rooms[j].roomNum) {
//                rooms[i].east = &rooms[j];
//            }
//            if (rooms[i].westNum == rooms[j].roomNum) {
//                rooms[i].west = &rooms[j];
//            }
//        }
//    }
//}

