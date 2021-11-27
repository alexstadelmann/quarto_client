#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <ranlib.h>
#include <time.h>
#include <string.h>



#define POSIXLY_CORRECT 1
#define GAMEKINDNAME "Quarto"
#define PORTNUMBER 1357
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"
#define ID_LEN 13

//The following functions are defined in helperFunctions.c
void printInstructions(); 
bool isValidId(char *); 
bool isValidPlayerNum(char *); 
void idInit(char *, int); 
void printId(char *, int);



