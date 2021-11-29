#ifndef respHn
#define respHn

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "handleRequest.h"
#include "header.h"


extern char* game_id;
extern int player_number;
int step;                       //Wächter, dass kein Schritt übersprungen wurde

char *handle(char *request);

#endif
