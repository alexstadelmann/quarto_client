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
        char sver[10];
        sprintf(sver, "%f", VERSION);
        strcpy(response,"VERSION ");
        strcat(response, sver);
        //SChön formatierte Ausgabe
        strcpy(print, "The MNM server with version ");
        char *version = substring(request, 16,strlen(request)-22);      //Aus dem vom Server gesendeten String die Versionsnummer herausfiltern
        strcat(print, version);
        strcat(print, " accepted the connection. ");

        if (version != NULL) {
            free(version);
        }  
        step++;  
    } else if (step==2 && match(request, "Client version accepted - please send Game-ID to join"))
    {
        strcpy(response, "ID ");
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
        strcpy(print, "Es wird das Spiel ");
        char *gamekind = substring(request, 9, strlen(request));
        strcat(print, gamekind);
        strcat(print, " gespielt.");

        if (gamekind != NULL)
        {
            free(gamekind);
        }

        step++;
        
    }else if (step == 4 && match(request, ".+")){
        char sint[12];
        sprintf(sint, "%d", player_number);
        strcpy(response, "PLAYER ");
        strcat(response, sint); 

        //Ausgabe
        strcpy(print, "Diese Partie trägt den Namen : \'");
        char *gamename = substring(request, 2, strlen(request));
        strcat(print, gamename);
        strcat(print, "\'.");

        if (gamename != NULL)
        {
            free(gamename);
        }
        step++;

    }else if(step == 5 && match(request, "YOU .+ .+")){
        if (response != NULL)
        {
            free(response);
        }
        response=NULL;
        //Ausgabe (hier auch die jeweiligen Werte im richtigen Format in der Struct ablegen (in Milestone 2))
        strcpy(print, "You are the Player with the number ");
        char *playnum = substring(request, 5,7);                    //evtl. verzählt --> Testen und Zahlen ggf. anpassen
        strcat(print, playnum);
        strcat(print, " and your name is ");
        char *playname = substring(request, 8, strlen(request));
        strcat(print, playname);

        if (playnum != NULL)
        {
            free(playnum);
        }
        if (playname != NULL)
        {
            free(playname);
        }
        step++;
    }else if (step == 6 && match(request, "TOTAL .+")){
        if (response != NULL){
            free(response);
        }
        response=NULL;

        char *totalPlayer = substring(request, 6, strlen(request));
        int anz = atoi(totalPlayer);
        if(anz > 1){
            strcpy(print, "Es nehmen ");
        }else{
            strcpy(print, "Es nimmt ");
        }
        strcat(print, totalPlayer);
        strcat(print, " am Spiel teil.");
        if (totalPlayer != NULL)
        {
            free(totalPlayer);
        }
        step++;
    }else if (match(request, "ENDPLAYERS") ){
        if(response!=NULL){
            free(response);
        }
        response=NULL;

        strcpy(print, "The game starts. Have fun!");

    }else if (step >= 7 && match(request, ".+ .+ .+")){
        if(response!=NULL){
            free(response);
        }
        response = NULL;

        char *playNum = substring(request, 2, 4); //hier nochmal checken ob richtige Nummern
        char *playName = substring(request, 4, strlen(request)-1);
        char *status = substring(request, strlen(request)-1,strlen(request) );
        

        strcpy(print, "Spieler Nummer ");
        strcat(print, playNum);
        strcat(print, " (");
        strcat(print, playName);
        strcat(print, ") ist ");

        if(atoi(status)==1){
            strcat(print, "bereit!");
        }else if(atoi(status)==0){
            strcat(print, "nicht bereit!");
        }

        if (playNum != NULL){
            free(playNum);
        }
        if (playName != NULL){
            free(playName);
        }
        if (status != NULL){
            free(status);
        }

    }else{                                                                        //Unbekannte Anfrage
        if(response!=NULL){
            free(response);
        }
        response = NULL;                                                            
        if(print!=NULL){
            free(print);
        }
         print = NULL;
    }

    if(response != NULL){
        strcat(response, "\n");
    }
    if(print != NULL){
        printf("Server: %s\n", print);
        free(print);
    }

    return  response;
    
}