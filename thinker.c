#include "header.h"
#include "performConnection.h"
#include "thinker.h"
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
  bool winningMove = is_winning_move(nextPiece, nextField, board);
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

/*is_winning_move() first uses "bitwise and" to check if four pieces in a line
have a quality in common stored as a "1" in the binary representation of the piece.
The lines can be horizonal, vertical or diagonal.
If four pieces in a line do not share quality stored as "1", then the result
of the four "bitwise and's" is zero.

Also we have to check qualities stored as "0" in binary. 
For that purpose we invert the binaries(the piece and the board)
and proceed like before.
*/
bool is_winning_move(int piece, int field, int board[42][4]) {
  //check for common qualities stored as "1"s
  if(is_winning_move_helper(piece, field, board)) return true;

  //invert binaries to check for common qualities stored as "0"s
  piece ^= 15;

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++){
      
      if(board[i][j] != -1) {
        board[i][j] ^= 15;
      }
    } 
  }

  //call helper function with inverted binaries
  return is_winning_move_helper(piece, field, board);

}
bool is_winning_move_helper(int piece, int field, int board[42][4]) {
    int res = piece;
    int column = field % 4;
    int row = field / 4;
  
  //check vertical lines
  for(int i = 0; i < 4; i++) {

    //skip the field where we want to position the piece
    if(i == row) continue;

    //if a field is empty, then we know its not a winning move
    if(board[i][column] == -1) {
      res = 0;
      break;
    }
      //use bitwise and
      res &= board[i][column];
  }
  //if the result is not zero we have a winner
  if(res != 0) {
    return true;
  } 

  //restore initial value of res
  res = piece;
  


  //check horizontal lines like above
  for(int j = 0; j < 4; j++) {

    if(j == column) continue;

    if(board[row][j] == -1) {
      res = 0;
      break;
    }

    res = res & board[row][j];
    
    
  }
  
  if(res != 0) {
    return true;
  } 

  res = piece;
    

  //diagonal from upper left corner to lower right corner
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      
      //the sum of the indexes of the fields on this diagonal equals three
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
  } 

  res = piece;
    

  //diagonal line from lower left corner to upper right corner
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      
      //row number equals column number on this diagonal
      if(i == j) {
        if(board[i][j] == -1) {
          res = 0;
          break;
        }
        
        res = res & board[i][j];
       
      }
    }
  }
  if(res != 0) {
    return true;
  } 

  return false;

}
