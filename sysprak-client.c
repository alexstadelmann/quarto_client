#include "header.h"

/*How-To-Use: Zum Ausführen kann man ./sysprak-client aufrufen mit zwei optionalen Parametern
-g <13-stellige GAMEID> -p <Spielernummer(1 oder 2)>
Wird keine Gameid mitgegeben, dann erstellt das Programm eine zufällige GameId
und fallst keine Spielernummer übergeben wird, dann ist der Default Spieler 1.
*/
int main(int argc, char **argv) {

  /* 
  if(argc != 5) {
    fprintf(stderr, "Incorrect number of arguments!\n");
    return EXIT_FAILURE;
  }
  */
  
  char *game_id = (char*) malloc(sizeof(char)*(ID_LEN + 1));  
  int player_number = 1;
  int ret;
  
  srand(time(NULL));

  //initializes random game id string. Might turn out to be unnessesary if sysprak-client is allways called with parameters.
  id_init(game_id, ID_LEN + 1);

 
  while ((ret = getopt(argc, argv, "g:p:")) != -1) {
    switch(ret) {
      case 'g':

        if(is_valid_id(optarg)) {
          strcpy(game_id, optarg);
          break;
        } else {
          fprintf(stderr, "The game ID entered is incorrect!\n");
          return EXIT_FAILURE;
        }
      case 'p':
        if(is_valid_player_number(optarg)){
          player_number = atoi(optarg);
          break;
        } else {
          fprintf(stderr, "The player number you entered is incorrect!");
          return EXIT_FAILURE;
        }
        
      default:
        break;

    }
  }

  printf("Game ID: %s\nPlayer Number: %d\n",game_id, player_number);
  connectServer();
  
 return EXIT_SUCCESS;

}



