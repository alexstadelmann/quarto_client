#include "handleResponse.h"

int step=1;

char *handle(char *request){
    char *response;
    char *print;

    if((response = malloc(BUFFERLENGTH*sizeof(char)))==NULL){
        //TODO: Fehlerbehandlung
    }

    if((print = malloc(BUFFERLENGTH*sizeof(char)))== NULL){
        //TODO: Fehlerbehandlung
    }

    if (step==1 && match(request, "MNM Gameserver .+accepting connections"))
    {
        strcpy(response,"VERSION ");
        strcat(response, VERSION);
        //SChön formatierte Ausgabe
        strcpy(print, "The MNM server with version ");
        char *version = substring(request, 16,strlen(request)-22);      //Aus dem vom Server gesendeten String die Versionsnummer herausfiltern
        strncat(print, version);
        strncat(print, " accepted the connection. ");

        if (version != NULL) {
            free(version);
        }  
        step++;  
    } else if (step==2 && match(request, "Client version accepted - please send Game-ID to join"))
    {
        strncpy(response, "ID ");
        strcat(response, game_id);
        //Ausgabe
        strcpy(print, "Client version accepted - please send Game-ID to join.");

        step++;

    }else if (step == 3 && match(request, "PLAYING .+")){
        if(response != NULL){
            free(response);
        }
        response = NULL;                                                //NULL-Pointer, da der Client hier nicht reagieren muss
        //Ausgabe
        strncpy(print, "Es wird das Spiel ");
        char *gamekind = substring(request, 9, strlen(request));
        strncat(print, gamekind);
        strncat(print, " gespielt.");

        if (gamekind != NULL)
        {
            free(gamekind);
        }

        step++;
        
    }else if (step ==4 && match(request, ".+")){
        strcpy(response, "PLAYER ");
        strcat(response, player_number); 
    }
    

    

}