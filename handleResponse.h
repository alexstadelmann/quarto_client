#ifndef respHn
#define respHn

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "handleRequest.h"
#include "header.h"


extern char* gameid;
extern int playerNumber;
int step;                       //Wächter, dass kein Schritt übersprungen wurde

char *handle(char *request);

#endif
