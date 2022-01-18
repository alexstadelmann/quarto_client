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
int board[4][4] = {{4,11,6,3},{2,3,3,3},{4,4,4,4},{5,5,4,5}};
int cube[4][4][4];
char test[10][4];
char test2[2][10][4];

void make_cube_from_board(int height, int width, int board[height][width], int depth, int cube[height][width][depth]) {

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      int temp = board[i][j];
      for(int k = depth - 1; k >= 0; k--) {
        if(temp % 2 == 1) {
          cube[i][j][k] = 1;
        } else {
          cube[i][j][k] = 0;
        }
        temp /= 2;
      }
    }
  }
}

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




int main() {
 make_cube_from_board(4,4,board,4,cube);
 for(int j = 0; j < 4; j++) {
   
   printf("%d", cube[0][0][j]);
 }
 puts("");


  
}