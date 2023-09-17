    //
    // Created by Saurav Lamichhane on 9/17/23.
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
    void assignCreatures(int numOfCreatures, int numOfRooms);
    void look();
    void clean();
    void dirty();
    void updateRespect(bool roomStatus);
    void changeRoomEast();
    void changeRoomWest();
    void changeRoomNorth();
    void changeRoomSouth();

    //work in progress
    void leaveRoom(int creatureType);



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
            scanf("%d %d %d %d %d", &rooms[i].state, &rooms[i].northNum, &rooms[i].southNum, &rooms[i].eastNum,
                  &rooms[i].westNum);
            createRoom(i);
        }
        assignRoom(numOfRooms);

        //test code

        //fix it so that it doesn't run when its null

        //Creatures
        printf("# of creatures: ");
        scanf("%d", &numOfCreatures);
        creatures = (struct Creature *) malloc(sizeof(struct Creature) * numOfCreatures);
        int pcNum;
        for (int i = 0; i < numOfCreatures; i++) {
            printf("type + location: ");
            scanf("%d %d", &creatures[i].type, &creatures[i].location);
        }
        for (int i = 0; i < numOfCreatures; i++) {
            if (creatures[i].type == 0) {
                creatures[i].type = 3;
                pcNum = creatures[i].creatureNum;
            }
        }
        assignCreatures(numOfCreatures, numOfRooms);

        //Assigning current room
        currentRoom = malloc(sizeof (struct Room));
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
                printf("Goodbye!");
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


        }

        //free memory
        free(rooms);
        free(creatures);
        free(currentRoom);

        return 0;
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
            printf("Your room is already clean!");
        }
    }
    void dirty() {
        bool roomStatus;
        if (currentRoom->state == 2) { /* if it's dirty, make it half dirty, remember the respect system*/
            printf("Your room is already dirty!");
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
        bool isExecuted = false;
        if (currentRoom->eastNum != -1 && isExecuted == false) { //east is open
            for (int i = 0; i < currentRoom->creatureCounter; i++) {
                if (currentRoom->creatures[i].type == creatureType) { //type wants to leave
                    //Move them east
                    for (int j = 0; j < currentRoom->east->creatureCounter + 1; j++) {
                        if (currentRoom->east->creatures[j].type == 0) { //if the creature spot is free, then add the creature there
                            currentRoom->east->creatures[j] = currentRoom->creatures[i];
                            currentRoom->east->creatureCounter++;
                            printf("%d is dissatisfied with the room and leaves to %d\n", currentRoom->creatures[i].creatureNum, currentRoom->eastNum);
                            isExecuted = true;
                            break;
                        }
                    }
                    //Remove them from the current one
                    for (int j = 0; j < currentRoom->creatureCounter; j++) {
                        if (currentRoom->creatures[j].type == creatureType) {
                            currentRoom->creatures[j].type = 0;
                            currentRoom->creatureCounter--;
                            break;
                        }
                    }
                }
            }
        }
        if (currentRoom->westNum != -1 && isExecuted == false) {
            if (currentRoom->westNum != -1) { //east is open
                for (int i = 0; i < currentRoom->creatureCounter; i++) {
                    if (currentRoom->creatures[i].type == creatureType) { //type wants to leave
                        //Move them east
                        for (int j = 0; j < currentRoom->west->creatureCounter + 1; j++) {
                            if (currentRoom->west->creatures[j].type == 0) { //if the creature spot is free, then add the creature there
                                currentRoom->west->creatures[j] = currentRoom->creatures[i];
                                currentRoom->west->creatureCounter++;
                                printf("%d is dissatisfied with the room and leaves to %d\n", currentRoom->creatures[i].creatureNum, currentRoom->westNum);
                                isExecuted = true;
                                break;
                            }
                        }
                        //Remove them from the current one
                        for (int j = 0; j < currentRoom->creatureCounter; j++) {
                            if (currentRoom->creatures[j].type == creatureType) {
                                currentRoom->creatures[j].type = 0;
                                currentRoom->creatureCounter--;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (currentRoom->northNum != -1 && isExecuted == false) {
            if (currentRoom->northNum != -1) { //east is open
                for (int i = 0; i < currentRoom->creatureCounter; i++) {
                    if (currentRoom->creatures[i].type == creatureType) { //type wants to leave
                        //Move them east
                        for (int j = 0; j < currentRoom->north->creatureCounter + 1; j++) {
                            if (currentRoom->north->creatures[j].type == 0) { //if the creature spot is free, then add the creature there
                                currentRoom->north->creatures[j] = currentRoom->creatures[i];
                                currentRoom->north->creatureCounter++;
                                printf("%d is dissatisfied with the room and leaves to %d\n", currentRoom->creatures[i].creatureNum, currentRoom->northNum);
                                isExecuted = true;
                                break;
                            }
                        }
                        //Remove them from the current one
                        for (int j = 0; j < currentRoom->creatureCounter; j++) {
                            if (currentRoom->creatures[j].type == creatureType) {
                                currentRoom->creatures[j].type = 0;
                                currentRoom->creatureCounter--;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (currentRoom->southNum != -1 && isExecuted == false) {
            if (currentRoom->southNum != -1) { //east is open
                for (int i = 0; i < currentRoom->creatureCounter; i++) {
                    if (currentRoom->creatures[i].type == creatureType) { //type wants to leave
                        //Move them east
                        for (int j = 0; j < currentRoom->south->creatureCounter + 1; j++) {
                            if (currentRoom->south->creatures[j].type == 0) { //if the creature spot is free, then add the creature there
                                currentRoom->south->creatures[j] = currentRoom->creatures[i];
                                currentRoom->south->creatureCounter++;
                                printf("%d is dissatisfied with the room and leaves to %d\n", currentRoom->creatures[i].creatureNum, currentRoom->southNum);
                                isExecuted = true;
                                break;
                            }
                        }
                        //Remove them from the current one
                        for (int j = 0; j < currentRoom->creatureCounter; j++) {
                            if (currentRoom->creatures[j].type == creatureType) {
                                currentRoom->creatures[j].type = 0;
                                currentRoom->creatureCounter--;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }


    void changeRoomEast() {
        //Reference to PC to add later
        struct Creature pc;
        for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
            if (currentRoom->creatures[i].type == 3) {
                pc = currentRoom->creatures[i];
            }
        }
        if (currentRoom->eastNum != -1) {
            //Add PC to east room
            for (int i = 0; i < currentRoom->east->creatureCounter + 1; i++) {
                if (currentRoom->east->creatures[i].type == 0) {
                    currentRoom->east->creatures[i] = pc;
                    currentRoom->east->creatureCounter++;
                    break;
                }
            }
            //Remove PC from original room
            for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
                if (currentRoom->creatures[i].type == 3) {
                    currentRoom->creatures[i].type = 0;
                    currentRoom->creatureCounter--;
                    break;
                }
            }
            currentRoom = currentRoom->east;
        } else {
            printf("You tried going east, but ran into a wall.\n");
        }
    }

    void changeRoomWest() {
        //Reference to PC to add later
        struct Creature pc;
        for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
            if (currentRoom->creatures[i].type == 3) {
                pc = currentRoom->creatures[i];
            }
        }
        if (currentRoom->westNum != -1) {
            //Add PC to east room
            for (int i = 0; i < currentRoom->west->creatureCounter + 1; i++) {
                if (currentRoom->west->creatures[i].type == 0) {
                    currentRoom->west->creatures[i] = pc;
                    currentRoom->west->creatureCounter++;
                    break;
                }
            }
            //Remove PC from original room
            for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
                if (currentRoom->creatures[i].type == 3) {
                    currentRoom->creatures[i].type = 0;
                    currentRoom->creatureCounter--;
                    break;
                }
            }
            currentRoom = currentRoom->west;
        } else {
            printf("You tried going west, but ran into a wall.\n");
        }
    }


    void changeRoomNorth() {
        //Reference to PC to add later
        struct Creature pc;
        for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
            if (currentRoom->creatures[i].type == 3) {
                pc = currentRoom->creatures[i];
            }
        }
        if (currentRoom->northNum != -1) {
            //Add PC to east room
            for (int i = 0; i < currentRoom->north->creatureCounter + 1; i++) {
                if (currentRoom->north->creatures[i].type == 0) {
                    currentRoom->north->creatures[i] = pc;
                    currentRoom->north->creatureCounter++;
                    break;
                }
            }
            //Remove PC from original room
            for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
                if (currentRoom->creatures[i].type == 3) {
                    currentRoom->creatures[i].type = 0;
                    currentRoom->creatureCounter--;
                    break;
                }
            }
            currentRoom = currentRoom->north;
        } else {
            printf("You tried going north, but ran into a wall.\n");
        }
    }


    void changeRoomSouth() {
        //Reference to PC to add later
        struct Creature pc;
        for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
            if (currentRoom->creatures[i].type == 3) {
                pc = currentRoom->creatures[i];
            }
        }
        if (currentRoom->southNum != -1) {
            //Add PC to east room
            for (int i = 0; i < currentRoom->south->creatureCounter + 1; i++) {
                if (currentRoom->south->creatures[i].type == 0) {
                    currentRoom->south->creatures[i] = pc;
                    currentRoom->south->creatureCounter++;
                    break;
                }
            }
            //Remove PC from original room
            for (int i = 0; i < currentRoom->creatureCounter + 1; i++) {
                if (currentRoom->creatures[i].type == 3) {
                    currentRoom->creatures[i].type = 0;
                    currentRoom->creatureCounter--;
                    break;
                }
            }
            currentRoom = currentRoom->south;
        } else {
            printf("You tried going south, but ran into a wall.\n");
        }
    }