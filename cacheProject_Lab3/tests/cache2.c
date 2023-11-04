//
// Created by Saurav Lamichhane on 10/24/23.
//

#include <stdbool.h>
#include <printf.h>
#include <stdlib.h>
#include <math.h>
#include <libc.h>


int main() {
    //Get the inputs
    char strings[65]; // You can store up to 100 strings of up to 64 characters each (plus the null terminator)

    char recentInput[65];

    int stringCounter = 0;
    while (atoi(recentInput) != -1) {
        scanf("%s", &strings[stringCounter]);
        printf("%s", strings[stringCounter]);
        strcpy(recentInput, strings[stringCounter]);
        stringCounter++;
    }

    int arrayLength = sizeof(strings) / sizeof(strings[0]);
    for (int i = 0; i < arrayLength; i++ ) {
        printf("%s\n", strings[i]);
    }

    return 0;
}