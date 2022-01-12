#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char nextCoordinates[2];
int width = 4;
int height = 4;
int board[4][4] = {{4,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}};
int freeFields[16];

char *intToBinary(int n) {
    int m = n;
    int counter = 0;
    while (n != 0) {
        counter++;
        n = n / 2;
    }
    //make space for \0 at the end
    printf("counter size: %d\n", counter);

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


int main() {
  
  insertCoordinates(11);
  printf("first:%c, second: %c\n", nextCoordinates[0], nextCoordinates[1]);

  int haha = freeFieldsSearch();
  printf("fieldOptions: %d", haha);


  
}