//
// Created by Saurav Lamichhane on 10/24/23.
//

#include <stdbool.h>
#include <printf.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int valid;
    int tag;
    int amntUsed;              //LFU requires you to remove the value that is used the least
    time_t timeUsed;           //LRU requires you to remove the value that is the oldest in the timeline
} CacheLine;

typedef struct {
    int numberOfLines;
    CacheLine** cacheLine;
} CacheSet;

typedef struct {
    int S;
    int E;
    int B;
    int m;
} Cache;


//Globals
int totalMiss = 0;
int totalCycles = 0;

//Prototypes
CacheLine **createCacheLine(int S, int E);
void cacheSimulation(CacheLine **cache);


int main() {
    //Necessary variables
    int S;
    int E;
    int B;
    int m;
    char policy; //F and R
    int hitTime;
    int missPenalty;

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
    scanf("%s", &policy);
    printf("Enter the hit time: \n");
    scanf("%d", &hitTime);
    printf("Enter the miss penalty: \n");
    scanf("%d", &missPenalty);

    //Store the inputs
    char input[2];
    while (atoi(input) != -1) {
        scanf("%s", &input);        //just remember the input is strings for now; convert it to hex later
        printf("%s\n", input);
    }

    //Calculated Cache Values
    // (t = m - (b + s)) - Tag
    // b = log(2) (m) - Offset
    // s = log2 (S) -
    int s = log2 (S);
    int b = log2 (m);
    int t = m - (b + s);

    //Create + Populate Cache
    CacheLine **cache = createCacheLine(S, E);
    cacheSimulation(cache);

}

void cacheSimulation(CacheLine **cache) {
    //Body
}

CacheLine **createCacheLine(int S, int E) {
    CacheLine ** cache = malloc(S * sizeof(CacheLine **));
    for (int i = 0; i < E; i++) {
        cache = malloc(E * sizeof(CacheLine **));
    }
    return cache;
}

int decToHex(int memoryAddress) {

}

