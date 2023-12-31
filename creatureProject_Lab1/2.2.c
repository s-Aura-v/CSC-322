//
// Creature Game by Saurav.
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

// Global variables + 3 global pointers
int respect = 40;
struct Room *rooms = NULL;
struct Creature *creatures = NULL;
struct Room *currentRoom;

//functions:
void createRoom(int roomNum);
void assignRoom(int numOfRooms);
void setCreatures(int numOfRooms);
void assignCreatures(int numOfCreatures, int numOfRooms);
void help();
void look();
void clean();
void dirty();
void updateRespect(bool roomStatus);
void changeRoomEast();
void changeRoomWest();
void changeRoomNorth();
void changeRoomSouth();
void leaveRoom(int creatureType);
void creatureChangeRoomEast(int creatureNum);
void creatureChangeRoomWest(int creatureNum);
void creatureChangeRoomNorth(int creatureNum);
void creatureChangeRoomSouth(int creatureNum);
void creatureClean(int creatureNum);
void creatureDirty(int creatureNum);


int main() {
    // Setup (Adding User Input)
    int numOfRooms;
    int numOfCreatures;
    srand(time(0));

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
    for (int i = 0; i < numOfCreatures; i++) {
        if (creatures[i].type == 0) {
            creatures[i].type = 3;
        }
    }
    setCreatures(numOfRooms);
    assignCreatures(numOfCreatures, numOfRooms);

    //Assigning current room
    for (int i = 0; i < numOfRooms; i++) {
        for (int j = 0; j < rooms[i].creatureCounter; j++) {
            if (rooms[i].creatures[j].type == 3) {      // 3 = PC
                currentRoom = &rooms[i];
            }
        }
    }

    char input[20];
    while (respect > 0 || respect < 80) {
        //Set the input
        printf("Enter a command: ");
        scanf("%s", input);
        //Tests
        if (strcmp(input, "tLook") == 0) {
            for (int i = 0; i < numOfRooms; i++) {
                printf("%d - ", rooms[i].roomNum);
                printf("%d %d\n", rooms[i].roomNum, rooms[i].creatureCounter);
            }
            printf("%d\n", respect);
        }
        else if (strcmp(input, "rLook") == 0) {
            printf("Current Room: %d: S:%d\n ", currentRoom->roomNum, currentRoom->state);
            for (int i = 0; i < numOfRooms; i++) {
                printf("%d %d %d\n", rooms[i].roomNum, rooms[i].state, rooms[i].creatureCounter);
            }
        }

            //end of tests
        else if (strcmp(input, "exit") == 0) {
            break;
        }
        else if (strcmp(input, "look") == 0) {
            look();
        }
        else if (strcmp(input, "clean") == 0) {
            clean();
        }
        else if (strcmp(input, "dirty") == 0) {
            dirty();
        }
        else if (strcmp(input, "east") == 0) {
            changeRoomEast();
        }
        else if (strcmp(input, "west") == 0) {
            changeRoomWest();
        }
        else if (strcmp(input, "north") == 0) {
            changeRoomNorth();
        }
        else if (strcmp(input, "south") == 0) {
            changeRoomSouth();
        }
        else if (strcmp(input, "help") == 0) {
            help();
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
                creatureClean(creatureNum);
            }
            else if (strcmp(command, "dirty") == 0) {
                creatureDirty(creatureNum);
            }
            else if (strcmp(command, "east") == 0) {
                creatureChangeRoomEast(creatureNum);
            }
            else if (strcmp(command, "west") == 0) {
                creatureChangeRoomWest(creatureNum);
            }
            else if (strcmp(command, "north") == 0) {
                creatureChangeRoomNorth(creatureNum);
            }
            else if (strcmp(command, "south") == 0) {
                creatureChangeRoomSouth(creatureNum);
            }
        }
    }

    if (respect > 80) {
        printf("You actually won!\n");
    } else if (respect < 0){
        printf("Did you lose this game because you played this game or did you play this game because you wanted to lose?\n");
    } else {
        printf("Goodbye! Quitting is actually the real way to win\n");
    }

    //free memory
    free(rooms);
    free(creatures);
    return 0;
}

void help() {
    printf(
            "To enter the amount of rooms, enter an [int]. <The max amount of rooms is 99>. Example: 3\n"
            "To input a room, enter [State North South East West] in order. Example: 0 -1 1 -1 2\n"
            "To enter the amount of creatures, enter an [int]. Example: 4\n"
            "To input a creature, enter [CreatureType CreatureLocation]. Example: 1 0\n"
            "Creature Types: PC - 0 | Animal - 1 | NPC - 2 | Each creature is numbered by when they were inputted, starting from 0.\n"
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

void setCreatures(int numOfRooms) {
    for (int i = 0; i < numOfRooms; i++) {
        for (int j = 0; j < 10; j++) {
            rooms[i].creatures[j].creatureNum = -1;
            rooms[i].creatures[j].type = 0;
            rooms[i].creatures[j].location = -1;
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
            rooms[i].creatureCounter = roomIndex;
        }
    }
}

void look() {
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

void clean() {
    bool roomStatus;
    if (currentRoom->state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
        currentRoom->state = 1;
        roomStatus = true;
        updateRespect(roomStatus);
    } else if (currentRoom->state == 1) { /* if it's half-dirty, make it clean*/
        currentRoom->state = 0;
        roomStatus = true;
        updateRespect(roomStatus);
    } else {
        printf("Your room is already clean!\n");
    }
}
void dirty() {
    bool roomStatus;
    if (currentRoom->state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
        printf("Your room is already dirty!\n");
    } else if (currentRoom->state == 1) { /* if it's half-dirty, make it clean*/
        currentRoom->state = 2;
        roomStatus = false;
        updateRespect(roomStatus);
    } else {
        currentRoom->state = 1;
        roomStatus = false;
        updateRespect(roomStatus);
    }
}

void updateRespect(bool roomStatus) {       //Update Respect due to PC's actions ONLY
    for (int i = 0; i < currentRoom->creatureCounter; i++) {
        if (roomStatus == true && currentRoom) {   //if room got clean
            if (currentRoom->creatures[i].type == 1) {
                respect++;
                printf("%d licks your face. Respect is now %d.\n", currentRoom->creatures[i].creatureNum, respect);
            } else if (currentRoom->creatures[i].type == 2) {
                respect--;
                printf("%d growls. Respect is now %d.\n", currentRoom->creatures[i].creatureNum, respect);
                if (currentRoom->state == 0) {  //if the room becomes clean, NPCs leave
                    leaveRoom(2);
                }
            }
        } else if (roomStatus == false) {   //if room got dirty
            if (currentRoom->creatures[i].type == 1) {
                respect--;
                printf("%d grumbles. Respect is now %d.\n", currentRoom->creatures[i].creatureNum, respect);
                if (currentRoom->state == 2) {  //if the room becomes dirty, animal leaves
                    leaveRoom(1);
                }
            } else if (currentRoom->creatures[i].type == 2) {
                respect++;
                printf("%d smiles. Respect is now %d.\n", currentRoom->creatures[i].creatureNum, respect);
            }
        }
    }
}

void leaveRoom(int creatureType) {
    int randomV;
    bool isExecuted = false;
    while (isExecuted == false) {
        randomV = rand() % 4; // 0-east, 1-west, 2-north,3-south
        if (randomV == 0) {
            if (currentRoom->eastNum != -1 && isExecuted == false) { //east is open
                for (int i = 0; i < currentRoom->creatureCounter; i++) {
                    if (currentRoom->creatures[i].type == creatureType) { //type wants to leave
                        struct Creature temp = currentRoom->creatures[i];
                        //Remove them from the current one
                        for (int j = 0; j < currentRoom->creatureCounter; j++) {
                            if (currentRoom->creatures[j].type == creatureType) {
                                currentRoom->creatures[j].type = 0;
                                currentRoom->creatureCounter--;
                                break;
                            }
                        }
                        //Move them east
                        for (int j = 0; j < currentRoom->east->creatureCounter + 1; j++) {
                            if (currentRoom->east->creatures[j].type ==
                                0) { //if the creature spot is free, then add the creature there
                                currentRoom->east->creatures[j] = temp;
                                currentRoom->east->creatureCounter++;
                                //Try to change the room if NPC doesn't like it
                                if ((currentRoom->east->state == 2 && temp.type == 1) ||
                                    (currentRoom->east->state == 0 && temp.type == 2)) {
                                    currentRoom->east->state = 1;           // clean it or dirty it
                                }
                                printf("%d is dissatisfied with the room and leaves to %d\n",
                                       currentRoom->creatures[i].creatureNum, currentRoom->eastNum);
                                isExecuted = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (randomV == 1) {
            if (currentRoom->westNum != -1 && isExecuted == false) {
                if (currentRoom->westNum != -1) { //east is open
                    for (int i = 0; i < currentRoom->creatureCounter; i++) {
                        if (currentRoom->creatures[i].type == creatureType) { //type wants to leave
                            struct Creature temp = currentRoom->creatures[i];
                            //Remove them from the current one
                            for (int j = 0; j < currentRoom->creatureCounter; j++) {
                                if (currentRoom->creatures[j].type == creatureType) {
                                    currentRoom->creatures[j].type = 0;
                                    currentRoom->creatureCounter--;
                                    break;
                                }
                            }
                            //Move them west
                            for (int j = 0; j < currentRoom->west->creatureCounter + 1; j++) {
                                if (currentRoom->west->creatures[j].type ==
                                    0) { //if the creature spot is free, then add the creature there
                                    currentRoom->west->creatures[j] = temp;
                                    currentRoom->west->creatureCounter++;
                                    if ((currentRoom->west->state == 2 && temp.type == 1) ||
                                        (currentRoom->west->state == 0 && temp.type == 2)) {
                                        currentRoom->west->state = 1;           // clean it or dirty it
                                    }
                                    printf("%d is dissatisfied with the room and leaves to %d\n",
                                           currentRoom->creatures[i].creatureNum, currentRoom->westNum);
                                    isExecuted = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (randomV == 2) {
            if (currentRoom->northNum != -1 && isExecuted == false) {
                if (currentRoom->northNum != -1) { //east is open
                    for (int i = 0; i < currentRoom->creatureCounter; i++) {
                        if (currentRoom->creatures[i].type == creatureType) { //type wants to leave
                            struct Creature temp = currentRoom->creatures[i];
                            //Remove them from the current one
                            for (int j = 0; j < currentRoom->creatureCounter; j++) {
                                if (currentRoom->creatures[j].type == creatureType) {
                                    currentRoom->creatures[j].type = 0;
                                    currentRoom->creatureCounter--;
                                    break;
                                }
                            }
                            //Move them east
                            for (int j = 0; j < currentRoom->north->creatureCounter + 1; j++) {
                                if (currentRoom->north->creatures[j].type ==
                                    0) { //if the creature spot is free, then add the creature there
                                    currentRoom->north->creatures[j] = temp;
                                    currentRoom->north->creatureCounter++;
                                    if ((currentRoom->north->state == 2 && temp.type == 1) ||
                                        (currentRoom->north->state == 0 && temp.type == 2)) {
                                        currentRoom->north->state = 1;           // clean it or dirty it
                                    }
                                    printf("%d is dissatisfied with the room and leaves to %d\n",
                                           currentRoom->creatures[i].creatureNum, currentRoom->northNum);
                                    isExecuted = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (randomV == 3) {
            if (currentRoom->southNum != -1 && isExecuted == false) {
                if (currentRoom->southNum != -1) { //east is open
                    for (int i = 0; i < currentRoom->creatureCounter; i++) {
                        if (currentRoom->creatures[i].type == creatureType) { //type wants to leave
                            struct Creature temp = currentRoom->creatures[i];
                            //Remove them from the current one
                            for (int j = 0; j < currentRoom->creatureCounter; j++) {
                                if (currentRoom->creatures[j].type == creatureType) {
                                    currentRoom->creatures[j].type = 0;
                                    currentRoom->creatureCounter--;
                                    break;
                                }
                            }
                            //Move them east
                            for (int j = 0; j < currentRoom->south->creatureCounter + 1; j++) {
                                if (currentRoom->south->creatures[j].type ==
                                    0) { //if the creature spot is free, then add the creature there
                                    currentRoom->south->creatures[j] = temp;
                                    currentRoom->south->creatureCounter++;
                                    if ((currentRoom->south->state == 2 && temp.type == 1) ||
                                        (currentRoom->south->state == 0 && temp.type == 2)) {
                                        currentRoom->south->state = 1;           // clean it or dirty it
                                    }
                                    printf("%d is dissatisfied with the room and leaves to %d\n",
                                           currentRoom->creatures[i].creatureNum, currentRoom->southNum);
                                    isExecuted = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (currentRoom->northNum == -1 && currentRoom->southNum == -1 && currentRoom->eastNum == -1 &&
            currentRoom->westNum == -1) {
            isExecuted = true;
        }
    }
    if (currentRoom->northNum == -1 && currentRoom->southNum == -1 && currentRoom->eastNum == -1 && currentRoom->westNum == -1) {
        for (int i = 0; i < 10; i++) {  // Go through the creatures
            if (currentRoom->creatures[i].type == creatureType) {
                currentRoom->creatures[i].type = 0;
                printf("%d has nowhere to go so they left through the roof.\n", currentRoom->creatures[i].creatureNum);
                currentRoom->creatureCounter--;
                break;  // Exit the loop after finding and processing the creature
            }
        }
        // Everybody be mad
        for (int i = 0; i < currentRoom->creatureCounter; i++) {
            if (currentRoom->creatures[i].type == 1 || currentRoom->creatures[i].type == 2) {
                printf("%d did not like the way the previous creature was treated. ", currentRoom->creatures[i].creatureNum);
                respect--;  // Respect decremented here
                printf("Respect is now %d\n", respect);
                break;  // This break exits the inner loop after decrementing respect once
            }
        }
    }
}


void changeRoomEast() {
    //Reference to PC to add later
    struct Creature pc;
    for (int i = 0; i < 10; i++) {
        if (currentRoom->creatures[i].type == 3) {
            pc = currentRoom->creatures[i];
        }
    }
    if (currentRoom->eastNum != -1) {
        //Remove PC from original room
        for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
            if (currentRoom->creatures[i].type == 3) {
                currentRoom->creatures[i].type = 0;
                currentRoom->creatureCounter--;
                break;
            }
        }
        //Add PC to new room
        if (currentRoom->east->creatureCounter < 10) {
            //Add PC to east room
            for (int i = 0; i < currentRoom->east->creatureCounter + 1; i++) {
                if (currentRoom->east->creatures[i].type == 0) {
                    currentRoom->east->creatures[i] = pc;
                    currentRoom->east->creatureCounter++;
                    break;
                }
            }
            currentRoom = currentRoom->east;
        } else {
            printf("Room full!\n");
        }
    } else {
        printf("You tried going east, but ran into a wall.\n");
    }
}

void changeRoomWest() {
    //Reference to PC to add later
    struct Creature pc;
    for (int i = 0; i < 10; i++) {
        if (currentRoom->creatures[i].type == 3) {
            pc = currentRoom->creatures[i];
        }
    }
    if (currentRoom->westNum != -1) {
        if (currentRoom->west->creatureCounter < 10) {
            //Remove PC from original room
            for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
                if (currentRoom->creatures[i].type == 3) {
                    currentRoom->creatures[i].type = 0;
                    currentRoom->creatureCounter--;
                    break;
                }
            }
            //Add PC to east room
            for (int i = 0; i < currentRoom->west->creatureCounter + 1; i++) {
                if (currentRoom->west->creatures[i].type == 0) {
                    currentRoom->west->creatures[i] = pc;
                    currentRoom->west->creatureCounter++;
                    break;
                }
            }
            currentRoom = currentRoom->west;
        } else {
            printf("Room full!\n");
        }
    } else {
        printf("You tried going west, but ran into a wall.\n");
    }
}

void changeRoomNorth() {
    //Reference to PC to add later
    struct Creature pc;
    for (int i = 0; i < 10; i++) {
        if (currentRoom->creatures[i].type == 3) {
            pc = currentRoom->creatures[i];
        }
    }
    if (currentRoom->northNum != -1) {
        //Remove PC from original room
        for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
            if (currentRoom->creatures[i].type == 3) {
                currentRoom->creatures[i].type = 0;
                currentRoom->creatureCounter--;
                break;
            }
        }
        if (currentRoom->north->creatureCounter < 10) {
            //Add PC to east room
            for (int i = 0; i < currentRoom->north->creatureCounter + 1; i++) {
                if (currentRoom->north->creatures[i].type == 0) {
                    currentRoom->north->creatures[i] = pc;
                    currentRoom->north->creatureCounter++;
                    break;
                }
            }
            currentRoom = currentRoom->north;
        } else {
            printf("Room full!\n");
        }
    } else {
        printf("You tried going north, but ran into a wall.\n");
    }
}

void changeRoomSouth() {
    //Reference to PC to add later
    struct Creature pc;
    for (int i = 0; i < 10; i++) {
        if (currentRoom->creatures[i].type == 3) {
            pc = currentRoom->creatures[i];
        }
    }
    if (currentRoom->southNum != -1) {
        if (currentRoom->south->creatureCounter < 10) {
            //Remove PC from original room
            for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
                if (currentRoom->creatures[i].type == 3) {
                    currentRoom->creatures[i].type = 0;
                    currentRoom->creatureCounter--;
                    break;
                }
            }
            //Add PC to south room
            for (int i = 0; i < currentRoom->south->creatureCounter + 1; i++) {
                if (currentRoom->south->creatures[i].type == 0) {
                    currentRoom->south->creatures[i] = pc;
                    currentRoom->south->creatureCounter++;
                    break;
                }
            }
            currentRoom = currentRoom->south;
        } else {
            printf("Room full!\n");
        }
    } else {
        printf("You tried going south, but ran into a wall.\n");
    }
}

void creatureChangeRoomEast(int creatureNum) {
    if (currentRoom->eastNum != -1) {
        if (currentRoom->east->creatureCounter < 10) {
            for (int i = 0; i < currentRoom->creatureCounter; i++) {
                if (currentRoom->creatures[i].creatureNum == creatureNum) {
                    for (int j = 0; j < 10; j++) {
                        if (currentRoom->east->creatures[j].type == 0) {
                            struct Creature temp = currentRoom->creatures[i];
                            //Remove creature from current
                            currentRoom->creatures[i].type = 0;
                            currentRoom->creatureCounter--;
                            //Add creature to east
                            currentRoom->east->creatures[j] = temp;
                            currentRoom->east->creatureCounter++;
                            //Change state of room
                            if (currentRoom->east->state == 2 && temp.type == 1) { //if dirty and animal
                                currentRoom->east->state = 1; //half-dirty
                            } else if (currentRoom->east->state == 0 && temp.type == 2) { //if clean and NPC
                                currentRoom->east->state = 1;
                            }
                            break;
                        }
                    }
                }
            }
        } else {
            respect--;
            printf("%d tried to enter the room, but ended up getting blocked by the mass of bodies. Respect is now %d\n", creatureNum, respect);
        }
    }
}

void creatureChangeRoomWest(int creatureNum) {
    if (currentRoom->westNum!= -1) {
        if (currentRoom->west->creatureCounter < 10) {
            for (int i = 0; i < currentRoom->creatureCounter; i++) {
                if (currentRoom->creatures[i].creatureNum == creatureNum) {
                    for (int j = 0; j < currentRoom->west->creatureCounter + 1; j++) {
                        if (currentRoom->west->creatures[j].type == 0) {
                            //Temp to add it to new room
                            struct Creature temp = currentRoom->creatures[i];
                            //Remove creature from current
                            currentRoom->creatures[i].type = 0;
                            currentRoom->creatureCounter--;
                            //Add creature to east
                            currentRoom->west->creatures[j] = temp;
                            currentRoom->west->creatureCounter++;
                            //Change state of room
                            if (currentRoom->west->state == 2 && temp.type == 1) { //if dirty and animal
                                currentRoom->west->state = 1; //half-dirty
                            } else if (currentRoom->west->state == 0 && temp.type == 2) { //if clean and NPC
                                currentRoom->west->state = 1;
                            }
                            break;
                        }
                    }
                }
            }
        } else {
            respect--;
            printf("%d tried to enter the room, but ended up getting blocked by the mass of bodies. Respect is now %d\n", creatureNum, respect);
        }
    }
}

void creatureChangeRoomNorth(int creatureNum) {
    if (currentRoom->northNum != -1) {
        if (currentRoom->north->creatureCounter < 10) {
            for (int i = 0; i < currentRoom->creatureCounter; i++) {
                if (currentRoom->creatures[i].creatureNum == creatureNum) {
                    for (int j = 0; j < currentRoom->north->creatureCounter + 1; j++) {
                        if (currentRoom->north->creatures[j].type == 0) {
                            //Temp to add it to new room
                            struct Creature temp = currentRoom->creatures[i];
                            //Remove creature from current
                            currentRoom->creatures[i].type = 0;
                            currentRoom->creatureCounter--;
                            //Add creature to east
                            currentRoom->north->creatures[j] = temp;
                            currentRoom->north->creatureCounter++;
                            //Change state of room
                            if (currentRoom->north->state == 2 && temp.type == 1) { //if dirty and animal
                                currentRoom->north->state = 1; //half-dirty
                            } else if (currentRoom->north->state == 0 && temp.type == 2) { //if clean and NPC
                                currentRoom->north->state = 1;
                            }
                            break;
                        }
                    }
                }
            }
        } else {
            respect--;
            printf("%d tried to enter the room, but ended up getting blocked by the mass of bodies. Respect is now %d\n", creatureNum, respect);
        }
    }
}

void creatureChangeRoomSouth(int creatureNum) {
    if (currentRoom->southNum != -1) {
        if (currentRoom->south->creatureCounter < 10) {
            for (int i = 0; i < currentRoom->creatureCounter; i++) {
                if (currentRoom->creatures[i].creatureNum == creatureNum) {
                    for (int j = 0; j < currentRoom->south->creatureCounter + 1; j++) {
                        if (currentRoom->south->creatures[j].type == 0) {
                            //Temp to add it to new room
                            struct Creature temp = currentRoom->creatures[i];
                            //Remove creature from current
                            currentRoom->creatures[i].type = 0;
                            currentRoom->creatureCounter--;
                            //Add creature to south
                            currentRoom->south->creatures[j] = temp;
                            currentRoom->south->creatureCounter++;
                            //Change state of room
                            if (currentRoom->south->state == 2 && temp.type == 1) { //if dirty and animal
                                currentRoom->south->state = 1; //half-dirty
                            } else if (currentRoom->south->state == 0 && temp.type == 2) { //if clean and NPC
                                currentRoom->south->state = 1;
                            }
                            break;
                        }
                    }
                }
            }
        } else {
            printf("%d tried to enter the room, but ended up getting blocked by the mass of bodies. Respect is now %d\n", creatureNum, respect);
            respect--;
        }
    }
}

void creatureClean(int creatureNum) {   //error
    for (int i = 0; i < currentRoom->creatureCounter; i++) {
        if (currentRoom->creatures[i].creatureNum == creatureNum) {
            if (currentRoom->state == 2 && currentRoom->creatures[i].type == 1) {   //Room:Dirty | Animal:Clean | Animal-happy, npc-sad
                currentRoom->state = 1;
                respect += 3;
                printf("%d licks your face a lot! Respect is now %d\n", creatureNum, respect);
                //Decrease respect based on other creatures
                for (int j = 0; j < 10; j++) {
                    if (currentRoom->creatures[j].type == 2) {
                        respect--;
                        printf("%d grumbles! Respect is now %d\n", currentRoom->creatures[j].creatureNum, respect);
                    }
                }
            } else if (currentRoom->state == 1 && currentRoom->creatures[i].type == 1) {
                currentRoom->state = 0;
                respect += 3;
                printf("%d licks your face a lot! Respect is now %d\n", creatureNum, respect);

                //Decrease respect based on other creatures
                for (int j = 0; j < 10; j++) {
                    if (currentRoom->creatures[j].type == 2) {
                        respect--;
                        printf("%d grumbles! Respect is now %d\n", currentRoom->creatures[j].creatureNum,
                               respect);
                        leaveRoom(2);   //room is clean so NPC now leaves
                    }
                }
                } else if (currentRoom->state == 0) {
                printf("Room is already clean!");
            } else if (currentRoom->state == 1 && currentRoom->creatures[i].type == 2) {
                currentRoom->state = 0;
                respect -= 3;
                printf("%d grumbles lot! Respect is now %d\n", creatureNum, respect);
                leaveRoom(2);
                //Increase respect based on other creatures
                for (int j = 0; j < 10; j++) {
                    if (currentRoom->creatures[j].type == 1) {
                        respect++;
                        printf("%d licks your face! Respect is now %d\n", currentRoom->creatures[j].creatureNum,
                               respect);
                    }
                }
                } else if (currentRoom->state == 2 && currentRoom->creatures[i].type == 2) {
                currentRoom->state = 1;
                respect -= 3;
                printf("%d grumbles lot! Respect is now %d\n", creatureNum, respect);
                //Increase respect based on other creatures
                for (int j = 0; j < 10; j++) {
                    if (currentRoom->creatures[j].type == 1) {
                        respect++;
                        printf("%d licks your face! Respect is now %d\n", currentRoom->creatures[j].creatureNum,
                               respect);
                    }
                }
            }
        }
    }
}

void creatureDirty(int creatureNum) {
    for (int i = 0; i < currentRoom->creatureCounter; i++) {
        if (currentRoom->creatures[i].creatureNum == creatureNum) {
            if (currentRoom->state == 0 && currentRoom->creatures[i].type == 2) {     // clean and npc dirties
                currentRoom->state = 1;
                respect += 3;
                printf("%d smiles a lot! Respect is now %d\n", creatureNum, respect);
                for (int j = 0; j < 10; j++) {
                    if (currentRoom->creatures[j].type == 1) {
                        respect--;
                        printf("%d growls. Respect is now %d\n", currentRoom->creatures[j].creatureNum, respect);
                    }
                }
            } else if (currentRoom->state == 1 && currentRoom->creatures[i].type == 2) {
                currentRoom->state = 2;
                respect += 3;
                printf("%d smiles a lot! Respect is now %d\n", creatureNum, respect);
                for (int j = 0; j < 10; j++) {
                    if (currentRoom->creatures[j].type == 1) {
                        respect--;
                        printf("%d growls. Respect is now %d\n", currentRoom->creatures[j].creatureNum, respect);
                        leaveRoom(1);
                    }
                }
            } else if (currentRoom->state == 2) {
                printf("Room is already dirty!");
            } else if (currentRoom->state == 1 && currentRoom->creatures[i].type == 1) {     // clean and animal dirties
                currentRoom->state = 2;
                respect -= 3;
                printf("%d growls a lot! Respect is now %d\n", creatureNum, respect);
                leaveRoom(1);
                for (int j = 0; j < 10; j++) {
                    if (currentRoom->creatures[j].type == 2) {
                        respect++;
                        printf("%d smiles. Respect is now %d\n", currentRoom->creatures[j].creatureNum, respect);
                    }
                }
            } else if (currentRoom->state == 0 && currentRoom->creatures[i].type == 1) {
                currentRoom->state = 1;
                respect -= 3;
                printf("%d growls a lot! Respect is now %d\n", creatureNum, respect);
                for (int j = 0; j < 10; j++) {
                    if (currentRoom->creatures[j].type == 2) {
                        respect++;
                        printf("%d smiles. Respect is now %d\n", currentRoom->creatures[j].creatureNum, respect);
                    }
                }
            }
        }
    }
}