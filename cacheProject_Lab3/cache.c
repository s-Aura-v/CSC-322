//
// Created by Saurav Lamichhane on 10/24/23.
//

#include <stdbool.h>
#include <printf.h>
#include <stdlib.h>
#include <math.h>
#include <libc.h>

typedef struct {
    int valid;
    int tag;
    int amntUsed;              //LFU requires you to remove the value that is used the least
    int cycleCounter;           //LRU requires you to remove the value that is the oldest in the timeline
} CacheLine;

typedef struct {
    int numberOfLines;
    CacheLine** cacheLine;
} CacheSet;

//Globals
double totalMiss = 0;
double totalCycles = 0;
char policy = 'F'; //F for LFU and R for LRU
int hitTime = 0;
int missPenalty = 0;
char* binaryAddress;



//Prototypes
void cacheSimulation(CacheLine **cache, int S, int E, int B, int m, int s, int b, int t, char input[]);
void hexToBinary(char memoryAddress[]);

int main() {
    //Necessary variables
    int S;
    int E;
    int B;
    int m;

    //Initialize the variables
    printf("Enter the number of sets (S): \n");
    scanf("%d", &S);
    printf("Enter the number of lines per set (E): \n");
    scanf(" %d", &E);
    printf("Enter the block size (B): \n");
    scanf("%d", &B);
    printf("Enter the number of physical memory bits (m): \n");
    scanf("%d", &m);
    printf("Choose a policy: [LFU or LRU]: \n");
    //this sets the m to 0 for some reason, relating to s and d error \0
    char temp[4];
    scanf("%s", temp);
    policy = temp[1];
    printf("Enter the hit time: \n");
    scanf("%d", &hitTime);
    printf("Enter the miss penalty: \n");
    scanf("%d", &missPenalty);

    //Calculated Cache Values
    // (t = m - (b + s)) - Tag
    // b = log(2) (m) - Offset
    // s = log2 (S) -
    int s = log2(S);
    int b = log2(m);
    int t = m - (b + s);

    //Create the cache
    CacheLine ** cache = malloc(S * sizeof(CacheLine **));
    for (int i = 0; i < E; i++) {
        cache = malloc(E * sizeof(CacheLine **));
    }
    //BROKEN CODE
//    //Set Variable
//    for (int i = 0; i < S; i++) {
//        for (int j = 0; j < E; j++) {
//            cache[i][j].valid = 0;
//            cache[i][j].tag = 0;
//            cache[i][j].amntUsed = 0;
//            cache[i][j].cycleCounter = 0;
//        }
//    }

    //Get the inputs
    char input[64];
    while (atoi(input) != -1) {
        scanf("%s", &input);        //just remember the input is strings for now; convert it to binary later
        printf("Input: %s\n", input);
        if (atoi(input) != -1) {
            cacheSimulation(cache, S, E, B, m s, b, t, input);
        }
    }

}

void cacheSimulation(CacheLine **cache, int S, int E, int B, int m, int s, int b, int t, char input[]) {
    //apply masks so that you can sort and replace things
    //mask - string of binary stuff
    //  do bitwise operations
    // binary list of 1: you can and it aganist some other number, anything

    //1. Convert hex to binary
    hexToBinary(input);
    printf("%s\n", binaryAddress);

    //2. Get Set ID
    char * setID = malloc(20 * sizeof(char *));  //20 is temporary value for now
    //start from substring and go to the end and set it as setID
    int binaryCounter = strlen(binaryAddress) - 1 - b;
    strcat(setID, &binaryAddress[binaryCounter]); /

    //3. Tag Number
    char * tagNum = malloc(50 * sizeof (char *)); //50 temp
    binaryCounter = strlen(binaryAddress) - 1 - (s +b);

    printf("BinAdd: %s\n", binaryAddress);
    printf("TempAdd: %s", setID);

    //4. Do the simulation

    bool complete = false;
    int currentCycle = 0;

    while (complete == false) {
        bool lineExist = false;
        totalCycles += hitTime;
        totalCycles += 1;

        for (int i = 0; i < S; i++) {
            if (lineExist == true) {
                break;
            }
            if (cache[][] == setID)


        }

        complete = true;
    }
    //Body
}


void hexToBinary(char memoryAddress[]) {
    binaryAddress = malloc(100* sizeof (char*));
    for (int i = 0; memoryAddress[i] != '\0'; i++) {
        switch (memoryAddress[i]) {
            case '0':
                strcat(binaryAddress, "0000");
                break;
            case '1':
                strcat(binaryAddress, "0001");
                break;
            case '2':
                strcat(binaryAddress, "0010");
                break;
            case '3':
                strcat(binaryAddress, "0011");
                break;
            case '4':
                strcat(binaryAddress, "0100");
                break;
            case '5':
                strcat(binaryAddress, "0101");
                break;
            case '6':
                strcat(binaryAddress, "0110");
                break;
            case '7':
                strcat(binaryAddress, "0111");
                break;
            case '8':
                strcat(binaryAddress, "1000");
                break;
            case '9':
                strcat(binaryAddress, "1001");
                break;
            case 'a':
                strcat(binaryAddress, "1010");
                break;
            case 'b':
                strcat(binaryAddress, "1011");
                break;
            case 'c':
                strcat(binaryAddress, "1100");
                break;
            case 'd':
                strcat(binaryAddress, "1101");
                break;
            case 'e':
                strcat(binaryAddress, "1110");
                break;
            case 'f':
                strcat(binaryAddress, "1111");
                break;
        }
    }
}

