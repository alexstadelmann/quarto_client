#include <stdio.h>    //for printf and fprintf
#include <stdlib.h>   //for rand und macros like EXIT_SUCCESS
#include <unistd.h>   //for getopt
#include <stdbool.h>  // for true and false
#include <ctype.h>   //for isdigit and isalphanum
#include <time.h>   //for srand(time(NULL))
#include <string.h> //for strcpy


//global definitions:
#define GAMEKINDNAME "Quarto"
#define PORTNUMBER 1357
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"
#define ID_LEN 13
#define BUFFERLENGTH 128
#define REQUESTSLENGTH 5 // maximum number of consecutive lines send by the server and stored in one buffer. 
#define OUR_VERSION "2.3"
#define VERSIONLENGTH 16
#define NAME_LEN 64

//important parameters of the game:
char *game_id;
char *player_number;
char *player_name;
char *cip_version;

//The following functions are defined in helperFunctions.c
void print_instructions(); 
bool is_valid_id(char *); 
bool is_valid_player_number(char *); 
void print_id(char *, int);
int recv_all(int sockfd, char *buf, size_t len);
void extract_regex(const char *string, char *pattern, char *dest);



