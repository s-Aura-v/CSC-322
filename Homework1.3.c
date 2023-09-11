#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*Initial Setup*/

struct Creature {
    int type;
    int location;
};

struct Room {
    int roomNum; //maybe this might work
    int state;
    int north;
    int south;
    int east;
    int west;
    struct Creature roomCreatures[10];
};

// Global variables
int respect = 40;
struct Room *rooms = NULL;
struct Creature *creatures = NULL;

///* functions to make the program work*/
void look(struct Room *currentRoom);
void clean(struct Room *currentRoom, bool roomStatus);
void dirty(struct Room *currentRoom, bool roomStatus);
void updateRoomPointer(struct Room *currentRoom);

//work in progress
void changeRoomEast(struct Room *currentRoom);
void changeRoomWest(struct Room *currentRoom);
void changeRoomNorth(struct Room *currentRoom);
void changeRoomSouth(struct Room *currentRoom);

//work work in progress
 void decreaseRespect();
 void higherDecreaseRespect();
 void increaseRespect();
 void higherincreaseRespect();

// void growl();
// void grumble();
// void lick();
// void smile();



int main() {
    // Setup (Adding User Input)
    int numOfRooms;
    int numOfCreatures;
    struct Room currentRoom;
    bool roomStatus;

    printf("# of rooms: ");
    scanf("%d", &numOfRooms);

    rooms = (struct Room *) malloc(sizeof(struct Room) * numOfRooms);

    for (int i = 0; i < numOfRooms; i++) {
        printf("rooms: ");
        scanf("%d %d %d %d %d", &rooms[i].state, &rooms[i].north, &rooms[i].south, &rooms[i].east, &rooms[i].west);
    }

    printf("# of creatures: ");
    scanf("%d", &numOfCreatures);

    creatures = (struct Creature *) malloc(sizeof(struct Creature) * numOfCreatures);

    for (int i = 0; i < numOfCreatures; i++) {
        printf("creatures: ");
        scanf("%d %d", &creatures[i].type, &creatures[i].location);
    }

    // Add a creature for each location
    int roomIndex;
    for (int i = 0; i < numOfRooms; i++) {
        roomIndex = 0;
        for (int j = 0; j < 10; j++) {
            if (creatures[j].location == i) {
                rooms[i].roomCreatures[roomIndex] = creatures[j];
                roomIndex++;
            }
        }
    }

    //Current room
    for (int i = 0; i < numOfRooms; i++) {
        rooms[i].roomNum = i;           //?
        for (int j = 0; j < 10; j++) {
            if (rooms[i].roomCreatures[j].type == 0) {
                //set current room equal to that room
                currentRoom.roomNum = i;
                currentRoom.state = rooms[i].state;
                currentRoom.north = rooms[i].north;
                currentRoom.south = rooms[i].south;
                currentRoom.east = rooms[i].east;
                currentRoom.west = rooms[i].west;
                for (int k = 0; k < 10; k++) {
                    currentRoom.roomCreatures[k] = rooms[i].roomCreatures[k];
                }
            }
        }
    }

    //Gameplay

    char input[20];
    char command[5];        // used in creature command to clean/dirty ; check if its clean or dirty
    int creatureType;       // used in creature command to clean/dirty

    while (respect > 0) {
        //Set the input
        printf("Enter a command: ");
        scanf("%s", input);

        if (strcmp(input, "look") == 0) {
            look(&currentRoom);
        }

        //test code
        else if (strcmp(input, "tLook") == 0) {
            for (int i = 0; i < (10); i++) {
                printf("%d - %d\n", rooms[i].roomNum, rooms[i].state);
            }
        }
        else if (strcmp(input, "resp") == 0) {
            increaseRespect();
            printf("%d", respect);
            decreaseRespect();
            printf("%d", respect);
            higherDecreaseRespect();
            printf("%d", respect);
            higherincreaseRespect();
            printf("%d", respect);
        }
        //
        else if (strcmp(input, "clean") == 0) {
            clean(&currentRoom, roomStatus);
        }
        else if (strcmp(input, "dirty") == 0) {
            dirty(&currentRoom, roomStatus);
        }
        else if (strcmp(input, "exit") == 0) {
            printf("Goodbye!");
            break;
        }

//        else if (strcmp(input, "1:clean") == 0) {
//            cClean(&currentRoom, roomStatus);
//        }
//        else if (strcmp(input, "1:dirty") == 0) {
//
//        }
//        else if (strcmp(input, "2:clean") == 0) {
//
//        }
//        else if (strcmp(input, "2:dirty") == 0) {
//
//        }
//
//        if (sscanf(input, "%d:%5s", &creatureType, &command) == 0) {
//            if (strcmp(command, "clean") == 0) {
//            }
//        }
//

            else if (strcmp(input, "east") == 0) {
            changeRoomEast(&currentRoom);
        }

        else if (strcmp(input, "west") == 0) {
            changeRoomWest(&currentRoom);
        }

        else if (strcmp(input, "north") == 0) {
            changeRoomNorth(&currentRoom);
        }

        else if (strcmp(input, "south") == 0) {
            changeRoomSouth(&currentRoom);
        }
    }


    //Prevent memory leaks
    free(rooms);
    free(creatures);

    printf("You lost! You ran out of respect");
    return 0;
}
//
void look(struct Room *currentRoom) {

    printf("Room state: %d | ", currentRoom->state); /* Print out the room cleanliness */

    /* Check neighbors in the room*/
    printf("neighbors ");
    if (currentRoom->north != -1) {
        printf("%d to the north | ", currentRoom->north);
    }
    if (currentRoom->east != -1) {
        printf("%d to the east | ", currentRoom->east);
    }
    if (currentRoom->south != -1) {
        printf("%d to the south | ", currentRoom->south);
    }
    if (currentRoom->west != -1) {
        printf("%d to the west | ", currentRoom->west);
    }

    /*Check creatures*/
    printf("contains:\nPC\n");  /*work on this more, to include all the creatures in the room*/
    for (int i = 0; i < 10; i++) {
        if (currentRoom->roomCreatures[i].type != 0) {
            printf("%d\n", currentRoom->roomCreatures[i].type);
        }
    }
}

void clean(struct Room *currentRoom, bool roomStatus) {
    if (currentRoom->state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
        currentRoom->state = 1;
        roomStatus = true;
        // checkCreatureEmotion();
         updateRoomPointer(currentRoom);
    } else if (currentRoom->state == 1) { /* if it's half-dirty, make it clean*/
        currentRoom->state = 0;
        roomStatus = true;
        // checkCreatureEmotion();
         updateRoomPointer(currentRoom);
    } else {
        printf("Your room is already clean!");
    }
}

void dirty(struct Room *currentRoom, bool roomStatus) {
    if (currentRoom->state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
        printf("Your room is already dirty!");
    } else if (currentRoom->state == 1) { /* if it's half-dirty, make it clean*/
        currentRoom->state = 2;
        roomStatus = false;
        // checkCreatureEmotion();
         updateRoomPointer(currentRoom);
    } else {
        currentRoom->state = 1;
        roomStatus = false;
        // checkCreatureEmotion();
         updateRoomPointer(currentRoom);
    }
}

//void cClean(struct Room *currentRoom, bool roomStatus) {
//    if (currentRoom->state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
//        currentRoom->state = 1;
//        roomStatus = true;
//        // checkCreatureEmotion();
//        updateRoomPointer(currentRoom);
//    } else if (currentRoom->state == 1) { /* if it's half-dirty, make it clean*/
//        currentRoom->state = 0;
//        roomStatus = true;
//        // checkCreatureEmotion();
//        updateRoomPointer(currentRoom);
//    } else {
//        printf("Your room is already clean!");
//    }
//
//    printf("%d licks your face")
//}



void updateRoomPointer(struct Room *currentRoom) {
    for (int i = 0; i < (10); i++) { //maybe use a different index for i < 100 lol sizeof(array)/sizeof(array[0]);
        if (rooms[i].roomNum == currentRoom->roomNum) {
            rooms[i].state = currentRoom->state;
            rooms[i].north = currentRoom->north;
            rooms[i].south = currentRoom->south;
            rooms[i].east = currentRoom->east;
            rooms[i].west = currentRoom->west;
            for (int k = 0; k < 10; k++) {
                rooms[i].roomCreatures[k] = currentRoom->roomCreatures[k];
            }
        }
    }
}

void changeRoomEast(struct Room *currentRoom) {
    if (currentRoom->east == -1) {
        printf("You tried going east, but ended up running into the wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {        // change the i < to the size of the array
            if (currentRoom->east == rooms[i].state) {
                *currentRoom = rooms[i];
            }
        }
    }
}

void changeRoomWest(struct Room *currentRoom) {
    if (currentRoom->west == -1) {
        printf("You tried going west, but ended up running into the wall!\n");
    } else {
        for (int i = 0; i <  10; i++) {        // change the i < to the size of the array
            if (currentRoom->west == rooms[i].state) {//edit it later; rn i'm checking it based on state number
                *currentRoom = rooms[i];
            }
        }
    }
}
void changeRoomNorth(struct Room *currentRoom) {
    if (currentRoom->north == -1) {
        printf("You tried going east, but ended up running into the wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {        // change the i < to the size of the array
            if(currentRoom->north == rooms[i].state) {                   //edit it later; rn i'm checking it based on state number
                *currentRoom = rooms[i];
            }
        }
    }
}
void changeRoomSouth(struct Room *currentRoom) {
    if (currentRoom->south == -1) {
        printf("You tried going east, but ended up running into the wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {        // change the i < to the size of the array
            *currentRoom = rooms[i];
        }
    }
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

