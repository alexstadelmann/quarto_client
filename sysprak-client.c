#include "header.h"
#include "serverConnectionHeader.h"

/*How-To-Use: Zum Ausführen kann man ./sysprak-client aufrufen mit zwei optionalen Parametern
-g <13-stellige GAMEID> -p <Spielernummer(1 oder 2)>
Wird keine Gameid mitgegeben, dann erstellt das Programm eine zufällige GameId
und falls keine Spielernummer übergeben wird, dann ist der Default Spieler 1.
*/
int main(int argc, char **argv){

  //-p <player_number> is optional, to there are 3 or 5 arguments.
  if(argc != 3 && argc != 5) {
    fprintf(stderr, "Incorrect number of arguments!\n");
    return EXIT_FAILURE;
  }
  
  //allocate memory for global parameters (declared in header.h):
  game_id = (char*) malloc((ID_LEN + 1)*sizeof(char));
  player_number = (char*) malloc(NAME_LEN*sizeof(char));
  player_name = (char*) malloc(NAME_LEN*sizeof(char));
  cip_version = (char*) malloc(sizeof(char));
  

  
  
  player_number=NULL;
  int playercheck = 0; // schaut ob spieler als parameter mitgegeben wurde, bei 0 = kein Spieler und bei 1 = Spieler
  int ret;

 
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
        if(strcmp(optarg,"")!=0){
          player_number=optarg;
          playercheck = 1;
          break;
        } else {
          fprintf(stderr, "The player number you entered is incorrect!");

          
          return EXIT_FAILURE;
        }
        
      default:
        break;

    }
  }

  if(playercheck ==0){
    player_number="";
    printf("No player set\n");
  }

  
  if (connectServer() == -1){
      //Fehlerbehandlung
  }
  
 return EXIT_SUCCESS;

}



