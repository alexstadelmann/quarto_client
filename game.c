#include "performConnection.h"
#include "handleRequest.h"
#include "prolog.h"

char *intToBinary(int n) {
    int counter = 0;
    while (n != 0) {
        if (n % 2 == 0) {
            counter = counter + 1;
        }
        else {
            counter = counter + 1;
        }
        n = n / 2;
    }

    char *result[counter];
    counter = 0;

    while (n != 0) {
        if (n % 2 == 0) {
            result[counter] = "0";
        }
        else {
            result[counter] = "1";
        }
        n = n / 2;
    }
    return *result;
}


bool game(int socket_fd) {

  char *line = (char*) malloc(BUFFERLENGTH*sizeof(char));


  /* Each phase of the game has a number for the switch:
  default (and "Idle") -> 0
  "Move" -> 1
  "Game Over" -> 2
  "Choose Move" -> 3
  */
  int phase = 0;

  while(true) {

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

    switch(phase) {

      //default and "Idle"
      case 0:

        if(match(line + 2, "MOVE .+")){
          sscanf(line + 2, "MOVE %d", &moveTime);
          phase = 1;
          break;
        }

        if (match(line + 2, "WAIT")) {
          char msg1[64];
          strcpy(msg1,"OKWAIT");
          send(socket_fd, msg1, sizeof(msg1), 0);
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
          printf("NextPiece: %d\n", nextPiece);
          break;
        }

        if(match(line + 2, "^FIELD ?,?")) {
          sscanf(line + 2, "FIELD %d,%d", &width, &height);
          printf("width: %d and height %d\n", width, height);
          break;
        } 

        if(match(line + 2, "^ENDFIELD$")) {
          char msg2[52];
          strcpy(msg2, "THINKING\n");
          if(write(socket_fd, msg2, sizeof(msg2)) == -1) {
            perror("sending msg to server");
            return false;
          }
          printf("C: %s\n", msg2);
          break;
        }
        if(match(line + 2, "OKTHINK")) {
          printf("%s", line + 2);
          printField(4, field);
          
          phase = 3;
          break;
        }
        recvField(line + 2);
        break;
    
      default:
      break;
    }

    
  }
}