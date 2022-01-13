#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

char nextCoordinates[2];
int width = 4;
int height = 4;
int board[4][4] = {{4,11,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,4,-1}};
char cube[4][4][5];
char test[10][4];
char test2[2][10][4];



int freeFields[16];

char *intToBinary(int n) {
    int m = n;
    int counter = 0;
    while (n != 0) {
        counter++;
        n = n / 2;
    }

    char * result = (char *) malloc(counter*sizeof(char));
    result[counter] = '\0';
    counter--;
    while (counter >= 0) {
        if (m % 2 == 0) {
            *(result + counter) = '0';
        }
        else {
            *(result + counter) = '1';
        }
        m = m / 2;
        counter--;
    }
    result[counter] = '\0';
    return result;
}

void insertCoordinates(int pos) {
  char column = (char) (pos / width + 65);
  char row = (char) (pos % height + 49);
  nextCoordinates[0] = column;
  nextCoordinates[1] = row;
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

void makeBinaryCube() {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(board[i][j] != -1) {
        char *bin = intToBinary(board[i][j]);
        strcpy(cube[i][j], bin);
        free(bin);
      }
      
    }
  } 
}

// void isWinningMove(int piece, int field, int board[42][4]) {
// //   int res = piece;
// //   int column = field % 4;
// //   int row = field / 4;


// //   //vertical line
// //   for(int i = 0; i < 4; i++) {
// //     if(i == row) continue;
// //     if(board[i][column] != -1) res = res & board[i][column];
// //   }

// //   if(res != 0) {
// //     return true;
// //   } else {
// //     res = piece;
// //   }

//   //horizontal line
//   for(int j = 0; j < 4; j++) {
//     if(j == column) continue;

//     if(board[row][j] != -1) res = res & board[row][j];
    
//   }

//   if(res != 0) {
//     return true;
//   } else {
//     res = piece;
//   }

// //   //diagonal from upper left corner to lower right corner
// //   for(int i = 0; i < 4; i++){
// //     for(int j = 0; j < 4; j++){
// //       if(i + j == 3) {
// //         if(i == row && j == column) continue;

// //         if(board[i][j] != -1) res = res & board[i][j];
// //       }
// //     } 
// //   }

// //   if(res != 0) {
// //     return true;
// //   } else {
// //     res = piece;
// //   }

// //   //diagonal line from upper right corner to lower left corner
// //   //TO DO
    
  
//   return false;


// }

int main() {
 int test = 0 & (-1);
 printf("%d", test);


  
}