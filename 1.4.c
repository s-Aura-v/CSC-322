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

//void checkForNull();

int main() {
    // Setup (Adding User Input)
    int numOfRooms;
    int numOfCreatures;

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
    struct Room *currentRoom;
    for (int i = 0; i < numOfRooms; i++) {
        for (int j = 0; j < 10; j++) {
            if (rooms[i].creatures[j].type == 3) {      // 3 = PC
                currentRoom = &rooms[i];
            }
        }
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
        } else if (strcmp(input, "exit") == 0) {
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
//                rooms[i].north = malloc(sizeof(struct Room) * numOfRooms);
                rooms[i].north = &rooms[j];
            }
            if (rooms[i].southNum == rooms[j].roomNum) {
//                rooms[i].south = malloc(sizeof(struct Room) * numOfRooms);
                rooms[i].south = &rooms[j];
            }
            if (rooms[i].eastNum == rooms[j].roomNum) {
//                rooms[i].east = malloc(sizeof(struct Room) * numOfRooms);
                rooms[i].east = &rooms[j];
            }
            if (rooms[i].westNum == rooms[j].roomNum) {
//                rooms[i].west = malloc(sizeof(struct Room) * numOfRooms);
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
    if (currentRoom->north != NULL) {
        printf("%d to the north | ", currentRoom->northNum);
    }
    if (currentRoom->south != NULL) {
        printf("%d to the south | ", currentRoom->southNum);
    }
    if (currentRoom->east != NULL) {
        printf("%d to the east | ", currentRoom->eastNum);
    }
    if (currentRoom->west != NULL) {
        printf("%d to the west | ", currentRoom->westNum);
    }
}

//void checkForNull() {
//
//
//}
