/**
 * menu.h
 * Defines functions for menu operations
 * Brett Haensgen
 * 9/30/2025
 * gcc main.c function.c menu.c -o output
 */

void list(vector list[]);
int addvect(vector list[]);
int findvect(vector list[], char* c);
void clear(vector list[]);
void help(void);
void printvector(vector v);