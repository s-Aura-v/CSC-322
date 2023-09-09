#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*Initial Setup*/

// Define creature structure
struct Creature {
    int type;
    int location;
};

// Define Room
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
//void look();
//void clean();
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
        printf("%d %d", creatures[i].type, creatures[i].location);
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

    // test
    for (int i = 0; i < numOfRooms; i++) {
        printf(" wallahi - %d", rooms[i].state);
        for (int j = 0; j < 10; j++) {
            printf("%d - %d\n", rooms[i].roomCreatures[j].type, rooms[i].roomCreatures[j].location);
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
//void look();
//void clean();
//void dirty();
//void changeRoomEast();
//void changeRoomWest();
//void changeRoomNorth();
//void changeRoomSouth();
