#include "performConnection.h"
#include "handleRequest.h"
#include "prolog.h"
#include "header.h"
#include "handleResponse.h"
#include <unistd.h>
#include "thinker.h"

//Variables from the game phase:
int moveTime;
int board[4][4];
bool player0won = false;
bool player1won = false;
char winnerName[126];
int nextPiece;
int nextSquare;
int nextOpponentPiece;
int freePieces[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
char nextMove[16];
char nextCoordinates[2];
int free_squares[16];
int height;
int width;



bool game(int socket_fd) {

  char *line = (char*) malloc(BUFFERLENGTH*sizeof(char));
  char msg[64];
  

  /* Each phase of the game has a number for the switch:
  default (and "Idle") -> 0
  "Move" -> 1 (name from script is somewhat misleading as we actually receive the board)
  "Game Over" -> 2
  "Make move" -> 3
  */
  int phase = 0;

  //flag needed for phase 3()
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

        if(match(line + 2, "^MOVE .+$")) {

          sscanf(line + 2, "MOVE %d", &moveTime);
          phase = 1;
          break;
        }

        if(match(line + 2, "^WAIT$")) {

          printf("S: %s\n", line + 2);
          strcpy(msg,"OKWAIT\n");

          if(write(socket_fd, msg, strlen(msg)) == -1) {
            perror("sending msg to server");
            return false;
          }

          printf("C: OKWAIT\n");
          break;
        } 

        if(match(line + 2, "^GAMEOVER$")) {
          phase = 2;
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

      //Gameover:
      case 2:

        if(match(line + 2, "^PLAYER0WON .+$")) {
          
          if(strcmp(line + 2, "PLAYER0WON Yes") == 0) {
            player0won = true;
          }
          break;
        }

        if(match(line + 2, "^PLAYER0W1N .+$")) {
          
          if(strcmp(line + 2, "PLAYER1WON Yes") == 0) {
            player1won = true;
          }
          break;
        }

        if(match(line + 2, "^QUIT$")) {
          
          puts("\n ---------------------------");
          if(player0won) { 
            printf("| Player 1 has won the game |\n");
          } else if (player1won) {
            printf("| Player 2 has won the game |\n");
          } else {
            printf("| Its a tie                 |\n");
          }
          puts(" ---------------------------");
          return true;
        }

        if(match(line + 2, "^FIELD ?,?")) {
          sscanf(line + 2, "FIELD %d,%d", &width, &height);
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


bool recv_board(char *line) {
  int temp = atoi(&line[0]) - 1;
  char array[4][16];
  sscanf(line + 2, "%s %s %s %s", &array[0][0], &array[1][0], &array[2][0], &array[3][0]);
  for(int j = 0; j < 4; j++) {
    if(array[j][0] == '*') {
      board[temp][j] = -1;
    } else {
      int temp2 = atoi(&array[j][0]);
      board[temp][j] = temp2;
      freePieces[temp2] = -1;
    }
  }
  
  return true;
}
