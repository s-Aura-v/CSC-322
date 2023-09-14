//
// Created by Saurav Lamichhane on 9/13/23.
// CREATURE TYPES: 1 - ANIMAL | 2 - NPC | 3 - PC

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
    int creatureCounter;
};

// Global variables
int respect = 40;
struct Room *rooms = NULL;
struct Creature *creatures = NULL;

//functions *add later*
void help();
void createRoom(int roomNum);
void assignRoom(int numOfRooms);
void assignCreatures(int numOfCreatures, int numOfRooms);
struct Room look(struct Room currentRoom);
struct Room clean(struct Room currentRoom, bool roomStatus);
struct Room dirty(struct Room currentRoom, bool roomStatus);
void updateRoomState(struct Room currentRoom);
struct Room changeRoomEast(struct Room currentRoom);
struct Room changeRoomWest(struct Room currentRoom);
struct Room changeRoomNorth(struct Room currentRoom);
struct Room changeRoomSouth(struct Room currentRoom);
struct Room creatureClean(struct Room currentRoom, int creatureType);
struct Room creatureDirty(struct Room currentRoom, int creatureType);
void decreaseRespect();
void higherDecreaseRespect();
void increaseRespect();
void higherincreaseRespect();
struct Room growl(struct Room currentRoom);
struct Room grumble(struct Room currentRoom);
struct Room lick(struct Room currentRoom);
struct Room smile(struct Room currentRoom);
struct Room leaveRoom(struct Room currentRoom, int creatureType);
struct Room checkCreatureEmotion(struct Room currentRoom, bool roomStatus);


int main() {
    // Setup (Adding User Input)
    int numOfRooms;
    int numOfCreatures;
    bool roomStatus = true;

    //Inputting the Rooms
    printf("# of rooms: ");
    scanf("%d", &numOfRooms);
    rooms = (struct Room *) malloc(sizeof(struct Room) * numOfRooms);
    for (int i = 0; i < numOfRooms; i++) {
        printf("rooms: ");
        scanf("%d %d %d %d %d", &rooms[i].state, &rooms[i].northNum, &rooms[i].southNum, &rooms[i].eastNum,
              &rooms[i].westNum);
        createRoom(i);
    }
    assignRoom(numOfRooms);

    //Creatures
    printf("# of creatures: ");
    scanf("%d", &numOfCreatures);
    creatures = (struct Creature *) malloc(sizeof(struct Creature) * numOfCreatures);
    for (int i = 0; i < numOfCreatures; i++) {
        printf("type + location: ");
        scanf("%d %d", &creatures[i].type, &creatures[i].location);
    }
    assignCreatures(numOfCreatures, numOfRooms);

    //Test
    for (int i = 0; i < numOfRooms; i++) {
        for (int j = 0; j < 10; j++) {
        printf("Creature #: %d | Type: %d| Location: %d\n", rooms[i].creatures[j].creatureNum, rooms[i].creatures[j].type, rooms[i].creatures[j].location);
        }
    }

}

void createRoom(int roomNum) {
    rooms[roomNum].roomNum = roomNum;
    rooms[roomNum].north = NULL;
    rooms[roomNum].south = NULL;
    rooms[roomNum].east = NULL;
    rooms[roomNum].west = NULL;
}

void assignRoom(int numOfRooms) {
    for (int i = 0; i < numOfRooms; i++) {
        for (int j = 0; j < numOfRooms; j++) {
            if (rooms[i].northNum == rooms[j].roomNum) {
                rooms[i].north = &rooms[j];
            }
            if (rooms[i].southNum == rooms[j].roomNum) {
                rooms[i].south = &rooms[j];
            }
            if (rooms[i].eastNum == rooms[j].roomNum) {
                rooms[i].east = &rooms[j];
            }
            if (rooms[i].westNum == rooms[j].roomNum) {
                rooms[i].west = &rooms[j];
            }
        }
    }
}

void assignCreatures(int numOfCreatures, int numOfRooms) {
    for (int i = 0; i < numOfCreatures; i++) {
        creatures[i].creatureNum = i;
    }
    for (int i = 0; i < numOfRooms; i++) {
        int roomIndex = 0;
        for (int j = 0; j < numOfCreatures; j++) {
            if (creatures[j].location == rooms[i].roomNum) {
                rooms[i].creatures[roomIndex] = creatures[j];
                roomIndex++;
            }
        }
    }
}