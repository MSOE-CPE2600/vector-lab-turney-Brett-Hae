/**
 * menu.h
 * Menu functions for vector calulator
 * Brett Haensgen
 * 9/30/2025
 * gcc main.c function.c menu.c -o output
 */

#include <stdio.h>
#include <string.h>
#include "vector.h"

#define VLIST_LENGTH 10

// list out all vectors stored in list
void list(vector list[]){
    for(int i = 0; i < VLIST_LENGTH; i++) {
        if(list[i].name[0] != '\0') {
            printf("%s = %f, %f, %f\n", list[i].name, list[i].x, list[i].y, list[i].z);
        }
    }
}

// Return 0-9 for vector position or -1 for full list
int addvect(vector list[]) {
    for(int i = 0; i < VLIST_LENGTH; i ++) {
        if(strcmp(list[i].name, "\0") == 0) {
            return i;
        }
    }
    return -1;
}

// Return 0-9 for vector position or -1 for not in list
int findvect(vector list[], char* c) {
    for(int i = 0; i < VLIST_LENGTH; i ++) {
        if(strcmp(list[i].name, c) == 0) {
            return i;
        }
    }
    return -1;
}

// Clear out vector list
void clear(vector list[]) {
    vector v;
    v.name[0] = '\0';
    v.x = 0;
    v.y = 0;
    v.z = 0;
    for(int i = 0; i < VLIST_LENGTH; i ++) {
        list[i] = v;
    }
}

// Prints out guide to calculator functions (had to delete spaces because they would print)
void help(void) {
    printf("INSTRUCTIONS\n\
    List: prints out all the vectors stored in the list\n\
    Clear: removes all vectors stored in the list\n\
    Quit: exit the calculator program\n\
    Help: prints out all possible commands\n\
CALCULATOR COMMANDS\n\
    V1 : prints out singular vector\n\
    V1 = F F F : assigns vector with three floats\n\
    V1 = F F : assigns vector with two floats (third will be set to 0)\n\
    V2 OP V3 : does operation on two vectors and prints as temporary answer vector\n\
    V1 = V2 OP V3 : does operation on two vectors and saves to vector list\n\
VALID OPERATIONS\n\
    + : adds two vectors\n\
    - : subtracts two vectors\n\
    x : cross product of two vectors\n\
    . : dot product of two vectors (calculates a double, only V2 OP V3 is valid)\n\
    * : scalar of a vector (V2 or V3 can be a float)\n");
}

// Prints out single vector
void printvector(vector v) {
    printf("%s = %f, %f, %f\n", v.name, v.x, v.y, v.z);
}