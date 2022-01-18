
//standard libraries that anyone could need
#include <stdio.h>    
#include <stdlib.h>   
#include <unistd.h>   
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>

#ifndef header
#define header

#include <sys/wait.h>




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


void thinker();

//The following functions are defined in helperFunctions.c
void print_instructions(); 
bool is_valid_id(char *); 
bool is_valid_player_number(char *); 
bool is_valid_file(char *arg, char *string);
void print_id(char *, int);
int recv_all(int, char *, size_t);
void print_board(int, int, int[4][4]);
char* intToBinary(int);
void print_cube();

//Variable for pipe
int pfds[2];


//Fuction from board.c
bool recv_board(char*);
void makeBinaryCube();

//variables for shared memory
int shmID_board;
int* shm_board_address;


//declare important variables
  char game_id[ID_LEN + 1];
  char player_number[2];
  char player_name[NAME_LEN + 1];
  char cip_version[VERSION_LEN + 1];

//Variables from the game phase:
int moveTime;
int board[4][4];
char cube[4][4][5];
int width;
int height;
int winner;
char winnerName[126];
int nextPiece;
int freePieces[16];
int nextOpponentPiece;
char nextMove[16];
int freeSquares[16];
int nextSquare;
char nextCoordinates[2];


#endif
