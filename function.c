/**
 * function.c
 * Functions for vector calculator
 * Brett Haensgen
 * 9/30/2025
 * gcc main.c function.c menu.c -o output
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "vector.h"
#include "function.h"
#include "menu.h"

// Add two vectors function
vector add(vector a, vector b) {
    vector c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;

    return c;
}

// Subtract two vectors function
vector subtract(vector a, vector b) {
    vector c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;

    return c;
}

// Scale a vector function
vector scalar(vector a, float b) {
    vector c;
    c.x = a.x * b;
    c.y = a.y * b;
    c.z = a.z * b;

    return c;
}

// Dot product of two vectors function
double dot(vector a, vector b) {
    double result = 0;
    result = result + (a.x * b.x);
    result = result + (a.y * b.y);
    result = result + (a.z * b.z);

    return result;
}

// Cross product of two vectors function
vector cross(vector a, vector b) {
    vector c;
    c.x = (a.y * b.z) - (a.z * b.y);
    c.y = (a.z * b.x) - (a.x * b.z);
    c.z = (a.x * b.y) - (a.y * b.x);

    return c;
}

// Selects which operationn should be done if valid
vector function(char *v1, char *v2, char *operand, vector vlist[]) {
    // Creates blank vector result
    vector result = { .x = 0, .y = 0, .z = 0 };

    // Checks for scalar operator
    if(strcmp(operand,"*") == 0) {
        if(!isFloat(v1)) {
            if(!isFloat(v2)) {
                // If neither input is a scalar, print error and assign null character error name
                printf("Error on input: illegal expression\n");
                result.name[0] = '\0';
            } else {
                // v2 is the scalar
                int v1_pos = findvect(vlist, v1);

                // If vector is not found, print error and assign null character error name
                if(v1_pos == -1) {
                    printf("Error in finding vector: does not exist\n");
                    result.name[0] = '\0';
                } else {
                    // Scalar operation
                    result = scalar(vlist[v1_pos], strtof(v2, NULL));
                }
            }
        } else {
            // v1 is the scalar
            int v2_pos = findvect(vlist, v2);

            // If vector is not found, print error and assign null character error name
            if(v2_pos == -1) {
                printf("Error in finding vector: does not exist\n");
                result.name[0] = '\0';
            } else {
                // Scalar operation
                result = scalar(vlist[v2_pos], strtof(v1, NULL));
            }
        }
    
    // Checks for other possible operators
    } else if(strcmp(operand,"-") == 0 || strcmp(operand,"+") == 0 || strcmp(operand,"x") == 0) {
        // Finds the two inputted vectors
        int v1_pos = findvect(vlist, v1);
        int v2_pos = findvect(vlist, v2);

        // If vectors are not found, print error and assign null character error name
        if(v1_pos == -1 || v2_pos == -1) {
            printf("Error in finding vector: does not exist\n");
            result.name[0] = '\0';
        } else {
            // Subtraction operation
            if(strcmp(operand,"-") == 0) {
                result = subtract(vlist[v1_pos], vlist[v2_pos]);

            // Addition operation
            } else if(strcmp(operand,"+") == 0) {
                result = add(vlist[v1_pos], vlist[v2_pos]);

            // Cross product operation
            } else if(strcmp(operand,"x") == 0) {
                result = cross(vlist[v1_pos], vlist[v2_pos]);
            } 
        }
    
    // If no legal operators were inputted, print error message and assign null charactor error name
    } else {
        printf("Error on input: illegal operation\n");
        result.name[0] = '\0';
    }

    return result;
}

// Checks if the passed string is a float
bool isFloat(char *str) {
    char *endptr;
    strtof(str, &endptr);
    return endptr != str && *endptr == '\0';
}