//
// Created by Saurav Lamichhane on 9/11/23; I'M USING 3 FOR PC BECAUSE 0 IS THE VALUES PRESENT IN UNINITIALIZED ARRAYS
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
};

// Global variables
int respect = 40;
struct Room *rooms = NULL;
struct Creature *creatures = NULL;

//functions *add later*
void createRoom(int roomNum);
void assignRoom(int numOfRooms);
void assignCreatures(int numOfCreatures, int numOfRooms);
void look(struct Room *currentRoom);
void clean(struct Room *currentRoom, bool roomStatus);
void dirty(struct Room *currentRoom, bool roomStatus);
void updateRoomState(struct Room *currentRoom);
void changeRoomEast(struct Room *currentRoom);
void changeRoomWest(struct Room *currentRoom);
void changeRoomNorth(struct Room *currentRoom);
void changeRoomSouth(struct Room *currentRoom);
//void updateCurrentRoom(struct Room *currentRoom, int roomNum);





//void checkForNull();

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
    currentRoom = malloc(sizeof (struct Creature));
    for (int i = 0; i < numOfRooms; i++) {
        for (int j = 0; j < 10; j++) {
            if (rooms[i].creatures[j].type == 3) {      // 3 = PC
                currentRoom = rooms[i];
            }
        }
    }

    //test
    for (int i = 0; i < numOfRooms; i++) {
        printf("%d %d %d %d %d", rooms[i].roomNum, rooms[i].northNum, rooms[i].southNum, rooms[i].eastNum, rooms[i].westNum);
    }

    char input[20];
    char command[5];        // used in creature command to clean/dirty ; check if its clean or dirty
    int creatureType;       // used in creature command to clean/dirty

    while (respect > 0 || respect < 80) {
        //Set the input
        printf("Enter a command: ");
        scanf("%s", input);

        if (strcmp(input, "look") == 0) {
            look(currentRoom);
        }
        //test code
        else if (strcmp(input, "tLook") == 0) {
            for (int i = 0; i < numOfRooms; i++) {
                printf("%d - ", rooms[i].roomNum);
                printf("%d\n", rooms[i].state);
            }
        }
        //end of test
        else if (strcmp(input, "clean") == 0) {
            clean(currentRoom, roomStatus);
        }
        else if (strcmp(input, "dirty") == 0) {
            dirty(currentRoom, roomStatus);
        }
        else if (strcmp(input, "east") == 0) {
            changeRoomEast(currentRoom);
        }

        else if (strcmp(input, "west") == 0) {
            changeRoomWest(currentRoom);
        }

        else if (strcmp(input, "north") == 0) {
            changeRoomNorth(currentRoom);
        }

        else if (strcmp(input, "south") == 0) {
            changeRoomSouth(currentRoom);
        }
        else if (strcmp(input, "exit") == 0) {
            printf("Goodbye!");
            break;
        }
    }
        //free memory
    free(rooms);

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
    for (int i = 0; i < numOfRooms; i++) {
        int index = 0;
        for (int j = 0; j < numOfCreatures; j++) {
            if (creatures[j].location == rooms[i].roomNum) {
                rooms[i].creatures[index] = creatures[j];
                rooms[i].creatures[index].creatureNum = index;
                index++;
            }
        }
    }
}

void look(struct Room *currentRoom) {
    printf("Room number: %d | Room state: %d | ", currentRoom->roomNum, currentRoom->state); /* Print out the room cleanliness */
    //Print out the neighbors
    if (currentRoom->northNum != -1) {
        printf("%d to the north | ", currentRoom->northNum);
    }
    if (currentRoom->southNum != -1) {
        printf("%d to the south | ", currentRoom->southNum);
    }
    if (currentRoom->eastNum != -1) {
        printf("%d to the east | ", currentRoom->eastNum);
    }
    if (currentRoom->westNum != -1) {
        printf("%d to the west | ", currentRoom->westNum);
    }

    //Print out the creatures
    printf("contains:\n");  /*work on this more, to include all the creatures in the room*/
    for (int i = 0; i < 10; i++) {
        if (currentRoom->creatures[i].type == 3) {
            printf ("PC\n");
        }
        else if (currentRoom->creatures[i].type == 2) {
            printf ("human %d\n", currentRoom->creatures[i].creatureNum);
        }
        else if (currentRoom->creatures[i].type == 1) {
            printf ("animal %d\n", currentRoom->creatures[i].creatureNum);
        }
    }

}

void clean(struct Room *currentRoom, bool roomStatus) {
    if (currentRoom->state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
        currentRoom->state = 1;
        roomStatus = true;
        // checkCreatureEmotion();
        updateRoomState(currentRoom);
    } else if (currentRoom->state == 1) { /* if it's half-dirty, make it clean*/
        currentRoom->state = 0;
        roomStatus = true;
        // checkCreatureEmotion();
        updateRoomState(currentRoom);
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
        updateRoomState(currentRoom);
    } else {
        currentRoom->state = 1;
        roomStatus = false;
        // checkCreatureEmotion();
        updateRoomState(currentRoom);
    }
}


void updateRoomState(struct Room *currentRoom) {
    for (int i = 0; i < 10; i++) { //maybe use a different index for i < 100 lol sizeof(array)/sizeof(array[0]);
        if (rooms[i].roomNum == currentRoom->roomNum) {
            rooms[i].state = currentRoom->state;
        }
    }
}

void changeRoomEast(struct Room *currentRoom) {     //remember to update the creatures
    if (currentRoom->eastNum == -1) {
        printf("You tried going East, but ran into a wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {  //edit it later to include size of Room
            if (rooms[i].roomNum == currentRoom->eastNum) {
                *currentRoom = rooms[i];
            }
        }
    }
}
void changeRoomWest(struct Room *currentRoom) {
    if (currentRoom->westNum == -1) {
        printf("You tried going West, but ran into a wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {  //edit it later to include size of Room
            if (rooms[i].roomNum == currentRoom->westNum) {
                *currentRoom = rooms[i];
            }
        }
    }
}
void changeRoomNorth(struct Room *currentRoom) {
    if (currentRoom->northNum == -1) {
        printf("You tried going North, but ran into a wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {  //edit it later to include size of Room
            if (rooms[i].roomNum == currentRoom->northNum) {
                *currentRoom = rooms[i];
            }
        }
    }
}
void changeRoomSouth(struct Room *currentRoom) {
    if (currentRoom->southNum == -1) {
        printf("You tried going South, but ran into a wall!\n");
    } else {
        for (int i = 0; i < 10; i++) {  //edit it later to include size of Room
            if (rooms[i].roomNum == currentRoom->southNum) {
                *currentRoom = rooms[i];
            }
        }
    }
}

//void updateCurrentRoom(struct Room *currentRoom, int roomNum) {
//    *currentRoom = rooms[roomNum];
//}
















//void checkForNull() {
//
//
//}





























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
