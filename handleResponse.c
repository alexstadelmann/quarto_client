#include "handleResponse.h"

int step = 1;

char *handle(char *request){
    char *response;


    if((response = (char*) malloc(BUFFERLENGTH*sizeof(char))) == NULL){
        perror("Error allocating memory");
    }
    
    switch(step) {

      //each case expects a different message from the server.
      case 1:

        //check if message is correct
        if(match(request, "MNM Gameserver .+accepting connections")) {

          //extract first digit of the server game version
          sscanf(request, "MNM Gameserver v%s accepting connections", cip_version);
          
          if(cip_version[0] == '2') {
            strcpy(response,"VERSION ");
            strcat(response, OUR_VERSION);
            
            step++;
            
          } else {
            strcpy(response, "Error");
          } 
        } else {
          strcpy(response, "Error");
        }
        break;  
      case 2:
        if(match(request, "Client version accepted - please send Game-ID to join")) {
          strcpy(response, "ID ");
          strcat(response, game_id);
          
          step++;
          
      
        } else {
          strcpy(response, "Error");
        }
        break;
      case 3:
        if(match(request, "PLAYING .+")) {

          char game[64];
          sscanf(request, "PLAYING %s", game);
          if (strcmp(game, "Quarto")) {
            
            strcpy(response, "Error");
            
          } else {
            free(response);
            response = NULL;
            step++;
          }
          
          
        } 

        break;  
      case 4:
        if(match(request, ".+")) {
          strcpy(response, "PLAYER ");
          strcat(response, player_number); 
          step++;
          
        } 
        break;
      case 5:
        if(match(request, "YOU .+ .+")) {

          sscanf(request, "YOU %s Player %s", player_number, player_name);
          free(response);
          response = NULL;
          step++;

        } else {
          strcpy(response, "Error");
        }
        break;

      
      case 6:
        if(match(request, "TOTAL .+")) {
          free(response);
          response = NULL;
          step++;
        } else {
          strcpy(response, "Error");
        }
        
        break;
      case 7:
        if(match(request, ".+ .+ .+")) { 
          free(response);
          response = NULL;
          
        } else if (match(request, "ENDPLAYERS")) {
          free(response);
          response = NULL;
          step++;
        } else {
          strcpy(response, "Error");
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
    
    return  response;
    
}