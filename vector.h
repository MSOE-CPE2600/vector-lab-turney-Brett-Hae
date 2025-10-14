/**
 * vector.h
 * Structure for vectors used by calculator
 * Brett Haensgen
 * 9/30/2025
 * gcc main.c function.c menu.c -o output
 */

typedef struct {
    char name[10];
    double x;
    double y;
    double z;
} vector;