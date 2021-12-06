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
#define BUFFERLENGTH 128
#define REQUESTSLENGTH 5                          //Buffer beim einlesen, ggf anpassen
#define VERSION "2.3"

//Spielernummer wird von optarg jetzt als char eingelesen statt int
char *game_id;
char *player_number;

//The following functions are defined in helperFunctions.c
void print_instructions(); 
bool is_valid_id(char *); 
bool is_valid_player_number(char *); 
void print_id(char *, int);
int recv_all(int sockfd, char *buf, size_t len);



