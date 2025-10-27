/**
 * menu.h
 * Defines functions for menu operations
 * Brett Haensgen
 * 9/30/2025
 * gcc main.c function.c menu.c -o output
 */

void list(vector *list, int size);
vector* addvect(vector *list, int *size, vector v);
int findvect(vector *list, char* c, int size);
vector* clear(vector *list, int *size);
void help(void);
void printvector(vector v);
int load(char filename[], vector **list, int *size);
int save(char* filename, vector *list, int size);
void checkExtension(char* filename);
vector* fill(vector *list, int *size, int count);