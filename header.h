#include <stdio.h>    //for printf and fprintf
#include <stdlib.h>   //for rand und macros like EXIT_SUCCESS
#include <unistd.h>   //for getopt
#include <stdbool.h>  // for true and false
#include <ctype.h>   //for isdigit and isalphanum
#include <time.h>   //for srand(time(NULL))
#include <string.h> //for strcpy



#define GAMEKINDNAME "Quarto"
#define PORTNUMBER 1357
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"
#define ID_LEN 13

//The following functions are defined in helperFunctions.c
void print_instructions(); 
bool is_valid_id(char *); 
bool is_valid_player_number(char *); 
void id_init(char *, int); 
void print_id(char *, int);



