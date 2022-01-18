#include "header.h"
#include "thinker.h"

/*
The following functions rely on a handful of global variables defined in game.c
*/
void free_pieces_search(int freePieces[]) {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {

      if(board[i][j] != -1) {
        freePieces[board[i][j]] = -1;
      }
    }
  }
}


void calculateMove() {


  free_pieces_search(freePieces);

  int square_options = free_squares_search(free_squares);
  srand(time(0));
  nextSquare = free_squares[rand() % square_options];
  convert_coordinates(nextSquare, nextCoordinates);
  insertNextMove(nextCoordinates, nextMove);

}

/*Update the free_squares array so that it contains all the empty fields.
It returns the number of empty fields, i.e. the length of the array.
*/
int free_squares_search(int free_squares[]) {
  int count = 0;
  for(int i = 3; i >= 0; i--) {
    for(int j = 0; j < 4; j++) {
      
      if(board[i][j] == -1) {
        
        free_squares[count] = i*4 + j;
        count++;
      }
    }
  }
  return count;
}

//translates the standard coordinates (0 to 15) to coordinates like "A4";
void convert_coordinates(int pos, char next_coordinates[]) {

  char column = (char) (pos % width + 65);
  char row = (char) (pos / height + 49);
  next_coordinates[0] = column;
  next_coordinates[1] = row;
}

//create the message that the client sends the server, e.g  "PLAY B2,7"
void insertNextMove(char next_coordinates[], char next_move[]) {
  strcpy(next_move, "PLAY ");
  strcat(next_move, next_coordinates);
  chooseNextOpponentPiece();
  char temp[4];
  bool winningMove = is_winning_move(nextPiece, nextSquare, board);
  if(nextOpponentPiece != -1 && !winningMove) {
    sprintf(temp, ",%d\n", nextOpponentPiece);
    strcat(nextMove, temp);
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

/*is_winning_move() uses "bitwise and" to check if four pieces in a line
have a quality in common stored as a "1" in the binary representation of the piece.
The lines can be horizonal, vertical or diagonal.
If four pieces in a line do not share quality stored as "1", then the result
of the four "bitwise and's" is zero.

Also we have to check qualities stored as "0" in binary. 
For that purpose we invert the binaries(the piece and the board)
and proceed like before.
*/
bool is_winning_move(int piece, int Square, int board[][4]) {
  //check for common qualities stored as "1"s
  if(is_winning_move_helper(piece, Square, board)) return true;

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
  return is_winning_move_helper(piece, Square, board);

}

//helper function 
bool is_winning_move_helper(int piece, int Square, int board[][4]) {
    int res = piece;
    int column = Square % 4;
    int row = Square / 4;
  
  //check vertical lines
  for(int i = 0; i < 4; i++) {

    //skip the Square where we want to position the piece
    if(i == row) continue;

    //if a Square is empty, then we know its not a winning move
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
      
      //the sum of the indexes of the Squares on this diagonal equals three
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
