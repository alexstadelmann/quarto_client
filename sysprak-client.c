#include "header.h"
#include "init.h"
#include "connect.h"
#include "prolog.h"

  char portVal[BUFFERLENGTH_PORT];
  char *paramNameHost = "hostname";
  char *paramNamePort = "portnumber";
  char *paramNameGame = "gamekindname";
  char *string = "";
  char confile [100];
  int test = 0;
  pid_t pid =0;

  configparam confiparam;

  //Variables for SHM Segments
  int shmID_serverInfo;
  int shmID_player;
  int *shmIDplayer;  //hier einmal als Pointer definiert damit die Variable zum attachen benutzt werden kann

  struct serverinfo *serverinfo;

//Variables from the game phase:
int moveTime;
int board[4][4];
char cube[4][4][5];
int winner;
char winnerName[126];
int nextPiece;
int nextField;
int nextOpponentPiece;
int freePieces[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
char nextMove[16];
char nextCoordinates[2];
int freeFields[16];
int height;
int width;

//Hilfsfunktion zum Löschen der SHM Segmente beim Terminieren
static void handleExit(void){
  if(shmIDplayer != 0){
    for(int i=0; i<serverinfo->totalPlayers-1; i++){
      if(shmIDplayer[i]!=0){
        shmIDplayer[i] = deletingSHM(shmIDplayer[i]);
      }
    }
  }
  shmID_player = deletingSHM(shmID_player);
  shmID_serverInfo = deletingSHM(shmID_serverInfo);
}

void attachPlayers(int sig){
  (void)sig;
  for (int i= 0; i< serverinfo->totalPlayers-1; i++){
    serverinfo->restPlayers[i] =attachingSHM(shmIDplayer[i]);
  }
}


/*How-To-Use: call ./sysprak-client with two obligatory parameters: 
-g <GAME_ID>  and two optional parameters: -p <PLAYER_NUMBER>
*/
int main(int argc, char **argv)
{
  //create SHM Segments
  shmID_player = creatingSHM(BUFFERLENGTH*sizeof(int)); //vllt auch stattdessen sizeof(struct player)
  shmID_serverInfo = creatingSHM(sizeof(struct serverinfo)); 
  //signal for players
  signal(SIGUSR2, attachPlayers); 

  //check if argument count is correct
  if(!check_argc(argc)) return 1;

  //read command line parameters 
  if(!get_args(argc, argv)) return 1;
 
    
 //if(!make_config_file()) return 1;

  


 if((pid=fork())<0){
   perror("Error splitting the process");
   exit(1);

  //CONNECTOR (child process)
  }else if(pid == 0){
    

    //Aufruf Hilfsfunktion zum Löschen der Segmente
    atexit(handleExit);

    //connect to the MNM Server
    int socket_fd;
    if ((socket_fd = connectServer()) == -1){
      perror("connection");
      return -1;
    }

    //Attachen der SHM Bereiche
    serverinfo = attachingSHM(shmID_serverInfo);
    shmIDplayer = attachingSHM(shmID_player);

    //prolog phase beginns
    if(!prolog(socket_fd)) return 1;

    //prolog phase
    if(!game(socket_fd)) return 1;
    //game phase
    game(socket_fd);


    close(socket_fd);

  
  }else {
    //THINKER(parent process)
    //pid, which is fork's return value, is now the child's process-id.

    //SHM Segmente im Thinker attachen
    serverinfo = attachingSHM(shmID_serverInfo);
    shmIDplayer = attachingSHM(shmID_player);
    //Speichern der PID im Struct
    serverinfo->thinker =getpid();
    serverinfo->connector= pid;

    
    //kill the zombie process 
    if(waitpid(pid,  NULL, 0) != pid){
      perror("Error while waiting for childprocess");
      exit(EXIT_FAILURE);
    }
    
    
  }

 return EXIT_SUCCESS;
}
  
  
 




