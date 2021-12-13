#include "header.h"
#include "serverConnectionHeader.h"
#include "config.h" 

//declare important variables
  char game_id[ID_LEN + 1];
  char player_number[2];
  char player_name[NAME_LEN + 1];
  char cip_version[VERSION_LEN + 1];
  char portVal[BUFFERLENGTH_PORT];
  char *paramNameHost = "hostname";
  char *paramNamePort = "portnumber";
  char *paramNameGame = "gamekindname";
  char *string = "";
  char *confile;

  configparam confiparam;

/*How-To-Use: call ./sysprak-client with two obligatory parameters: 
-g <GAME_ID>  and two optional parameters: -p <PLAYER_NUMBER>
*/
int main(int argc, char **argv)
{

  //two parameters are optional, so there are 3 or 5 parameters in total.
  if(argc != 3 && argc != 5) {
    fprintf(stderr, "Incorrect number of arguments!\n");
    return EXIT_FAILURE;
  }
  
  
  
  // schaut ob spieler als parameter mitgegeben wurde, bei 0 = kein Spieler und bei 1 = Spieler
  int player_check = 0; 
  int ret;

  //get parameters
  while ((ret = getopt(argc, argv, "g:p:c:")) != -1) {
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
                   
          switch (atoi(optarg))
          {
          case 1:
            strcpy(player_number, "0");
            break;
          case 2:
            strcpy(player_number, "1");
            break;  
          
          default:
            break;
          }
            
          //strcpy(player_number,optarg);
          player_check = 1;
          break;
        } else {
          fprintf(stderr, "The player number you entered is incorrect!");          
          return EXIT_FAILURE;
        }
       
      case 'c':
        if(is_valid_file(optarg,string)){
        // if(strcmp(optarg,string) != 0){
            strcpy(confile, optarg);
            printf("The confile is %s. \n", confile);
        } else {
          strcpy(confile, "client.conf");                                                
          createClientConfig();
          printf("Using \"client.conf\" as confile. \n");
        } 
      break;

      default:
        break;

    }
  }

  if(player_check == 0){
    strcpy(player_number,"");
    printf("No player set\n");
  }

  //fill struct
  char *hostValue = readConfig(paramNameHost);
  strcpy(confiparam.hostName,hostValue);
  free(hostValue);

  char *gameKindValue = readConfig(paramNameGame);
  strcpy(confiparam.gameKindName,gameKindValue);
  free(gameKindValue);

  char *portValue = readConfig(paramNamePort);
  strcpy(portVal, portValue);
  free(portValue);
  confiparam.portNumber = atoi(portVal);
  
  //connect to the MNM Server
  int socket_fd;
  if ((socket_fd = connectServer()) == -1){
      perror("connection");
  }
  //Phase1: the prolog interchange with the server
  performConnection(socket_fd);
  
 return EXIT_SUCCESS;

}



