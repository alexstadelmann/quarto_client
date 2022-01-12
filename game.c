#include "performConnection.h"
#include "handleRequest.h"
#include "prolog.h"
#include "header.h"




bool game(int socket_fd) {

  char *line = (char*) malloc(BUFFERLENGTH*sizeof(char));
  char msg[64];


  /* Each phase of the game has a number for the switch:
  default (and "Idle") -> 0
  "Move" -> 1
  "Game Over" -> 2
  "Choose Move" -> 3
  */
  int phase = 0;

  //flag needed for phase 3
  bool skipReading = false; 

  while(true) {

    if(!skipReading) {
        //receive the next line send by the server
      if(!read_line(socket_fd, line)) {
        perror("reading line");
        return false;
      }
      //check if message is negative
      if(line[0] == '-') {
        printf("S: Error! %s\nC: Disconnecting server...\n",line+2);
        free(line);
        return false;
      } 
    }
    switch(phase) {

      //default and "Idle"
      case 0:

        if(match(line + 2, "^MOVE .+$")){
          sscanf(line + 2, "MOVE %d", &moveTime);
          phase = 1;
          break;
        }

        if (match(line + 2, "^WAIT$")) {
          printf("S: %s\n", line + 2);
          strcpy(msg,"OKWAIT\n");
          if(write(socket_fd, msg, strlen(msg)) == -1) {
            perror("sending msg to server");
            return false;
          }
          printf("C: OKWAIT\n");
          
          break;
        } 

        if(match(line + 2, "GAMEOVER ? ?" )) {
          //AUFGABE: Gewinnerdaten aus line extrahieren und speichern
          phase = 3;
          break;
        }

        //should not reach this point
        perror("unexpected message from server");
        free(line);
        return false;
        

      //"Move"  
      case 1:

        if(match(line + 2, "NEXT .+")) {
          sscanf(line + 2, "NEXT %d", &nextPiece);
          freePieces[nextPiece] = -1;
          break;
        }

        if(match(line + 2, "^FIELD ?,?")) {
          sscanf(line + 2, "FIELD %d,%d", &width, &height);
          break;
        } 

        if(match(line + 2, "^ENDFIELD$")) {
          strcpy(msg, "THINKING\n");
          if(write(socket_fd, msg, strlen(msg)) == -1) {
            perror("sending msg to server");
            return false;
          }
          break;
        }
        if(match(line + 2, "OKTHINK")) {
          print_board(4, board);
          
          phase = 3;
          skipReading = true;
          break;
        }

        recv_board(line + 2);
        break;

      //Make move:  
      case 3:
        if(skipReading) {
          
          calculateMove();
          printf("nextMove: %s\n", nextMove);
          if(write(socket_fd, nextMove, strlen(nextMove))== -1) {
            perror("sending msg to server");
            return false;
          }
          skipReading = false;
        } else if(match(line + 2, "^MOVEOK$")) {
          phase = 0;
          break;
        } else {
          perror("unexpected message from server");
          return false;
        }
      
      default:
      break;
    }

    
  }
}