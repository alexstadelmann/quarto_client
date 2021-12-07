#include "handleResponse.h"
#include "header.h"

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
          sscanf(request, "MNM Gameserver v%c accepting connections", cip_version);

          if(*cip_version == '2') {
            strcpy(response,"VERSION ");
            strcat(response, OUR_VERSION);
            strcat(response, "\n");
            step++;
            return response;
          } else {
            perror("Wrong version number");
            exit(EXIT_FAILURE);
          } 
        } else {
          return NULL;
        }
      break;  
      case 2:
        if(match(request, "Client version accepted - please send Game-ID to join")) {
          strcpy(response, "ID ");
          strcat(response, game_id);
          strcat(response, "\n");
          step++;
          return response;
      
        } else 
          return NULL;

      break;
      case 3:
        if(match(request, "PLAYING .+")) {

          char game[64];
          sscanf(request, "PLAYING %s", game);
          if (strcmp(game, "Quarto")) {
            
            if(response != NULL){
            free(response);
            }
            perror("Server playing different game than quarto");
            exit(EXIT_FAILURE);
          }
          response = NULL;
          step++;
        } 

      break;  
      case 4:
        if(match(request, ".+")) {
          strcpy(response, "PLAYER ");
          strcat(response, player_number); 
          strcat(response, "\n");
          step++;
          return response;
        } 
      break;
      case 5:
        if(match(request, "YOU .+ .+")) {
          //sscanf(request, "YOU %s Player %s", player_number, player_name);
         // printf("%s, %s", player_number, player_name);
          
          
        } else {
          perror("Expected other message from server");
          exit(EXIT_FAILURE);
        }
        if (response != NULL)
        {
            free(response);
        }
        response=NULL;

        step++;
        break;

      //sixth message from server
      case 6:
        if(!match(request, "TOTAL .+")) {
          perror("Expected other message from server");
          exit(EXIT_FAILURE);
        }
        if (response != NULL)
        {
            free(response);
        }
        response=NULL;


        step++;
        break;
      //seventh message from server
      case 7:
        if(!match(request, ".+ .+ .+") || !match(request, "ENDPLAYERS")) {
          perror("Expected something else");
        } 
        if (response != NULL)
        {
            free(response);
        }
        response=NULL;

        step++;
        break; 

      default:
        if (response != NULL)
        {
            free(response);
        }
        response=NULL;
         

    }
    
    return  response;
    
}