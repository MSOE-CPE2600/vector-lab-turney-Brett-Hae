# Basic Summary
Calculator specifically designed for 3D vectors.
Provides some extra functionality on top of calculator like file IO and random vector generation.

# Build Instructions
Build with `make` or `gcc main.c function.c menu.c -c -lc -Wall -g -o vectorlab`

# Memory Usage
Uses dynamically allocated memory that reallocates each time a vector is added to the list.
Clear and quit will free the memory deleting all the vectors.
Load calls the clear function first to give a clean list of the new vectors.

# Help Menu (also built into the caluculator):
>**MENU INSTRUCTIONS**
>    - List: prints out all the vectors stored in the list
>    - Clear: removes all vectors stored in the list
>    - Fill: adds randomly generated vectors to the vector list
>    - Load: loads vectors from a .csv file to the vector list
>    - Save: saves the vector list to a .csv file
>    - Quit: exit the calculator program
>    - Help: prints out all possible commands

>**CALCULATOR COMMANDS**
>    - V1 : prints out singular vector
>    - V1 = F F F : assigns vector with three floats
>    - V1 = F F : assigns vector with two floats (third will be set to 0)
>    - V2 OP V3 : does operation on two vectors and prints as temporary answer vector
>    - V1 = V2 OP V3 : does operation on two vectors and saves to vector list

>**VALID OPERATIONS**
>    - (+) : adds two vectors
>    - (-) : subtracts two vectors
>    - (x) : cross product of two vectors
>    - (.) : dot product of two vectors (calculates a double, only V2 OP V3 is valid)
>    - (*) : scalar of a vector (V2 or V3 can be a float)