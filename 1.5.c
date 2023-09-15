//
// Created by Saurav Lamichhane on 9/11/23; I'M USING 3 FOR PC BECAUSE 0 IS THE VALUES PRESENT IN UNINITIALIZED ARRAYS
// CREATURE TYPES: 1 - ANIMAL | 2 - NPC | 3 - PC
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


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
void decreaseRespect();
void higherDecreaseRespect();
void increaseRespect();
void higherIncreaseRespect();
struct Room growl(struct Room currentRoom);
struct Room grumble(struct Room currentRoom);
struct Room lick(struct Room currentRoom);
struct Room smile(struct Room currentRoom);
struct Room leaveRoom(struct Room currentRoom, int creatureNum);
struct Room checkCreatureEmotion(struct Room currentRoom, bool roomStatus);
void updateRoomNeighbors(struct Room currentRoom);
struct Room creatureClean(struct Room currentRoom, int creatureNum, bool roomStatus);
struct Room creatureDirty(struct Room currentRoom, int creatureNum, bool roomStatus);
struct Room creatureChangeRoomEast(struct Room currentRoom, int creatureNum);
struct Room creatureChangeRoomWest(struct Room currentRoom, int creatureNum);
struct Room creatureChangeRoomNorth(struct Room currentRoom, int creatureNum);
struct Room creatureChangeRoomSouth(struct Room currentRoom, int creatureNum);





int main() {
    // Setup (Adding User Input)
    srand(time(0));
    int numOfRooms;
    int numOfCreatures;
    bool roomStatus = true;

    //Inputting the Rooms
    printf("# of rooms: ");
    scanf("%d", &numOfRooms);

    rooms = (struct Room *) malloc(sizeof(struct Room) * numOfRooms);

    for (int i = 0; i < numOfRooms; i++) {
        printf("rooms: ");
        scanf("%d %d %d %d %d", &rooms[i].state, &rooms[i].northNum, &rooms[i].southNum, &rooms[i].eastNum, &rooms[i].westNum);
        createRoom(i);
    }
    assignRoom(numOfRooms);

    //test code

    //fix it so that it doesn't run when its null

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

    char input[20];
    while (respect > 0 || respect < 80) {
        //Set the input
        printf("Enter a command: ");
        scanf("%s", input);

        if (strcmp(input, "look") == 0) {
            look(currentRoom);
        }
        else if (strcmp(input, "clean") == 0) {
            currentRoom = clean(currentRoom, roomStatus);
        }
        else if (strcmp(input, "dirty") == 0) {
            currentRoom = dirty(currentRoom, roomStatus);
        }
        else if (strcmp(input, "east") == 0) {
            currentRoom = changeRoomEast(currentRoom);
        }
        else if (strcmp(input, "west") == 0) {
            currentRoom = changeRoomWest(currentRoom);
        }
        else if (strcmp(input, "north") == 0) {
            currentRoom = changeRoomNorth(currentRoom);
        }
        else if (strcmp(input, "south") == 0) {
            currentRoom = changeRoomSouth(currentRoom);
        }
        else if (strcmp(input, "help") == 0) {
            help();
        }
        else if (strcmp(input, "exit") == 0) {
            printf("Goodbye!");
            break;
        }
            //tests
        else if (strcmp(input, "tLook") == 0) {
            for (int i = 0; i < numOfRooms; i++) {
                printf("%d - ", rooms[i].roomNum);
                printf("%d\n", rooms[i].state);
            }
            printf("%d\n", respect);
        }
        else {    //creature commands:
            char command[6];
            int creatureNum;
            char *token = strtok(input, ":");          //separates the input using the : [kinda like indexOf]
            if (token != NULL) {
                // The first token (before the colon) is the creature
                creatureNum = strtol(token, NULL, 10);  //telling it to find an integer with base 10
                token = strtok(NULL, ":");                      //get the value after :
                if (token != NULL) {
                    strncpy(command, token, 6);
                }
            }
            if (strcmp(command, "clean") == 0) {
                currentRoom = creatureClean(currentRoom, creatureNum, roomStatus);
            }
            else if (strcmp(command, "dirty") == 0) {
                currentRoom = creatureDirty(currentRoom, creatureNum, roomStatus);
            }
            else if (strcmp(command, "east") == 0) {
                currentRoom = creatureChangeRoomEast(currentRoom, creatureNum);
            }
            else if (strcmp(command, "west") == 0) {
                currentRoom = creatureChangeRoomWest(currentRoom, creatureNum);
            }
            else if (strcmp(command, "north") == 0) {
                currentRoom = creatureChangeRoomNorth(currentRoom, creatureNum);
            }
            else if (strcmp(command, "south") == 0) {
                currentRoom = creatureChangeRoomSouth(currentRoom, creatureNum);
            }
        }


    }
    //free memory
    free(rooms);
    free(creatures);
}

void help() {
    printf("Important Note: PC, in this game, is recognized as 3 not 0! Change your input accordingly!\n"
           "To enter the amount of rooms, enter an [int]. <The max amount of rooms is 99>. Example: 3\n"
           "To input a room, enter [State North South East West] in order. Example: 0 -1 1 -1 2\n"
           "To enter the amount of creatures, enter an [int]. Example: 4\n"
           "To input a creature, enter [CreatureType CreatureLocation]. Example: 1 0\n"
           "Creature Types: PC - 3 | NPC - 2 | Animal - 1 | Each creature is numbered by when they were inputted, starting from 0.\n"
           "You have several actions in this game: clean, dirty, north, south, east, west.\n"
           "You can command a creature to do an action as well by inputting [creatureNum:action]. Example: 2:clean\n"
           "The game ends when your respect reaches 0 or 80. You lose if it's 0 and win if it's 80.\n");
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

struct Room clean(struct Room currentRoom, bool roomStatus) {
    if (currentRoom.state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
        currentRoom.state = 1;
        roomStatus = true;
        updateRoomState(currentRoom);
        currentRoom = checkCreatureEmotion(currentRoom, roomStatus);
    } else if (currentRoom.state == 1) { /* if it's half-dirty, make it clean*/
        currentRoom.state = 0;
        roomStatus = true;
        updateRoomState(currentRoom);
        currentRoom = checkCreatureEmotion(currentRoom, roomStatus);
    } else {
        printf("Your room is already clean!\n");
    }
    return currentRoom;
}

struct Room dirty(struct Room currentRoom, bool roomStatus) {
    if (currentRoom.state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
        printf("Your room is already dirty!\n");
    } else if (currentRoom.state == 1) { /* if it's half-dirty, make it dirty*/
        currentRoom.state = 2;
        roomStatus = false;
        updateRoomState(currentRoom);
        currentRoom = checkCreatureEmotion(currentRoom, roomStatus);
    } else {
        currentRoom.state = 1;
        roomStatus = false;
        updateRoomState(currentRoom);
        currentRoom = checkCreatureEmotion(currentRoom, roomStatus);
    }
    return currentRoom;
}


void updateRoomState(struct Room currentRoom) {
    for (int i = 0; i < 10; i++) { //maybe use a different index for i < 100 lol sizeof(array)/sizeof(array[0]);
        if (rooms[i].roomNum == currentRoom.roomNum) {
            rooms[i].state = currentRoom.state;
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

struct Room changeRoomWest(struct Room currentRoom) {
    if (currentRoom.westNum == -1) {
        printf("You tried going West, but ran into a wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {  //edit it later to include size of Room
            if (rooms[i].roomNum == currentRoom.westNum) {
                currentRoom = rooms[i];
            }
        }
    }
    return currentRoom;
}

struct Room changeRoomNorth(struct Room currentRoom) {
    if (currentRoom.northNum == -1) {
        printf("You tried going North, but ran into a wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {  //edit it later to include size of Room
            if (rooms[i].roomNum == currentRoom.northNum) {
                currentRoom = rooms[i];
            }
        }
    }
    return currentRoom;
}

struct Room changeRoomSouth(struct Room currentRoom) {
    if (currentRoom.southNum == -1) {
        printf("You tried going South, but ran into a wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {  //edit it later to include size of Room
            if (rooms[i].roomNum == currentRoom.southNum) {
                currentRoom = rooms[i];
            }
        }
    }
    return currentRoom;
}

struct Room checkCreatureEmotion(struct Room currentRoom, bool roomStatus) {
    for (int i = 0; i < 10; i++) {
        if (currentRoom.creatures[i].type == 1 && roomStatus == false) { //false == dirtier, //1 - animal , 2 = npc // animal - clean, npc - dirty
            decreaseRespect();
            if (currentRoom.state == 2) {
                currentRoom = leaveRoom(currentRoom, currentRoom.creatures[i].creatureNum);
            }
        } else if (currentRoom.creatures[i].type == 1 && roomStatus == true) {
            increaseRespect();
        } else if (currentRoom.creatures[i].type == 2 && roomStatus == false) {
            increaseRespect();
        } else if (currentRoom.creatures[i].type == 2 && roomStatus == true) {
            decreaseRespect();
            if (currentRoom.state == 0) {
                currentRoom = leaveRoom(currentRoom, currentRoom.creatures[i].creatureNum);
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
                        printf("%d did not like the state of the room and left to %d\n", currentRoom.creatures[i].creatureNum, currentRoom.eastNum);
                        //Now remove it from old room [bit wonky]
                        currentRoom.creatures[i].type = 0;
                        currentRoom.creatures[i].creatureNum = -1;       //this might be wonky
                        currentRoom.creatures[i].location = -1;
                        isExecuted = true;
                        updateRoomNeighbors(currentRoom);
                    }
                }
            }
        }
    }
    if (currentRoom.westNum != -1) {
        for (int i = 0; i < 10; i++) {
            if (currentRoom.creatures[i].creatureNum == creatureNum) {
                for (int j = 0; j < 10; j++) {
                    if (currentRoom.west->creatures[j].type == 0 && isExecuted == false) {        //room is free
                        currentRoom.west->creatures[j] = currentRoom.creatures[i];
                        currentRoom.west->creatures[j].location = currentRoom.roomNum;
                        printf("%d did not like the state of the room and left to %d\n", currentRoom.creatures[i].creatureNum, currentRoom.westNum);
                        //Now remove it from old room [bit wonky]
                        currentRoom.creatures[i].type = 0;
                        currentRoom.creatures[i].creatureNum = -1;       //this might be wonky
                        currentRoom.creatures[i].location = -1;
                        isExecuted = true;
                        updateRoomNeighbors(currentRoom);
                    }
                }
            }
        }
    }
    if (currentRoom.northNum != -1) {
        for (int i = 0; i < 10; i++) {
            if (currentRoom.creatures[i].creatureNum == creatureNum) {
                for (int j = 0; j < 10; j++) {
                    if (currentRoom.north->creatures[j].type == 0 && isExecuted == false) {        //room is free
                        currentRoom.north->creatures[j] = currentRoom.creatures[i];
                        currentRoom.north->creatures[j].location = currentRoom.roomNum;
                        printf("%d did not like the state of the room and left to %d\n", currentRoom.creatures[i].creatureNum, currentRoom.northNum);
                        //Now remove it from old room [bit wonky]
                        currentRoom.creatures[i].type = 0;
                        currentRoom.creatures[i].creatureNum = -1;       //this might be wonky
                        currentRoom.creatures[i].location = -1;
                        isExecuted = true;
                        updateRoomNeighbors(currentRoom);
                    }
                }
            }
        }
    }
    if (currentRoom.southNum != -1) {
        for (int i = 0; i < 10; i++) {
            if (currentRoom.creatures[i].creatureNum == creatureNum) {
                for (int j = 0; j < 10; j++) {
                    if (currentRoom.south->creatures[j].type == 0 && isExecuted == false) {        //room is free
                        currentRoom.south->creatures[j] = currentRoom.creatures[i];
                        currentRoom.south->creatures[j].location = currentRoom.roomNum;
                        printf("%d did not like the state of the room and left to %d\n", currentRoom.creatures[i].creatureNum, currentRoom.southNum);
                        //Now remove it from old room [bit wonky]
                        currentRoom.creatures[i].type = 0;
                        currentRoom.creatures[i].creatureNum = -1;       //this might be wonky
                        currentRoom.creatures[i].location = -1;
                        isExecuted = true;
                        updateRoomNeighbors(currentRoom);
                    }
                }
            }
        }
    }
//    if (currentRoom.northNum == -1 && currentRoom.southNum == -1 && currentRoom.eastNum == -1 && currentRoom.westNum == -1) {
//        for (int i = 0; i < 10; i++) {
//            if (currentRoom.creatures[i].creatureNum == creatureNum) {
//                for (int j = 0; j < 10; j++) {
//                    printf("%d is stuck in the house without available rooms. They decide to leave.",
//                           currentRoom.creatures[creatureNum].creatureNum);
//                }
//            }
//        }
//        //leave the house
//    }
    return currentRoom;
}

void updateRoomNeighbors(struct Room currentRoom) {
    for (int i = 0; i < 10; i++) { //maybe use a different index for i < 100 lol sizeof(array)/sizeof(array[0]);
        if (rooms[i].roomNum == currentRoom.roomNum) {
            rooms[i] = currentRoom;
        }
    }

}

struct Room creatureClean(struct Room currentRoom, int creatureNum, bool roomStatus) {
    for (int i = 0; i < 10; i++) {
        if (currentRoom.creatures[i].creatureNum == creatureNum) {
            if (currentRoom.state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
                currentRoom.state = 1;
                roomStatus = true;
                updateRoomState(currentRoom);
                if (currentRoom.creatures[i].type == 2) {
                    higherDecreaseRespect();
                    if (currentRoom.state == 0) {
                        currentRoom = leaveRoom(currentRoom, creatureNum);
                    }
                }
            } else if (currentRoom.state == 1) { /* if it's half-dirty, make it clean*/
                currentRoom.state = 0;
                roomStatus = true;
                updateRoomState(currentRoom);
                if (currentRoom.creatures[i].type == 2) {
                    higherDecreaseRespect();
                    if (currentRoom.state == 0) {
                        currentRoom = leaveRoom(currentRoom, creatureNum);
                    }
                }
            } else {
                printf("Your room is already clean!\n");
            }
            return currentRoom;
        }
    }
}

struct Room creatureDirty(struct Room currentRoom, int creatureNum, bool roomStatus) {
    for (int i = 0; i < 10; i++) {
        if (currentRoom.state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
            printf("Your room is already dirty!\n");
        } else if (currentRoom.state == 1) { /* if it's half-dirty, make it dirty*/
            currentRoom.state = 2;
            roomStatus = false;
            updateRoomState(currentRoom);
            if (currentRoom.creatures[i].type == 1) {
                higherDecreaseRespect();
                if (currentRoom.state == 2) {
                    currentRoom = leaveRoom(currentRoom, creatureNum);
                }
            }
        } else {
            currentRoom.state = 1;
            roomStatus = false;
            updateRoomState(currentRoom);
            if (currentRoom.creatures[i].type == 1) {
                higherDecreaseRespect();
                if (currentRoom.state == 2) {
                    currentRoom = leaveRoom(currentRoom, creatureNum);
                }
            }
        }
        return currentRoom;
    }
}

    struct Room creatureChangeRoomEast(struct Room currentRoom, int creatureNum) {
        bool isExecuted = false;
        if(currentRoom.eastNum != -1) {
            for (int i = 0; i < 10; i++) {
                if (currentRoom.creatures[i].creatureNum == creatureNum) {
                    for (int j = 0; j < 10; j++) {
                        if (currentRoom.east->creatures[j].type == 0 && isExecuted == false) {
                            currentRoom.east->creatures[j] = currentRoom.creatures[i];
                            printf("The PC bullied %d to the east room.\n", creatureNum);
                            //remove creature from current room
                            currentRoom.creatures[i].type = 0;
                            currentRoom.creatures[i].location = -1;
                            currentRoom.creatures[i].creatureNum = -1;
                            isExecuted = true;
                        }
                    }
                }
            }
        }
        return currentRoom;
    }
struct Room creatureChangeRoomWest(struct Room currentRoom, int creatureNum) {
    bool isExecuted = false;
    if(currentRoom.westNum != -1) {
        for (int i = 0; i < 10; i++) {
            if (currentRoom.creatures[i].creatureNum == creatureNum) {
                for (int j = 0; j < 10; j++) {
                    if (currentRoom.west->creatures[j].type == 0 && isExecuted == false) {
                        currentRoom.west->creatures[j] = currentRoom.creatures[i];
                        printf("The PC bullied %d to the west room.\n", creatureNum);
                        //remove creature from current room
                        currentRoom.creatures[i].type = 0;
                        currentRoom.creatures[i].location = -1;
                        currentRoom.creatures[i].creatureNum = -1;
                        isExecuted = true;
                    }
                }
            }
        }
    }
    return currentRoom;
}
struct Room creatureChangeRoomNorth(struct Room currentRoom, int creatureNum) {
    bool isExecuted = false;
    if(currentRoom.northNum != -1) {
        for (int i = 0; i < 10; i++) {
            if (currentRoom.creatures[i].creatureNum == creatureNum) {
                for (int j = 0; j < 10; j++) {
                    if (currentRoom.north->creatures[j].type == 0 && isExecuted == false) {
                        currentRoom.north->creatures[j] = currentRoom.creatures[i];
                        printf("The PC bullied %d to the north room.\n", creatureNum);
                        //remove creature from current room
                        currentRoom.creatures[i].type = 0;
                        currentRoom.creatures[i].location = -1;
                        currentRoom.creatures[i].creatureNum = -1;
                        isExecuted = true;
                    }
                }
            }
        }
    }
    return currentRoom;
}
struct Room creatureChangeRoomSouth(struct Room currentRoom, int creatureNum) {
    bool isExecuted = false;
    if(currentRoom.southNum != -1) {
        for (int i = 0; i < 10; i++) {
            if (currentRoom.creatures[i].creatureNum == creatureNum) {
                for (int j = 0; j < 10; j++) {
                    if (currentRoom.south->creatures[j].type == 0 && isExecuted == false) {
                        currentRoom.south->creatures[j] = currentRoom.creatures[i];
                        printf("The PC bullied %d to the west room.\n", creatureNum);
                        //remove creature from current room
                        currentRoom.creatures[i].type = 0;
                        currentRoom.creatures[i].location = -1;
                        currentRoom.creatures[i].creatureNum = -1;
                        isExecuted = true;
                    }
                }
            }
        }
    }
    return currentRoom;
}


void decreaseRespect() {
    respect--;
}

void higherDecreaseRespect() {
    respect-=3;
}
void increaseRespect() {
    respect++;
}
void higherincreaseRespect() {
    respect+=3;
}


struct Room growl(struct Room currentRoom) {

}
struct Room grumble(struct Room currentRoom) {

}
struct Room  lick(struct Room currentRoom) {

}
struct Room  smile(struct Room currentRoom) {

}





//tests

//void tLook() {
//    printf("Room number: %d | Room state: %d | ", rooms[0].roomNum, rooms[0].state); /* Print out the room cleanliness */
//    //Print out the neighbors
//    if (rooms[0].north != NULL) {
//        printf("%d to the north | ", rooms[0].northNum);
//    }
//    if (rooms[0].south != NULL) {
//        printf("%d to the south | ", rooms[0].southNum);
//    }
//    if (rooms[0].east != NULL) {
//        printf("%d to the east | ", rooms[0].eastNum);
//    }
//    if (rooms[0].west != NULL) {
//        printf("%d to the west | ", rooms[0].westNum);
//    }
//}
