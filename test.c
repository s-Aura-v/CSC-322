////
//// Created by Saurav Lamichhane on 9/16/23. Trying to do pointers.
////
//
//#include <stdio.h>
//#include <string.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <time.h>
//
//struct Creature {
//    int creatureNum;
//    int type;
//    int location;
//};
//
//struct Room {
//    int roomNum;
//    int state;
//    struct Room *north;
//    struct Room *south;
//    struct Room *east;
//    struct Room *west;
//    int northNum;
//    int southNum;
//    int eastNum;
//    int westNum;
//    struct Creature creatures[10];
//    int creatureCounter;
//};
//
//// Global variables
//int respect = 40;
//struct Room *rooms = NULL;
//struct Creature *creatures = NULL;
//
////functions *add later*
//void help();
//void createRoom(int roomNum);
//void assignRoom(int numOfRooms);
//void assignCreatures(int numOfCreatures, int numOfRooms);
//struct Room look(struct Room currentRoom);
//struct Room clean(struct Room currentRoom, bool roomStatus);
//struct Room dirty(struct Room currentRoom, bool roomStatus);
//void updateRoomState(struct Room currentRoom);
//struct Room changeRoomEast(struct Room currentRoom);
//struct Room changeRoomWest(struct Room currentRoom);
//struct Room changeRoomNorth(struct Room currentRoom);
//struct Room changeRoomSouth(struct Room currentRoom);
//void decreaseRespect();
//void higherDecreaseRespect();
//void increaseRespect();
//void higherIncreaseRespect();
//struct Room leaveRoom(struct Room currentRoom, int creatureNum);
//struct Room checkCreatureEmotion(struct Room currentRoom, bool roomStatus);
//void updateRoomNeighbors(struct Room currentRoom);
//struct Room creatureClean(struct Room currentRoom, int creatureNum, bool roomStatus);
//struct Room creatureDirty(struct Room currentRoom, int creatureNum, bool roomStatus);
//struct Room creatureChangeRoomEast(struct Room currentRoom, int creatureNum);
//struct Room creatureChangeRoomWest(struct Room currentRoom, int creatureNum);
//struct Room creatureChangeRoomNorth(struct Room currentRoom, int creatureNum);
//struct Room creatureChangeRoomSouth(struct Room currentRoom, int creatureNum);
//
//int main() {
//    // Setup (Adding User Input)
//    srand(time(0));
//    int numOfRooms;
//    int numOfCreatures;
//    bool roomStatus = true;
//
//    //Inputting the Rooms
//    printf("# of rooms: ");
//    scanf("%d", &numOfRooms);
//    rooms = (struct Room *) malloc(sizeof(struct Room) * numOfRooms);
//    for (int i = 0; i < numOfRooms; i++) {
//        printf("rooms: ");
//        scanf("%d %d %d %d %d", &rooms[i].state, &rooms[i].northNum, &rooms[i].southNum, &rooms[i].eastNum, &rooms[i].westNum);
//        createRoom(i);
//    }
//    assignRoom(numOfRooms);
//
//    //Creatures
//    printf("# of creatures: ");
//    scanf("%d", &numOfCreatures);
//    creatures = (struct Creature *) malloc(sizeof(struct Creature) * numOfCreatures);
//    for (int i = 0; i < numOfCreatures; i++) {
//        printf("type + location: ");
//        scanf("%d %d", &creatures[i].type, &creatures[i].location);
//    }
//    for (int i = 0; i < numOfCreatures; i++) {
//        if (creatures[i].type == 0) {
//            creatures[i].type = 3;
//        }
//    }
//    assignCreatures(numOfCreatures, numOfRooms);
//
//    struct Room * currentRoom;
//    for (int i = 0; i < numOfRooms; i++) {
//        for (int j = 0; j < numOfCreatures; j++) {
//            if (rooms[i].creatures[j].type == 3)
//                struct Room * currentRoom = &rooms[
//        }
//    }
//
//    return 0;
//}
//
//void createRoom(int roomNum) {
//    rooms[roomNum].roomNum = roomNum;
//    rooms[roomNum].north = NULL;
//    rooms[roomNum].south = NULL;
//    rooms[roomNum].east = NULL;
//    rooms[roomNum].west = NULL;
//}
//
//void assignRoom(int numOfRooms) {
//    for (int i = 0; i < numOfRooms; i++) {
//        for (int j = 0; j < numOfRooms; j++) {
//            if (rooms[i].northNum == rooms[j].roomNum) {
//                rooms[i].north = &rooms[j];
//            }
//            if (rooms[i].southNum == rooms[j].roomNum) {
//                rooms[i].south = &rooms[j];
//            }
//            if (rooms[i].eastNum == rooms[j].roomNum) {
//                rooms[i].east = &rooms[j];
//            }
//            if (rooms[i].westNum == rooms[j].roomNum) {
//                rooms[i].west = &rooms[j];
//            }
//        }
//    }
//}
//
