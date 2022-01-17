#include "handleResponse.h"
#include <unistd.h>

int step = 1;
int countPlayer = 0; 
int sleepCounter = 10;
bool player1 = 0;
bool player2 = 0;

char *handleGame(char *request){
    char *response;
    char *print;

    if((response = (char*) malloc(BUFFERLENGTH*sizeof(char))) == NULL){
        perror("Error allocating memory\n");
    }
    if((print = malloc(BUFFERLENGTH*sizeof(char)))==NULL){
      perror("Error allocating memory\n");
    }
    
    switch(step) {
 
 
      case 1:  //Unterscheidung in welchen case wir springen
        if(match(request, "MOVE .+")){
          sscanf(request, "MOVE %d", moveTime);
          printf("%d\n", moveTime);
          sleepCounter = 10; 
          step = 2;
        }  
        if(match(request, "WAIT")){   
          step = 10;
        } 
        if(match(request, "GAMEOVER")){   
          step = 11;
        } else {  //?
          strcpy(response, "Error");
        }
        break; 

      case 2: 
      
      case 10:           //Server hat Move geschickt
        //server schickt das Spielfeld, so lange warten
        while(!match(request, "ENDSquare")){
          //Dauerschleife bis Schlüsselwort kommt
        }
        
        //hier einlesen des Spielfelds depending on Thniking-Method

        //dem Server Antworten
        strcpy(response, "THINKING");

        //Jetzt Aufgabe Phase Spielzug (Spielzug berechnen und senden) - aufruf der Methode inkl. Senden des Spielzugs

        step = 8;
        break;




      case 10:    //Wait-Zweig
        strcpy(response, "OKWAIT");
        sleep(1);
        sleepCounter--;
        if (sleepCounter <= 0){
          strcpy(response, "Error");
        }else{
          step = 8;
        }

        break;


      case 11:   //Gameover 

        if(match(request, "PLAYER0WON")){  
          
          if(response != NULL){
            free(response);
          }

          char *won0 = substring(request, 11, strlen(request));
          if(!strcmp(won0, "Yes")){
            player1 = 1;
          } 
          free(won0);

        } else if(match(request, "PLAYER1WON")) {
          
          if(response != NULL){
            free(response);
          }

          char *won1 = substring(request, 11, strlen(request));
          if(!strcmp(won1, "Yes")){
            player2 = 1;
          } 
          free(won1);
        } 

        if(match(request, "QUIT")){   
          
          if(player1 && !player2){ //erster spieler
 
           strcpy(print, "Player 1 won the game.");

          } else if(!player1 && player2){ //zweiter spieler

            strcpy(print, "Player 2 won the game.");

          } else { //untentschieden

            strcpy(print, "The game is undecided."); 
          }

        } 

        break;

      default:
        free(response);
        response = NULL;
        break;
    }

    if(response != NULL) {
      strcat(response, "\n");
    }

    if(print != NULL){
      printf("S: %s\n", print);
      free(print);
    }

    
    return  response;
    
}

