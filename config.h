#ifndef configFile                                                             
#define configFile                                                             

#include <stdio.h>  
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#include "header.h" 

//define struct
typedef struct{
    char hostName[BUFFERLENGTH];
    int portNumber;
    char gameKindName[BUFFERLENGTH];
}configparam;

//declare extern 
extern char *confile;

//define functions
char* readConfig(char *name);
char* findValueParam(const char *delim, char *string);
void createClientConfig();

#endif