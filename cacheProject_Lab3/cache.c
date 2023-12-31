//
// Created by Saurav Lamichhane on 10/24/23.
// Note: Use: gcc -o a.out cache.c -lm to compile!
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int valid;
    int tag;
    int setNumber;
    int amntUsed;              //LFU - least accessed
    int cycleCounter;           //LRU - oldest in timeline
} CacheLine;

//Globals
double totalMiss = 0;
double totalCycles = 0;
double totalRuns = 0;
char policy = 'F'; //F for LFU and R for LRU
int hitTime = 0;
int missPenalty = 0;
char* binaryAddress;
char setID[64];
char tagStr[64];

//Prototypes
void cacheSimulation(CacheLine **cache, int S, int E, int s, int b, int t, char input[]);
void hexToBinary(char memoryAddress[]);
int binaryToInt(char* setID);

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
    int s = (int) log2 ((double) S);
    int b = (int) log2 ((double) B);
    int t = m - (b + s);

    //Create the cache
    CacheLine ** cache = malloc(S * sizeof(CacheLine *));
    for (int i = 0; i < S; i++) {
        cache[i] = malloc(E * sizeof(CacheLine));
    }

    //Set Variable
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < E; j++) {
            cache[i][j].valid = 0;
            cache[i][j].tag = 0;
            cache[i][j].setNumber = i; //i = rows
            cache[i][j].amntUsed = 0;
            cache[i][j].cycleCounter = 0;
        }
    }

    //Get the inputs
    char input[65];
    strcpy(input, "placeholder");
    while (atoi(input) != -1) {
        scanf("%s", input);
        if (atoi(input) != -1) {
            cacheSimulation(cache, S, E, s, b, t, input);
        }
    }

    //Final Calculations:
    int missRate = round((totalMiss/totalRuns) * 100);
    printf("%d %d\n", missRate, (int) totalCycles);

    //Free Memories
    for (int i = 0; i < S; i++) {
        free(cache[i]);
    }
    free(cache);
}

void cacheSimulation(CacheLine **cache, int S, int E, int s, int b, int t, char input[]) {
    binaryAddress = malloc(260 * sizeof (char*));
    binaryAddress[0] = '\0';

    //1. Convert hex to binary: complete
    hexToBinary(input);

    //2. Get Set ID: complete
    strncpy(setID, binaryAddress + t, s);
    int setNum = binaryToInt(setID);

    //3. Tag Number: complete
    int binaryEnd = strlen(binaryAddress) - (s + b);
    strncpy(tagStr, binaryAddress, binaryEnd);
    int tagNum = binaryToInt(tagStr);

    //4. Do the simulation
    bool complete = false;
    totalRuns += 1;

    //Check if bits/tags exists
    bool validBitExists = false;
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < E; j++) {
            //No need to continue after finding a hit;
            //1. Assuming it is in the cache: ValidBit exists and TagExists
            if (cache[i][j].setNumber == setNum) {
                if (cache[i][j].valid == 1) {
                    validBitExists = true;
                    if (cache[i][j].tag == tagNum) {
                        totalCycles += hitTime;
                        cache[i][j].cycleCounter = totalCycles;

                        printf("%s H\n", input);
                        complete = true;
                        break;
                    }
                }
            }
        }
    }

    //1: Assume that validBit does not exist.
    bool roomAdded = false;
    if (complete == false) {
        if (validBitExists == false) {
            for (int i = 0; i < S; i++) {
                for (int j = 0; j < E; j++) {
                    if (cache[i][j].setNumber == setNum) {
                        //1. There is room for the address
                        if (cache[i][j].valid == 0 && roomAdded == false) {
                            totalMiss++;
                            totalCycles += missPenalty + hitTime;

                            cache[i][j].valid = 1;
                            cache[i][j].tag = tagNum;
                            cache[i][j].cycleCounter = totalCycles;
                            cache[i][j].amntUsed++;

                            printf("%s M\n", input);
                            roomAdded = true;
                            complete = true;
                        }
                    }
                }
            }
        }
    }

    //2. Assume that validBit does exist and the tag does not match. Evict!
    roomAdded = false;
    //a. Find the least used
    if (complete == false) {
        int leastUsed = 10000;
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < E; j++) {
                if (cache[i][j].setNumber == setNum) {
                    int challenger = cache[i][j].amntUsed;
                    if (challenger < leastUsed) {
                        leastUsed = challenger;
                    }
                }
            }
        }
        //b. Find the oldest in the time-line
        int leastCycles = 10000;
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < E; j++) {
                if (cache[i][j].setNumber == setNum) {
                    int challenger = cache[i][j].cycleCounter;
                    if (challenger < leastCycles) {
                        leastCycles = challenger;
                    }
                }
            }
        }
        //c. Compare and Evict!
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < E; j++) {
                if (policy == 'F') {
                    if (cache[i][j].setNumber == setNum) {
                        if (cache[i][j].amntUsed == leastUsed && roomAdded == false) {
                            //evict!
                            totalMiss++;
                            totalCycles += missPenalty + hitTime;

                            cache[i][j].tag = tagNum;
                            cache[i][j].cycleCounter = totalCycles;

                            printf("%s M\n", input);
                            roomAdded = true;
                            complete = true;
                        }
                    }
                } else { //LRU
                    if (cache[i][j].setNumber == setNum) {
                        if (cache[i][j].cycleCounter == leastCycles && roomAdded == false) {
                            //evict!

                            totalMiss++;
                            totalCycles += missPenalty + hitTime;

                            cache[i][j].tag = tagNum;
                            cache[i][j].cycleCounter = totalCycles;


                            printf("%s M\n", input);
                            roomAdded = true;
                            complete = true;
                        }
                    }
                }
            }
        }
    }
    //End the simulation
    free(binaryAddress);
}

void hexToBinary(char memoryAddress[]) {
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
            case 'A':
                strcat(binaryAddress, "1010");
                break;
            case 'b':
            case 'B':
                strcat(binaryAddress, "1011");
                break;
            case 'c':
            case 'C':
                strcat(binaryAddress, "1100");
                break;
            case 'd':
            case 'D':
                strcat(binaryAddress, "1101");
                break;
            case 'e':
            case 'E':
                strcat(binaryAddress, "1110");
                break;
            case 'f':
            case 'F':
                strcat(binaryAddress, "1111");
                break;
        }
    }
}

int binaryToInt(char* setID) {
    int binary = (int) strtol(setID, NULL, 2);
    return binary;
}