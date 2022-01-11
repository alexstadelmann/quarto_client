#include "header.h"
#include <math.h>

bool is_valid_id(char *arg) 
{
  int i = 0;
  int length = 0;
  while(arg[i] != '\0') {
    if(!isalnum((int)(arg[i]))) return false;
    i++;
    length++;
  } 
  if(length != 13) return false;
  return true;
}

bool is_valid_player_number(char *arg) 
{
  if((arg[0]== '1' || arg[0]== '2') && arg[1]== '\0') {
    return true;
  } else {
    return false;
  }
}

bool is_valid_file(char *arg, char *string)
{
  if(strcmp(arg,string) == 0){
    return false;
  } else {
    return true;
  }

}

void print_id(char *ptr, int length)
{
  for(int i = 0; i < length; i++){
    printf("%d", ptr[i]);
  }
}

int recv_all(int sockfd, char *buffer, size_t len)
{
  
  int packet_length = 0;
  int temp;
  do{
    temp = read(sockfd, buffer+packet_length, len);
    packet_length += temp;
  } while(buffer[packet_length - 1] != '\n');
  return packet_length;
}

bool read_line(int socket_fd, char* ptr) {
  int len = 0;
  do {

    if((read(socket_fd, ptr + len, 1) == -1)) {
      return false;
    } len++;

  } while (ptr[len - 1] != '\n');
  ptr[len - 1] = '\0';
  return true;
}


void printField(int n, int board[n][n]) {
  
  printf("\nNext: %d\n", nextPiece);
  puts(" ------------");
  for(int i = 0; i < n; i++) {
    printf("|");
    for(int j = 0; j < n; j++) {
      if(board[i][j] == -1) {
        printf(" * ");
      } else if(board[i][j] < 10) {
        printf(" %d ", board[i][j]);
      } else{
        printf(" %d",board[i][j]);
      }
      
    }
    printf("|\n");
  }
  puts(" ------------");
}

// void print_binary(double num) {
//   double digits =  log(num);
//   printf("digits: %f\n", digits);
// }