/**
 * menu.h
 * Menu functions for vector calulator
 * Brett Haensgen
 * 9/30/2025
 * gcc main.c function.c menu.c -o output
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"
#include "menu.h"

#define INPUT_LENGTH 50

// List out all vectors stored in list
void list(vector* list, int size){
    for(int i = 0; i < size; i++) {
        if(list[i].name[0] != '\0') {
            printf("%s = %f, %f, %f\n", list[i].name, list[i].x, list[i].y, list[i].z);
        }
    }
}

// Adds a vector to the list
vector* addvect(vector* list, int* size, vector v) {
    vector* temp = realloc(list, (*size + 1) * sizeof(vector));
    if (!temp) {
        printf("Error in adding vector: memory allocation failed\n");
        return list;
    }

    list = temp;
    list[*size] = v;
    (*size)++;
    return list;
}

// Return number for vector position or -1 for not in list
int findvect(vector* list, char* c, int size) {
    for(int i = 0; i < size; i ++) {
        if(strcmp(list[i].name, c) == 0) {
            return i;
        }
    }
    return -1;
}

// Clear out vector list
vector* clear(vector *list, int *size) {
    free(list);
    list = NULL;
    (*size) = 0;
    return list;
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
int load(char* filename, vector **list, int *size) {
    // Tkaes in name and checks for extenson
    char name[INPUT_LENGTH];
    strcpy(name, filename);
    checkExtension(name);

    // Opens file
    FILE *fptr;
    fptr = fopen(name, "r");
    if(!fptr) {
        perror("Error in opening file: file not found");
        return 1;
    }

    // Cleans the list out before adding the new vectors
    *list = clear(*list, size);
    
    char line[INPUT_LENGTH];

    // Read each line for vectors preformatted
    while (fgets(line, INPUT_LENGTH, fptr)) {
        vector v;
        line[strcspn(line, "\n")] = '\0';
        if (sscanf(line, "%[^,],%lf,%lf,%lf", v.name, &v.x, &v.y, &v.z) == 4) {
            *list = addvect(*list, size, v);
        } else {
            printf("Error in adding vector: line read failed\n");
        }
    }
    
    fclose(fptr);
    return 0;
}

// Saves a vector list to a .csv file
int save(char* filename, vector *list, int size) { 
    // Takes in name and checks for extension
    char name[INPUT_LENGTH];
    strcpy(name, filename);
    checkExtension(name);

    // Opens file
    FILE *fptr;
    fptr = fopen(name, "w");
    if(!fptr) {
        perror("Error in opening file: file not found");
        return 1;
    }

    // Saves all the vectors from the list to the file
    for(int i = 0; i < size; i++) {
        if(list[i].name[0] != '\0') {
            fprintf(fptr, "%s,%f,%f,%f \n", list[i].name, list[i].x, list[i].y, list[i].z);
        }
    }

    fclose(fptr);
    return 0;
}

// Ensures filename ends with ".csv"
void checkExtension(char* filename) {
    char* dot = strrchr(filename, '.');

    if (!dot || strcmp(dot, ".csv") != 0) {
        strcat(filename, ".csv");
    }
}

// Fill out the list with randomly generated vectors - partial credit to google
vector* fill(vector *list, int *size, int count) {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < count; i++) {
        vector v;
        snprintf(v.name, sizeof(v.name), "V%d", *size + 1);
        v.x = (rand() % 2001 - 1000) / 10.0; // Random double between -100.0 and +100.0
        v.y = (rand() % 2001 - 1000) / 10.0;
        v.z = (rand() % 2001 - 1000) / 10.0;

        list = addvect(list, size, v);
    }

    return list;
}