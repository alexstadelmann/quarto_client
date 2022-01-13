#include "header.h"
#include "performConnection.h"
#include <time.h>
#include <stdlib.h>


void calculateMove() {
  int fieldOptions = freeFieldsSearch();
  
  srand(time(0));
  nextField = freeFields[rand() % fieldOptions];
  insertCoordinates(nextField);
  insertNextMove();

}

int freeFieldsSearch() {
  int count = 0;
  for(int i = 3; i >= 0; i--) {
    for(int j = 0; j < 4; j++) {
      
      if(board[i][j] == -1) {
        
        freeFields[count] = i*4 + j;
        count++;
      }
    }
  }
  return count;
}

void insertCoordinates(int pos) {
  printf("Coordinate in decimal:%d\n", pos);
  char column = (char) (pos % width + 65);
  char row = (char) (pos / height + 49);
  nextCoordinates[0] = column;
  nextCoordinates[1] = row;
}

void insertNextMove() {
  strcpy(nextMove, "PLAY ");
  strcat(nextMove, nextCoordinates);
  chooseNextOpponentPiece();
  char temp[4];
  bool winningMove = isWinningMove(nextPiece, nextField, board);
  if(winningMove) {
    puts("Yuhuuu");
  }
  if(nextOpponentPiece != -1 && !winningMove) {
    sprintf(temp, ",%d\n", nextOpponentPiece);
    strcat(nextMove, temp);
    freePieces[nextOpponentPiece] = -1;
  } else {
    strcat(nextMove, "\n");
  }
  
}

void chooseNextOpponentPiece() {
  int cursor = 0;
  while(freePieces[cursor] == -1) {
    cursor++;
  }
  if(cursor <= 15) {
    nextOpponentPiece = cursor;
  } else {
    nextOpponentPiece = -1;
  }
}


bool isWinningMove(int piece, int field, int board[42][4]) {
  int res = piece;
  for(int k = 0; k < 2; k++) {
    if(k == 1) res = res^15;
    printf("res: %d\n", res);
  int column = field % 4;
  printf("column: %d\n", column);
  int row = field / 4;
  printf("row: %d\n", row);


  //vertical line
  for(int i = 0; i < 4; i++) {
    if(i == row) continue;
    if(board[i][column] == -1) {
      res = 0;
      break;
    }
    res = res & board[i][column];
    printf("res actualized: %d\n", res);
  }

  if(res != 0) {
    return true;
  } else {
    res = piece;
  }

  //horizontal line
  for(int j = 0; j < 4; j++) {
    if(j == column) continue;
    if(board[row][j] == -1) {
      res = 0;
      break;
    }
    res = res & board[row][j];
    printf("res actualized: %d\n", res);
    
  }

  if(res != 0) {
    return true;
  } else {
    res = piece;
  }

  //diagonal from upper left corner to lower right corner
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(i + j == 3) {
        if(i == row && j == column) continue;
        if(board[i][j] == -1){
          res = 0;
          break;
        } 

        res = res & board[i][j];
      }
    } 
  }

  if(res != 0) {
    return true;
  } else {
    res = piece;
  }

  //diagonal line from upper right corner to lower left corner
  
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i == j) {
        if(board[i][j] == -1) {
          res = 0;
          break;
        } else {
          res = res & board[i][j];
        }
      }
    }
  }
    
  
  
  }
  
  
  return false;

}


