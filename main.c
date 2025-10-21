/**
 * main.c
 * Limited vector calculator in 3D space
 * Brett Haensgen
 * 9/30/2025
 * gcc main.c function.c menu.c -o output
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "function.h"
#include "menu.h"

#define VLIST_LENGTH 10

int main(void) {
    // Stores the vector list
    vector vlist[VLIST_LENGTH]; //malloc, keep track of length and pass that around with ptr
    clear(vlist); // may still want clear but different versions - one to handle after malloc/realloc, one for free (empty?)

    // Stores user input
    char user_in[100];
    char* t1;
    char* t2;
    char* t3;
    char* t4;
    char* t5;

    // Boolean that keeps program running until quit
    bool quit = false;

    // Repeats calculator functionality
    while(!quit) {
        printf("vect_calc> ");
        fgets(user_in, 100, stdin);

        // Trim new line character
        user_in[strcspn(user_in, "\n")] = '\0';

        // Pull apart user input
        t1 = strtok(user_in, " ");
        t2 = strtok(NULL, " ");
        t3 = strtok(NULL, " ");
        t4 = strtok(NULL, " ");
        t5 = strtok(NULL, " ");

        // Trim apostrophe from each token
        char *tokens[] = {t1, t2, t3, t4, t5};
        for (int i = 0; i < 5; i++) {
            if (tokens[i] != NULL) {
                tokens[i][strcspn(tokens[i], ",")] = '\0';
            }
        }

        if(strcmp(t1, "quit") == 0) {
            // Quit option
            quit = true;
            printf("Goodbye\n");
        } else if(strcmp(t1, "list") == 0) {
            // List vectors menu option
            list(vlist);
        } else if(strcmp(t1, "clear") == 0) {
            // Clear list menu option
            clear(vlist);
        } else if(strcmp(t1, "help") == 0) {
            // Help statement menu option
            help();
        } else if(strcmp(t1, "fill") == 0) {
            // Fill list menu option
            fill(vlist);
        } else if(t2 != NULL && strcmp(t1, "save") == 0) {
            // Save to .csv menu option
            save(t2, vlist);
        } else if(t2 != NULL && strcmp(t1, "load") == 0) {
            // Load .csv menu option
            load(t2, vlist);
        } else if(t2 == NULL && findvect(vlist, t1) != -1) {
            // Single vector input print
            printvector(vlist[findvect(vlist, t1)]);
        } else if(t2 == NULL) {
            // If no other single word commands worked, print error
            printf("Error on input: command doesn't exist\n");
        } else {
            // If equal sign in equation
            if(strcmp(t2, "=") == 0) {
                // Try to find vector in list
                int vect_pos = findvect(vlist, t1);

                // If vector does not exist in list add it
                if(vect_pos == -1) {
                    vect_pos = addvect(vlist);

                    // Print error if list is full
                    if(vect_pos == -1) {
                        printf("Error in adding vector: list full\n");

                    // Add vector to open position
                    } else {
                        vector result;
                        strcpy(result.name, t1);
                        vlist[vect_pos] = result;
                    }
                } 

                // If vector was found or added properly, continue to operand checking
                if(vect_pos != -1) {
                    // Assigning vector with 2 floats
                    if(isFloat(t3) && isFloat(t4) && t5 == NULL) {
                        vlist[vect_pos].x = strtof(t3, NULL);
                        vlist[vect_pos].y = strtof(t4, NULL);
                        vlist[vect_pos].z = 0;
                        printvector(vlist[vect_pos]);

                    // Assigning vector with 3 floats
                    } else if(isFloat(t3) && isFloat(t4) && isFloat(t5)) {
                        vlist[vect_pos].x = strtof(t3, NULL);
                        vlist[vect_pos].y = strtof(t4, NULL);
                        vlist[vect_pos].z = strtof(t5, NULL);
                        printvector(vlist[vect_pos]);
                    
                    // Go into function to calculate vector result and put result in list
                    } else {
                        vector result = function(t3, t5, t4, vlist);

                        // Check if vector calculation was successful (error vectors have null character name)
                        if(result.name[0] != '\0') {
                            vlist[vect_pos].x = result.x;
                            vlist[vect_pos].y = result.y;
                            vlist[vect_pos].z = result.z;
                            printvector(vlist[vect_pos]);
                        }
                    }
                }

            // No equal sign in equation
            } else {
                // Check for dot product
                if(strcmp(t2,".") == 0) {
                    int v1_pos = findvect(vlist, t1);
                    int v3_pos = findvect(vlist, t3);

                    // If either vector does not exist in list
                    if(v1_pos == -1 || v3_pos == -1) {
                        printf("Error in finding vector: does not exist\n");

                    // Print the dot product as a float
                    } else {
                        double d = dot(vlist[v1_pos], vlist[v3_pos]);
                        printf("%f\n", d);
                    }
                
                    // Go into function to calculate vector result and print result
                } else {
                    vector result = function(t1, t3, t2, vlist);

                    // Check if vector calculation was successful (error vectors have null character name)
                    if(result.name[0] != '\0') {
                        strcpy(result.name, "ans");
                        printvector(result);
                    }
                }
            }
        }
    }
    
    return 0;
}