#include "header.h"
#include "performConnection.h"
#include <time.h>
#include <stdlib.h>


void calculateMove() {
  int fieldOptions = freeFieldsSearch();

  
  
  srand(time(0));
  insertCoordinates(freeFields[rand() % fieldOptions]);
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
  char column = (char) (pos / width + 65);
  char row = (char) (pos % height + 49);
  nextCoordinates[0] = column;
  nextCoordinates[1] = row;
}

void insertNextMove() {
  strcpy(nextMove, "PLAY ");
  strcat(nextMove, nextCoordinates);
  chooseNextOpponentPiece();
  char temp[4];
  if(nextOpponentPiece != -1) {
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



