#include <stdio.h>
#include <string.h>

/* Startup */
int respect;

struct Creatures {
    int type;
    int location;
};

struct Room{
    int cleanliness;
    int north;
    int east;
    int south;
    int west;
    struct Creatures creature;
};


void look(struct Room *roomlayout, struct Creatures *creatures);
void grumble();
void clean(struct Room *roomlayout);
void dirty();
void checkCreatureEmotion();

int main() {
    int numOfRooms;
    int numOfCreatures;
    
    printf("Enter the number of rooms: ");
    scanf("%d", &numOfRooms); /* n */
    struct Room roomlayout[numOfRooms];

    /*Enter the room data*/
    for (int i = 0; i < numOfRooms; i++) {
        printf("Enter the state of the room and its neighbors: ");
        scanf("%d %d %d %d %d", &roomlayout[i].cleanliness, &roomlayout[i].north, &roomlayout[i].south, &roomlayout[i].east, &roomlayout[i].west);
    }

    /*Print the room data*/
    for (int i = 0; i < numOfRooms; i++) {
        printf("%d, %d, %d, %d, %d", roomlayout[i].cleanliness, roomlayout[i].north, roomlayout[i].south, roomlayout[i].east, roomlayout[i].west);
    }

    /*THe number of animals*/
        printf("\nEnter the amount of creatures: ");
        scanf("%d", &numOfCreatures);

    /*The type of creature + location*/
    struct Creatures creature[numOfCreatures];
    for (int i = 0; i < numOfCreatures; i++) {
        printf("\nEnter the creatureType and location: ");
        scanf("%d %d", &creature[i].type, &creature[i].location);
        printf("%d, %d", creature[i].type, creature[i].location);
    }

    /* Based on the creature location, maybe put the creature in the correct room*/


    /*Let the game begin*/

    char input[20];

    while(1) {
        printf("\nEnter a command: ");
        scanf("%s", input);

        /*switch to case statement at the end*/
        if (strcmp(input, "look") == 0) {
            look(roomlayout, creature);
        }

        else if (strcmp(input, "clean") == 0) {
            printf("no");
        }

        else if (strcmp(input, "dirty") == 0) {
            printf("dirty");
        }

        else if (strcmp(input, "east") == 0) {
            printf("east");
        }

        else if (strcmp(input, "west") == 0) {
            printf("west");

        }

        else if (strcmp(input, "north") == 0) {
            printf("north");
        }

        else if (strcmp(input, "south") == 0) {
            printf("south");
        }

        else if (strcmp(input, "exit") == 0) {
            printf("Goodbye!");
            break;
        }

    }

    return 0;
}

void look(struct Room *roomlayout, struct Creatures *creature) { /* how do i print the index of the roomlayout*/

    // printf("don't forget the room number %d %d %d, neighbors to the %s", roomlayout->cleanliness, roomlayout->creature.type, roomlayout->creature.location, roomlayout->north);   
}

void clean(struct Room *roomlayout) {
    if (roomlayout->cleanliness == 2) { /* if its dirty, make it half dirty, remember the respect system*/
        roomlayout->cleanliness = 1;
    } else if (roomlayout->cleanliness == 1) { /* if it's half-dirty, make it clean*/
        roomlayout->cleanliness = 0;
    } printf("Your room is already clean!")
}

void dirty() {
    
}

void checkCreatureEmotion() {

}
