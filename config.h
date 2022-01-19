#ifndef configFile                                                             
#define configFile                                                             

#include <stdio.h>  
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#include "header.h" 


typedef struct{
    char hostname[BUFFERLENGTH];
    int portnumber;
    char gameKindName[BUFFERLENGTH];
}configparam;



//Variables 
char config_file[100];
configparam *config_param;
//define functions
bool readConfig(char *config);
void createClientConfig(char *confile);

#endif
