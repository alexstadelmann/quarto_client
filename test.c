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

char *intToBinary(int number, int length ) {
    
    int cursor = length;
  

    char * result = (char *) malloc(length*sizeof(char));
    result[cursor] = '\0';
    cursor--;
    while (number > 0) {
        if (number % 2 == 0) {
            *(result + cursor) = '0';
        }
        else {
            *(result + cursor) = '1';
        }
        number /= 2;
        cursor--;
    }
    while(cursor >= 0) {
      result[cursor] = '0';
      cursor--;
    }
    return result;
}



int main() {
 char *temp = intToBinary(77, 8);
   
   printf("%shhh", temp);
   free(temp);
 
 puts("");


  
}