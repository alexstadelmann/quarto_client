#include "handleResponse.h"
#include <unistd.h>

bool recv_board(char *line) {
  int temp = atoi(&line[0]) - 1;
  char array[4][16];
  sscanf(line + 2, "%s %s %s %s", &array[0][0], &array[1][0], &array[2][0], &array[3][0]);
  for(int i = 0; i < 4; i++) {
    if(array[i][0] == '*') {
      board[temp][i] = -1;
    } else {
      board[temp][i] = atoi(&array[i][0]);
    }
  }
  
  return true;
}