#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*initial setup*/
struct Creature {
    int type;
    int location;
};
struct Room{
    int cleanliness;
    int north;
    int east;
    int south;
    int west;
    int creatureAmount;
    struct Creature creatures[10];
};
bool roomStatus;  //true - room got cleaner // false - room got dirtier
struct Room actualRoom; // the room that you are currently in

/* functions to make the program work*/
void look(struct Room roomlayout);
void clean(struct Room currentRoom);
void dirty(struct Room currentRoom);
void checkCreatureEmotion(struct Room currentRoom);
void changeRoomEast(struct Room currentRoom, struct Room roomlayout[]);
void changeRoomWest(struct Room currentRoom);
void changeRoomNorth(struct Room currentRoom);
void changeRoomSouth(struct Room currentRoom);


int main() {
    int numOfRooms; // still have to initalize these two values
    int numOfCreatures;
    struct Room currentRoom;
    
    printf("Enter the number of rooms: ");
    scanf("%d", &numOfRooms); /* n */
    struct Room roomlayout[numOfRooms];

    /*Enter the room data*/
    for (int i = 0; i < numOfRooms; i++) {
        printf("Enter the state of the room and its neighbors: ");
        scanf("%d %d %d %d %d", &roomlayout[i].cleanliness, &roomlayout[i].north, &roomlayout[i].south, &roomlayout[i].east, &roomlayout[i].west);
    }
    // Set current room to the first inputted room
    currentRoom.cleanliness = roomlayout[0].cleanliness;
    currentRoom.creatureAmount = roomlayout[0].creatureAmount;
    for (int i = 0; i < currentRoom.creatureAmount; i++) {
        currentRoom.creatures[i] = roomlayout[0].creatures[i];
    }
    currentRoom.north = roomlayout[0].north;
    currentRoom.south = roomlayout[0].south;
    currentRoom.east = roomlayout[0].east;
    currentRoom.west = roomlayout[0].west;

     /*The number of animals*/
    printf("Enter the amount of creatures: ");
    scanf("%d", &numOfCreatures);

    /*The type of creature + location*/
    struct Creature creatures[numOfCreatures];
    for (int i = 0; i < numOfCreatures; i++) {
        printf("\nEnter the creatureType and location: ");
        scanf("%d %d", &creatures[i].type, &creatures[i].location);
    }

//i think this code is broken so look at it again
    for (int i = 0; i < numOfRooms; i++) {

        for (int j = 0; j < numOfCreatures; j++) {

            if (creatures[j].location == i) {

                roomlayout[i].creatures[i].location = creatures[j].location;
                roomlayout[i].creatures[i].type = creatures[j].type;

            }

        }
    }

    /*Reading Inputs*/

    char input[20];
    while(1) {
        printf("\nEnter a command: ");
        scanf("%s", input);

        /*switch to case statement at the end*/
        if (strcmp(input, "look") == 0) {
            look(currentRoom);
        }

        else if (strcmp(input, "clean") == 0) {
            clean(currentRoom);
        }

        else if (strcmp(input, "dirty") == 0) {
            dirty(currentRoom);
        }

        else if (strcmp(input, "east") == 0) {
            changeRoomEast(currentRoom, roomlayout);
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
    return 0;
}


void look(struct Room currentRoom) {

    printf("Room cleaniness: %d ", currentRoom.cleanliness); /* Print out the room cleanliness */

    /* Check neighbors in the room*/
    printf("neighbors ");
    if (currentRoom.north != -1) {
        printf("%d to the north ", currentRoom.north);
    } 
    if (currentRoom.east != -1) {
        printf("%d to the east ", currentRoom.east);
    }
    if (currentRoom.south != -1) {
        printf("%d to the south ", currentRoom.south);
    }
    if (currentRoom.west != -1) {
        printf("%d to the west ", currentRoom.west);
    }

    /*Check creatures*/
    printf(" contains:\n PC\n");  /*work on this more, to include all the creatures in the room*/
    for (int i = 0; i < currentRoom.creatureAmount; i++) {
        if (currentRoom.creatures->type == 1) {
            printf("%d 1\n", currentRoom.creatures->type);
        }

        if (currentRoom.creatures->type == 2) {
            printf("%d 2\n", currentRoom.creatures->type);
        }
    }
}

void clean(struct Room currentRoom) {
        if (currentRoom.cleanliness == 2) { /* if its dirty, make it half dirty, remember the respect system*/
           currentRoom.cleanliness = 1;
           roomStatus = true;
           checkCreatureEmotion(currentRoom);
        } else if (currentRoom.cleanliness == 1) { /* if it's half-dirty, make it clean*/
            currentRoom.cleanliness = 0;
            roomStatus = true;
            checkCreatureEmotion(currentRoom);
        } else { 
            printf("Your room is already clean!");
        }
    }

void dirty(struct Room currentRoom) {
    if (currentRoom.cleanliness == 2) { /* if its dirty, make it half dirty, remember the respect system*/
        printf("Your room is already dirty!");
    } else if (currentRoom.cleanliness == 1) { /* if it's half-dirty, make it dirty*/
        currentRoom.cleanliness = 2;
        roomStatus = false;
        checkCreatureEmotion(currentRoom);
    } else {                                   /*if it's clean, make it half-dirty*/
        currentRoom.cleanliness = 1;
        roomStatus = false;
        checkCreatureEmotion(currentRoom);

    }
}

// void checkCreatureEmotion(struct Room currentRoom) {

//     //animal - likes clean | stays in clean/half-dirty
//     //npc - likes dirty    | stays in half-dirty / dirty

//     // 0 - pc | 1 - animal | 2 - npc


//     //if creature type is an animal, and the room changes from clean to half dirty, then they growl and 
//     //                               if it is dirty, then they leave the room 

//     for (int i = 0; i < currentRoom.creatureAmount; i++) {

//         if((currentRoom.creatures.type == 1) && (roomStatus == false)) {

//             if (currentRoom.cleanliness == 2) {        //leave the room

//             }

//         } else if ((currentRoom->creatures->type == 1) && (roomStatus == true)) {

//         } else if ((currentRoom->creatures->type == 2) && (roomStatus == false)) {
  
//         }  else if ((currentRoom->creatures->type == 2) && (roomStatus == true)) {

//             if (currentRoom->cleanliness == 0) {        //leave the room

//             }
        
//         }
//     }
// }

/* I can probably combine all of these, but it's easier for me to do this for now*/

void changeRoomEast(struct Room currentRoom, struct Room roomlayout[]) {

    // if they say go east, check if east is there, if it is, go there
    if (currentRoom.east != -1) {

        for (int i = 0; i < sizeof(roomlayout)/sizeof(roomlayout[0]); i++) {
            if (roomlayout[i].west == currentRoom.cleanliness) {
                actualRoom.cleanliness = roomlayout[i].cleanliness;
                actualRoom.creatureAmount = roomlayout[i].creatureAmount;
                actualRoom.east = roomlayout[i].east;
                actualRoom.west = roomlayout[i].west;
                actualRoom.north = roomlayout[i].north;
                actualRoom.south = roomlayout[i].south;
            }
        }

        //how do I change the data to that of the east room
    } else {
        printf("You try to head East and end up running into the wall!");
    }
}


// void changeRoomWest(struct Room *currentRoom) {

//     // if they say go east, check if east is there, if it is, go there
//     if (currentRoom->west != -1) {


//         actualRoom->cleanliness = currentRoom;
//         actualRoom->creatureAmount = currentRoom;
//         actualRoom->east = currentRoom;
//         actualRoom->west = currentRoom;
//         actualRoom->north = currentRoom;
//         actualRoom->south = currentRoom;


//     } else {
//         printf("You try to head West and end up running into the wall!");
//     }
// }

// void changeRoomNorth(struct Room *currentRoom) {

//     // if they say go north, check if east is there, if it is, go there
//     if (currentRoom->north != -1) {
//         actualRoom->cleanliness = currentRoom;
//         actualRoom->creatureAmount = currentRoom;
//         actualRoom->east = currentRoom;
//         actualRoom->west = currentRoom;
//         actualRoom->north = currentRoom;
//         actualRoom->south = currentRoom;
//     } else {
//         printf("You try to head North and end up running into the wall!");
//     }
// }

// void changeRoomSouth(struct Room *currentRoom) {

//     // if they say go east, check if east is there, if it is, go there
//     if (currentRoom->south != -1) {
//         actualRoom->cleanliness = currentRoom;
//         actualRoom->creatureAmount = currentRoom;
//         actualRoom->east = currentRoom;
//         actualRoom->west = currentRoom;
//         actualRoom->north = currentRoom;
//         actualRoom->south = currentRoom;

//     } else {
//         printf("You try to head South and end up running into the wall!");
//     }
// }
// /* End of Change Room*/

