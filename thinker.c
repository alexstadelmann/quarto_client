#include "header.h"
#include "performConnection.h"
#include <time.h>
#include <stdlib.h>


void calculateMove() {
  int fieldOptions = freeFieldsSearch();
  
  srand(time(0));
  int random = rand();
  printf("fieldOptions: %d\n", fieldOptions);
  //random = random  fieldOptions;
  printf("random number%d\n", random);
  insertCoordinates(rand() % fieldOptions);
  puts("yuhuu");
  insertNextMove();

}

int freeFieldsSearch() {
  int count = 0;
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
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
  char next[2];
  sprintf(next, "%d", nextOpponentPiece);
  strcat(nextMove, next);
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



