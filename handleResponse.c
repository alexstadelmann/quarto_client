#include "handleResponse.h"

char *handle(char *request){
    char *response;
    char *retVal;

    if((response = malloc(BUFFERLENGTH*sizeof(char)))==NULL){
        //TODO: Fehlerbehandlung
    }

    if((retVal = malloc(BUFFERLENGTH*sizeof(char)))== NULL){
        //TODO: Fehlerbehandlung
    }

    if (step==1 && match(request, "MNM Gameserver .+accepting connections"))
    {
        strcpy(response,"VERSION ");
        strcat(response, VERSION);
    }
    

}