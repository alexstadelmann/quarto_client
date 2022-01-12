#include <stdio.h>    //for printf and fprintf
#include <stdlib.h>   //for macros like EXIT_SUCCESS
#include <unistd.h>   //for getopt
#include <sys/wait.h>

#ifndef header
#define header


#include <stdbool.h>  // for true and false
#include <ctype.h>   //for isdigit and isalphanum
#include <string.h> //for strcpy
#include <math.h>


//global definitions:
#define GAMEKINDNAME "Quarto"
#define PORTNUMBER 1357
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"
#define ID_LEN 13
#define BUFFERLENGTH 512
#define BUFFERLENGTH_PORT 6 //gegebenenfalls aendern
#define REQUESTSLENGTH 64 // maximum number of consecutive lines send by the server and stored in one buffer. 
#define OUR_VERSION "2.3"
#define VERSION_LEN 16
#define NAME_LEN 64


//The following functions are defined in helperFunctions.c
void print_instructions(); 
bool is_valid_id(char *); 
bool is_valid_player_number(char *); 
bool is_valid_file(char *arg, char *string);
void print_id(char *, int);
int recv_all(int, char *, size_t);
void print_board(int, int [4][4]);
char* intToBinary(int);


//Fuction from board.c
bool recv_board(char*);

//Function from thinker.c
void calculateMove();
void chooseNextOpponentPiece();
int freeFieldsSearch();
void insertCoordinates(int);
void insertNextMove();
int freeFieldsSearch();

//declare important variables
  char game_id[ID_LEN + 1];
  char player_number[2];
  char player_name[NAME_LEN + 1];
  char cip_version[VERSION_LEN + 1];

//Variables from the game phase:
int moveTime;
int board[4][4];
int width;
int height;
int winner;
char winnerName[126];
int nextPiece;
int freePieces[16];
int nextOpponentPiece;
char nextMove[16];
int freeFields[16];
char nextCoordinates[2];


#endif
