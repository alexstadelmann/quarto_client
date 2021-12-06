#include "handleResponse.h"
#include "header.h"

int step=1;

char *handle(char *request){
    char *response;


    if((response = (char*) malloc(BUFFERLENGTH*sizeof(char)))==NULL){
        perror("Error allocating memory");
    }
    
    switch(step) {

      //first message from server
      case 1:

        //check if message is correct
        if(match(request, "MNM Gameserver .+accepting connections")) {

          //extract first digit of the server game version
          sscanf(request, "MNM Gameserver v%c accepting connections", cip_version);

          if(*cip_version == '2') {
            strcpy(response,"VERSION ");
            strcat(response, OUR_VERSION);
          } else {
            perror("Wrong version number");
            exit(EXIT_FAILURE);
          } 
        } else {
          perror("Expected other message from server");
          exit(EXIT_FAILURE);
        }

        step++;
        break;

      //second message from server  
      case 2:
        if(match(request, "Client version accepted - please send Game-ID to join")) {
          strcpy(response, "ID ");
          strcat(response, game_id);
      
        } else {
          perror("Expected other messagge from server");
          exit(EXIT_FAILURE);
        }

        step++;
        break;

      //third message from server
      case 3:
        if(match(request, "PLAYING .+")) {

          char game[64];
          sscanf(request, "PLAYING %s", game);
          if (!strcmp(game, GAMEKINDNAME)) {
            if(response != NULL){
            free(response);
          }
          response = NULL;  
          }
        } else {
          perror("Expected other message from server");
          exit(EXIT_FAILURE);
        }

        step++;
        break;
      //fourth message from server  
      case 4:
        if(match(request, ".+")) {
          strcpy(response, "PLAYER ");
          strcat(response, player_number); 
          
        } else{
          perror("Expected other message from server");
          exit(EXIT_FAILURE);
        }

        step++;
        break;
      //fifth message from server
      case 5:
        if(match(request, "YOU .+ .+")) {
          sscanf(request, "YOU %s %s", player_number, player_name);
          
        } else {
          perror("Expected other message from server");
          exit(EXIT_FAILURE);
        }
        step++;
        break;

      //sixth message from server
      case 6:
        if(!match(request, "TOTAL .+")) {
          perror("Expected other message from server");
          exit(EXIT_FAILURE);
        }

        step++;
        break;
      //seventh message from server
      case 7:
        if(!match(request, ".+ .+ .+") & !match(request, "ENDPLAYERS")) {
          perror("Expected something else");
        } 
        step++;
        break; 

      default:
        printf("mal schauen was hier passiert :)\n");
         

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