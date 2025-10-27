/**
 * function.h
 * Defines functions for the vector calculator
 * Brett Haensgen
 * 9/30/2025
 * gcc main.c function.c menu.c -o output
 */

#include <stdbool.h>

vector add(vector a, vector b);
vector subtract(vector a, vector b);
vector scalar(vector a, float b);
double dot(vector a, vector b);
vector cross(vector a, vector b);
vector function(char *v1, char *v2, char *operand, vector *vlist, int size);
bool isFloat(char *str);
int isNumber(char *token);