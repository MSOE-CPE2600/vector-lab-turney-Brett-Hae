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
#include "menu.h"

#define VLIST_LENGTH 10
#define INPUT_LENGTH 50

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
    Fill: adds randomly generated vectors to the vector list\n\
    Load: loads vectors from a .csv file to the vector list\n\
    Save: saves the vector list to a .csv file\n\
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

// Loads a .csv file to the vector list
int load(char* filename, vector list[]) {
    char name[INPUT_LENGTH];
    strcpy(name, filename);
    checkExtension(name);

    FILE *fptr;
    fptr = fopen(name, "r");
    if(!fptr) {
        perror("Error opening file for writing");
        return 1;
    }
    
    char line[INPUT_LENGTH];

    // Read each line
    while (fgets(line, INPUT_LENGTH, fptr)) {
        vector v;
        line[strcspn(line, "\n")] = '\0';
        if (sscanf(line, "%[^,],%lf,%lf,%lf", v.name, &v.x, &v.y, &v.z) == 4) {
            int pos = addvect(list);
            if(pos == -1) {
                printf("Error in adding vector: list full\n");
            } else {
                list[pos] = v;
            }
        } else {
            printf("Error in adding vector: line read failed\n");
        }
    }

    
    fclose(fptr);
    return 0;
}

// Saves a vector list to a .csv file
int save(char* filename, vector list[]) {
    char name[INPUT_LENGTH];
    strcpy(name, filename);
    checkExtension(name);

    FILE *fptr;
    fptr = fopen(name, "w");
    if(!fptr) {
        perror("Error opening file for writing");
        return 1;
    }

    for(int i = 0; i < VLIST_LENGTH; i++) {
        if(list[i].name[0] != '\0') {
            fprintf(fptr, "%s,%f,%f,%f \n", list[i].name, list[i].x, list[i].y, list[i].z);
        }
    }

    fclose(fptr);
    return 0;
}

// Ensures filename ends with ".csv"
void checkExtension(char* filename) {
    const char* dot = strrchr(filename, '.');

    if (!dot || strcmp(dot, ".csv") != 0) {
        strcat(filename, ".csv");
    }
}

// Fill out the list with randomly generated vectors
int fill(vector list[]) {
    return 0;
}