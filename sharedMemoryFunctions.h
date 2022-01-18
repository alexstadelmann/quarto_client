#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "header.h"

//Rechte und Key des SHM-Segments
#define SMHKEY IPC_PRIVATE
#define PERMISSIONS 0644

struct serverinfo{
    char nameOfGame[BUFFERLENGTH];
    int  assignedPlayerNumber;
    int totalPlayers;
    char ourPlayerName[BUFFERLENGTH]; // Hier eventuell stattdessen struct player und dort auch unseren Player hinzufügen, bereit würde auch fehlen
    struct player *restPlayers[BUFFERLENGTH];
    pid_t connector;
    pid_t thinker;
    int shm_identifier; //not actually a serverinfo but helpful to communicate between processes
};

struct player{
    int playerNumber;
    char playerName[BUFFERLENGTH];
    int ready;
};


//functions
int creatingSHM(size_t size);
void *attachingSHM(int shmID);
void detachingSHM( void *shmAdress);
int deletingSHM (int shmID);