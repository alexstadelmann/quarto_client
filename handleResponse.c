#include "handleResponse.h"
#include "header.h"

int step=1;
//vieles auskommentierte noch vom alten Ansatz zur formatierten Ausgabe, kann helfen
// bisher nur die "normalen" Kommandozeilennachrichten die vom Server empfangen wurden welche noch schön formatiert ausgegeben werden müssen
char *handle(char *request){
    char *response;


    if((response = (char*) malloc(BUFFERLENGTH*sizeof(char)))==NULL){
        perror("Error allocating memory");
    }
    
    // switch(step) {
    //   case 1:
    //     //check server message
    //     if(match(request, "MNM Gameserver .+accepting connections")) {

    //       //extract first digit of game cip_version
    //       sscanf(request, "MNM Gameserver v%c accepting connections", cip_version);


    //       if(*cip_version == '2') {
    //         strcpy(response,"VERSION ");
    //         strcat(response, OUR_VERSION);
    //       } else {
    //         perror("Wrong version number");
    //         return NULL;
    //       } 
    //     } else {
    //       return NULL;
    //     }
          
    //     }
    // }
    if (step==1 && match(request, "MNM Gameserver .+accepting connections"))
    {   
        sscanf(request, "MNM Gameserver v%c accepting connections", cip_version);
        if(*cip_version == '2') {
          strcpy(response,"VERSION ");
          strcat(response, OUR_VERSION);
        } else {
          perror("Wrong version number");
        } 
        
        /*Schön formatierte Ausgabe
        strcpy(print, "The MNM server with version ");
        char *version = substring(request, 16,strlen(request)-22);      //Aus dem vom Server gesendeten String die Versionsnummer herausfiltern
        strcat(print, version);
        strcat(print, " accepted the connection. "); 

        if (version != NULL) {
            free(version);
        }  */
        step++;  
    } else if (step==2 && match(request, "Client version accepted - please send Game-ID to join"))
    {
        strcpy(response, "ID ");
        strcat(response, game_id);
        //Ausgabe
        //strcpy(print, "Client version accepted - please send Game-ID to join.");

        step++;

    }else if (step == 3 && match(request, "PLAYING .+")){
        if(response != NULL){
            free(response);
        }
        response = NULL;                                                //NULL-Pointer, da der Client hier nicht reagieren muss
        /*Ausgabe
        strcpy(print, "Es wird das Spiel ");
        char *gamekind = substring(request, 9, strlen(request));
        strcat(print, gamekind);
        strcat(print, " gespielt.");

        if (gamekind != NULL)
        {
            free(gamekind);
        } */

        step++;
        
    }else if (step == 4 && match(request, ".+")){
        //char sint[12];
        //sprintf(sint, "%d", player_number);
        strcpy(response, "PLAYER ");
        strcat(response, player_number); 

        /*Ausgabe
        strcpy(print, "Diese Partie trägt den Namen : \'");
        char *gamename = substring(request, 2, strlen(request));
        strcat(print, gamename);
        strcat(print, "\'.");

        if (gamename != NULL)
        {
            free(gamename);
        }*/
        step++;

    }else if(step == 5 && match(request, "YOU .+ .+")){
        if (response != NULL)
        {
            free(response);
        }
        response=NULL;
        /*Ausgabe (hier auch die jeweiligen Werte im richtigen Format in der Struct ablegen (in Milestone 2))
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
        } */
        step++;
    }else if (step == 6 && match(request, "TOTAL .+")){
        if (response != NULL){
            free(response);
        }
        response=NULL;
        /*
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
        } */
        step++;
    }else if (match(request, "ENDPLAYERS") ){
        if(response!=NULL){
            free(response);
        }
        response=NULL;

        printf("The game starts. Have fun!\n");

    }else if (step >= 7 && match(request, ".+ .+ .+")){
        if(response!=NULL){
            free(response);
        }
        response = NULL;
        //hier erstmal provisorisch game-id frei gemacht, dadurch zum geradigen Zeitpunkt keine leaks möglich.
        if (game_id!=NULL){
            free(game_id);
        }
        game_id= NULL;
        /*
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
        }*/

    }else{ 
        /*                                                                       //Unbekannte Anfrage
        if(response!=NULL){
            free(response);
        }
        response = NULL;                                                            
        if(print!=NULL){
            free(print);
        }
         print = NULL;*/
         strcpy(response,"Unknown request");
    }

    if(response != NULL){
        strcat(response, "\n");
    } /*hier noch vllt kommentar
    if(print != NULL){
        printf("S: %s\n", print);
        free(print);
    } */
    

    return  response;
    
}