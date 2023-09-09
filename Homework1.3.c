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
void look(struct Room currentRoom);
void clean();
//void dirty();
//void changeRoomEast();
//void changeRoomWest();
//void changeRoomNorth();
//void changeRoomSouth();


int main() {
    // Setup (Adding User Input)
    int numOfRooms;
    int numOfCreatures;
    struct Room currentRoom;

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
        for (int j = 0; j < 10; j++) {
            if (rooms[i].roomCreatures[j].type == 0) {
                //set current room equal to that room
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
    while (1) {
        //Set the input
        printf("\nEnter a command: ");
        scanf("%s", input);

        if (strcmp(input, "look") == 0) {
            look(currentRoom);
        }
        else if (strcmp(input, "clean") == 0) {
            clean();
        }
        else if (strcmp(input, "exit") == 0) {
            printf("Goodbye!");
            break;
        }
    }


    //Prevent memory leaks
    free(rooms);
    free(creatures);



    //Gameplay

//    char input[20];
//   while(1) {
//        printf("\nEnter a command: ");
//        scanf("%s", input);
//
//        /*switch to case statement at the end*/
//        if (strcmp(input, "look") == 0) {
//            look();
//        }
//
//        else if (strcmp(input, "clean") == 0) {
//            clean();
//        }
//
//        else if (strcmp(input, "dirty") == 0) {
//            dirty();
//        }
//
//        else if (strcmp(input, "east") == 0) {
//            changeRoomEast();
//        }
//
//        else if (strcmp(input, "west") == 0) {
//            changeRoomWest();
//        }
//
//        else if (strcmp(input, "north") == 0) {
//            changeRoomNorth();
//        }
//
//        else if (strcmp(input, "south") == 0) {
//            changeRoomSouth();
//        }
//
//        else if (strcmp(input, "exit") == 0) {
//            printf("Goodbye!");
//            break;
//        }
//    }
    return 0;
}
//
void look(struct Room currentRoom) {

    printf("Room cleaniness: %d | ", currentRoom.state); /* Print out the room cleanliness */

    /* Check neighbors in the room*/
    printf("neighbors ");
    if (currentRoom.north != -1) {
        printf("%d to the north | ", currentRoom.north);
    }
    if (currentRoom.east != -1) {
        printf("%d to the east | ", currentRoom.east);
    }
    if (currentRoom.south != -1) {
        printf("%d to the south | ", currentRoom.south);
    }
    if (currentRoom.west != -1) {
        printf("%d to the west | ", currentRoom.west);
    }

    /*Check creatures*/
    printf("contains:\nPC\n");  /*work on this more, to include all the creatures in the room*/
    for (int i = 0; i < 10; i++) {
        if (currentRoom.roomCreatures[i].type != 0) {
            printf("%d\n", currentRoom.roomCreatures[i].type);
        }
    }
}

void clean() {

}

//void dirty();
//void changeRoomEast();
//void changeRoomWest();
//void changeRoomNorth();
//void changeRoomSouth();
