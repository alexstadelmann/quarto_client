#ifndef respHn
#define respHn

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "handleRequest.h"
#include "header.h"

//extern keyword nicht notwendig
extern char *game_id;
extern char *player_number;
int step;                       //Wächter, dass kein Schritt übersprungen wurde

char *handle(char *request);

#endif
