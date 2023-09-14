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

    // creating current room
    struct Room currentRoom;
    for (int i = 0; i < numOfRooms; i++) {
        for (int j = 0; j < 10; j++) {
            if (rooms[i].creatures[j].type == 3) {      // 3 = PC
                currentRoom = rooms[i];
            }
        }
    }

    //Gameplay Loop
    char input[20];
    while (respect > 0 || respect < 80) {
        //Set the input
        printf("Enter a command: ");
        scanf("%s", input);

        if (strcmp(input, "look") == 0) {
            look(currentRoom);
        }
        else if (strcmp(input, "east") == 0) {
            currentRoom = changeRoomEast(currentRoom);
        }
        else if (strcmp(input, "leaveRoom") == 0) {
            currentRoom.state = 0;
            currentRoom = leaveRoom(currentRoom, 2);
        }
        else if (strcmp(input, "exit") == 0) {
            break;
        }
    }



//    Test
    for (int i = 0; i < numOfRooms; i++) {
        for (int j = 0; j < 10; j++) {
        printf("Creature #: %d | Type: %d| Location: %d\n", rooms[i].creatures[j].creatureNum, rooms[i].creatures[j].type, rooms[i].creatures[j].location);
        }
    }

}

struct Room changeRoomEast(struct Room currentRoom) {     //remember to update the creatures
    if (currentRoom.eastNum == -1) {
        printf("You tried going East, but ran into a wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {  //edit it later to include size of Room
            if (rooms[i].roomNum == currentRoom.eastNum) {
                currentRoom = rooms[i];
            }
        }
    }
    return currentRoom;
}


struct Room leaveRoom(struct Room currentRoom, int creatureNum) {
    bool isExecuted = false;
    if (currentRoom.eastNum != -1) {
        for (int i = 0; i < 10; i++) {
            if (currentRoom.creatures[i].creatureNum == creatureNum) {
                for (int j = 0; j < 10; j++) {
                    if (currentRoom.east->creatures[j].type == 0 && isExecuted == false) {        //room is free
                        currentRoom.east->creatures[j] = currentRoom.creatures[i];
                        currentRoom.east->creatures[j].location = currentRoom.roomNum;
                        //Now remove it from old room [bit wonky]
                        currentRoom.creatures[i].type = -1;
                        currentRoom.creatures[i].creatureNum = -1;       //this might be wonky
                        currentRoom.creatures[i].location = -1;
                        isExecuted = true;
                    }
                }
            }
        }
    }
    return currentRoom;
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

struct Room look(struct Room currentRoom) {
    printf("Room number: %d | Room state: %d | ", currentRoom.roomNum, currentRoom.state); /* Print out the room cleanliness */
    //Print out the neighbors
    if (currentRoom.northNum != -1) {
        printf("%d to the north | ", currentRoom.northNum);
    }
    if (currentRoom.southNum != -1) {
        printf("%d to the south | ", currentRoom.southNum);
    }
    if (currentRoom.eastNum != -1) {
        printf("%d to the east | ", currentRoom.eastNum);
    }
    if (currentRoom.westNum != -1) {
        printf("%d to the west | ", currentRoom.westNum);
    }

    //Print out the creatures
    printf("contains:\n");  /*work on this more, to include all the creatures in the room*/
    for (int i = 0; i < 10; i++) {
        if (currentRoom.creatures[i].type == 3) {
            printf ("PC\n");
        }
        else if (currentRoom.creatures[i].type == 2) {
            printf ("human %d\n", currentRoom.creatures[i].creatureNum);
        }
        else if (currentRoom.creatures[i].type == 1) {
            printf ("animal %d\n", currentRoom.creatures[i].creatureNum);
        }
    }
    return currentRoom;
}

