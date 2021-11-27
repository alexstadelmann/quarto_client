#include "header.h"


int main(int argc, char **argv) {
  char *gameId = (char*) malloc(sizeof(char)*(ID_LEN + 1));
  int playerNum = 1;
  int ret;
  srand(time(NULL));

  idInit(gameId, ID_LEN + 1);

  while ((ret = getopt(argc, argv, "g:p:")) != -1) {
    switch(ret) {
      case 'g':

        if(isValidId(optarg)) {
          strcpy(gameId, optarg);
          break;
        } else {
          fprintf(stderr, "The game ID entered is incorrect!\n");
          return EXIT_FAILURE;
        }
      case 'p':
        if(isValidPlayerNum(optarg)){
          playerNum = atoi(optarg);
          break;
        } else {
          fprintf(stderr, "The player number you entered is incorrect!");
          return EXIT_FAILURE;
        }
        
      default:
        abort();

    }
  }

  printf("Game ID: %s\nPlayer Number: %d\n",gameId, playerNum);
 
 return EXIT_SUCCESS;

}



