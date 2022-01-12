#include "handleResponse.h"
#include <unistd.h>

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