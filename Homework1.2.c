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
void look(struct Room actualRoom);
void clean();
void dirty();
void checkCreatureEmotion();
void changeRoomEast(struct Room roomlayout[], int numOfRooms);
void changeRoomWest(struct Room roomlayout[], int numOfRooms);
void changeRoomNorth(struct Room roomlayout[], int numOfRooms);
void changeRoomSouth(struct Room roomlayout[], int numOfRooms);


int main() {
    int numOfRooms; // still have to initalize these two values
    int numOfCreatures;
    
    printf("Enter the number of rooms: ");
    scanf("%d", &numOfRooms); /* n */
    struct Room roomlayout[numOfRooms];

    /*Enter the room data*/
    for (int i = 0; i < numOfRooms; i++) {
        printf("Enter the state of the room and its neighbors: ");
        scanf("%d %d %d %d %d", &roomlayout[i].cleanliness, &roomlayout[i].north, &roomlayout[i].south, &roomlayout[i].east, &roomlayout[i].west);
    }
    // Set current room to the first inputted room
    actualRoom.cleanliness = roomlayout[0].cleanliness;
    actualRoom.creatureAmount = roomlayout[0].creatureAmount;
    for (int i = 0; i < actualRoom.creatureAmount; i++) {
        actualRoom.creatures[i] = roomlayout[0].creatures[i];
    }
    actualRoom.north = roomlayout[0].north;
    actualRoom.south = roomlayout[0].south;
    actualRoom.east = roomlayout[0].east;
    actualRoom.west = roomlayout[0].west;

     /*The number of animals*/
    printf("Enter the amount of creatures: ");
    scanf("%d", &numOfCreatures);

    /*The type of creature + location*/
    struct Creature creatures[numOfCreatures];
    for (int i = 0; i < numOfCreatures; i++) {
        printf("Enter the creatureType and location: ");
        scanf("%d %d", &creatures[i].type, &creatures[i].location);
    }

//i think this code is broken so look at it again
    for (int i = 0; i < numOfRooms; i++) {
        int nextCreatureIndex = 0;

        for (int j = 0; j < numOfCreatures; j++) {
            if (creatures[j].location == i) {
                roomlayout[i].creatures[nextCreatureIndex].location = creatures[j].location;
                roomlayout[i].creatures[nextCreatureIndex].type = creatures[j].type;
                nextCreatureIndex++;
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
            look(actualRoom);
        }

        else if (strcmp(input, "clean") == 0) {
            clean();
        }

        else if (strcmp(input, "dirty") == 0) {
            dirty();
        }

        else if (strcmp(input, "east") == 0) {
            changeRoomEast(roomlayout, numOfRooms); //temporarily using roomNumber while i test the code
        }

        else if (strcmp(input, "west") == 0) {
            changeRoomWest(roomlayout, numOfRooms);
        }

        else if (strcmp(input, "north") == 0) {
            changeRoomNorth(roomlayout, numOfRooms);
        }

        else if (strcmp(input, "south") == 0) {
            changeRoomSouth(roomlayout, numOfRooms);
        }

        else if (strcmp(input, "exit") == 0) {
            printf("Goodbye!");
            break;
        }
    }
    return 0;
}


void look(struct Room actualRoom) {

    printf("Room cleaniness: %d ", actualRoom.cleanliness); /* Print out the room cleanliness */

    /* Check neighbors in the room*/
    printf("neighbors ");   
    if (actualRoom.north != -1) {
        printf("%d to the north ", actualRoom.north);
    } 
    if (actualRoom.east != -1) {
        printf("%d to the east ", actualRoom.east);
    }
    if (actualRoom.south != -1) {
        printf("%d to the south ", actualRoom.south);
    }
    if (actualRoom.west != -1) {
        printf("%d to the west ", actualRoom.west);
    }

    /*Check creatures*/
    printf(" contains:\n PC\n");  /*work on this more, to include all the creatures in the room*/
    for (int i = 0; i < actualRoom.creatureAmount; i++) {
        if (actualRoom.creatures->type == 1) {
            printf("%d 1\n", actualRoom.creatures->type);
        }

        if (actualRoom.creatures->type == 2) {
            printf("%d 2\n", actualRoom.creatures->type);
        }
    }
}

void clean() {
        if (actualRoom.cleanliness == 2) { /* if its dirty, make it half dirty, remember the respect system*/
           actualRoom.cleanliness = 1;
           roomStatus = true;
        //    checkCreatureEmotion();
        } else if (actualRoom.cleanliness == 1) { /* if it's half-dirty, make it clean*/
            actualRoom.cleanliness = 0;
            roomStatus = true;
            // checkCreatureEmotion();
        } else { 
            printf("Your room is already clean!");
        }
    }

void dirty() {
    if (actualRoom.cleanliness == 2) { /* if its dirty, make it half dirty, remember the respect system*/
        printf("Your room is already dirty!");
    } else if (actualRoom.cleanliness == 1) { /* if it's half-dirty, make it dirty*/
        actualRoom.cleanliness = 2;
        roomStatus = false;
        // checkCreatureEmotion();
    } else {                                   /*if it's clean, make it half-dirty*/
        actualRoom.cleanliness = 1;
        roomStatus = false;
        // checkCreatureEmotion();

    }
}

// void checkCreatureEmotion() {

//     //animal - likes clean | stays in clean/half-dirty
//     //npc - likes dirty    | stays in half-dirty / dirty

//     // 0 - pc | 1 - animal | 2 - npc


//     //if creature type is an animal, and the room changes from clean to half dirty, then they growl and 
//     //                               if it is dirty, then they leave the room 

//     for (int i = 0; i < actualRoom.creatureAmount; i++) {

//         if((actualRoom.creatures.type == 1) && (roomStatus == false)) {

//             if (actualRoom.cleanliness == 2) {        //leave the room

//             }

//         } else if ((actualRoom->creatures->type == 1) && (roomStatus == true)) {

//         } else if ((actualRoom->creatures->type == 2) && (roomStatus == false)) {
  
//         }  else if ((actualRoom->creatures->type == 2) && (roomStatus == true)) {

//             if (actualRoom->cleanliness == 0) {        //leave the room

//             }
        
//         }
//     }
// }

/* I can probably combine all of these, but it's easier for me to do this for now*/

void changeRoomEast(struct Room roomlayout[], int numOfRooms) {
    if (actualRoom.east != -1) {

        for (int i = 0; i < numOfRooms; i++) { //sizeof(roomlayout)/sizeof(roomlayout[0] fix that
            if (roomlayout[i].west == actualRoom.cleanliness) {
                actualRoom.cleanliness = roomlayout[i].cleanliness;
                actualRoom.creatureAmount = roomlayout[i].creatureAmount;
                actualRoom.east = roomlayout[i].east;
                actualRoom.west = roomlayout[i].west;
                actualRoom.north = roomlayout[i].north;
                actualRoom.south = roomlayout[i].south;
            }
        }
    } else {
        printf("You try to head East and end up running into the wall!");
    }
}


void changeRoomWest(struct Room roomlayout[], int numOfRooms) {

       if (actualRoom.west != -1) {
        for (int i = 0; i < numOfRooms; i++) { //sizeof(roomlayout)/sizeof(roomlayout[0] fix that
            if (roomlayout[i].east == actualRoom.cleanliness) {
                actualRoom.cleanliness = roomlayout[i].cleanliness;
                actualRoom.creatureAmount = roomlayout[i].creatureAmount;
                actualRoom.east = roomlayout[i].east;
                actualRoom.west = roomlayout[i].west;
                actualRoom.north = roomlayout[i].north;
                actualRoom.south = roomlayout[i].south;
            }
        }
    } else {
        printf("You try to head West and end up running into the wall!");
    }
}

void changeRoomNorth(struct Room roomlayout[], int numOfRooms) {

    if (actualRoom.north != -1) {
        for (int i = 0; i < numOfRooms; i++) { //sizeof(roomlayout)/sizeof(roomlayout[0] fix that
            if (roomlayout[i].south == actualRoom.cleanliness) {
                actualRoom.cleanliness = roomlayout[i].cleanliness;
                actualRoom.creatureAmount = roomlayout[i].creatureAmount;
                actualRoom.east = roomlayout[i].east;
                actualRoom.west = roomlayout[i].west;
                actualRoom.north = roomlayout[i].north;
                actualRoom.south = roomlayout[i].south;
            }
        }
    } else {
        printf("You try to head North and end up running into the wall!");
    }
}

void changeRoomSouth(struct Room roomlayout[], int numOfRooms) {

    if (actualRoom.south != -1) {
        for (int i = 0; i < numOfRooms; i++) { //sizeof(roomlayout)/sizeof(roomlayout[0] fix that
            if (roomlayout[i].north == actualRoom.cleanliness) {
                actualRoom.cleanliness = roomlayout[i].cleanliness;
                actualRoom.creatureAmount = roomlayout[i].creatureAmount;
                actualRoom.east = roomlayout[i].east;
                actualRoom.west = roomlayout[i].west;
                actualRoom.north = roomlayout[i].north;
                actualRoom.south = roomlayout[i].south;
            }
        }
    } else {
        printf("You try to head South and end up running into the wall!");
    }
}
// /* End of Change Room*/

