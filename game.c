#include "performConnection.h"
#include "handleRequest.h"
#include "prolog.h"



bool game(int socket_fd) {

  char *line = (char*) malloc(BUFFERLENGTH*sizeof(char));


  /* Each phase of the game has a number for the switch:
  default (and "Idle") -> 0
  "Move" -> 1
  "Game Over" -> 2
  "Spielzug" -> 3
  */
  int phase = 0;

  while(true) {

    //receive the next line send by the server
    if(!read_line(socket_fd, line)) {
      perror("reading line");
      return false;
    }
    printf("%s", line);
    if(match(line + 2, "^ENDFIELD$")) {
      puts("test");
      char msg3[] = "THINKING";
          if(write(socket_fd, msg3, sizeof(msg3)) == -1) {
            perror("sending msg to server");
            puts("uacamole");
            return false;
          }

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
          printf("%d\n", moveTime);
          phase = 1;
          break;
        }

        if (match(line + 2, "WAIT")) {
          char msg1[] = "OKWAIT";
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
        //printf("tadaa: %s\n", line + 2);

        if(match(line + 2, "NEXT .+")) {
          sscanf(line + 2, "NEXT %d", &nextPiece);
          printf("NextPiece: %d\n", nextPiece);
          break;
        }

        if(match(line + 2, "^FIELD ?,?")) {
          break;
        } 
        if(match(line + 2, "ENDFIELD")) {
          char msg2[] = "THINKING";
          if(write(socket_fd, msg2, sizeof(msg2) == -1)) {
            perror("sending msg to server");
            puts("uacamole");
            return false;
          }
          printf("C: %s\n", msg2);
          field[0][0] = 11;
          field[3][0] = 1;
          field[3][1] = 2;
          printField(4, field);
          break;
        }
        if(match(line + 2, "OKTHINK")) {
          printField(4, field);
          phase = 3;
          break;
        }
        if(match(line + 2, "MOVEOK")) {
          puts("Yuhuu");
          break;
        }
        recvField(line + 2);
        break;
    

    }
  }
}