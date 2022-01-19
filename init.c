#include "header.h"
#include "init.h"
#include "config.h"

//Variables for command line arguments
char game_id[ID_LEN + 1];
char player_number[2];
char player_name[NAME_LEN + 1];
char cip_version[VERSION_LEN + 1];
int player_check = 0; 

//variables for config file


bool check_argc(int argc) {
  if(argc != 3 && argc != 5) {
    perror("argc should be 3 or 5");
    return false;
  }
  return true;
}

bool get_args(int argc, char **argv) {
  
  int ret;

  //read parameters 
  while ((ret = getopt(argc, argv, "g:p:c:")) != -1) {

    switch(ret) {

      case 'g':
        if(is_valid_id(optarg)) {
          strcpy(game_id, optarg);
          break;
        } else {
          perror("game id incorrect");
          return false;
        }

      case 'p':
        if(is_valid_player_number(optarg)){
                   
          switch (atoi(optarg)) {
            case 1:
              strcpy(player_number, "0");
              break;
            case 2:
              strcpy(player_number, "1");
              break;  
            
            default:
              break;
            }
            break;
              
          } else {
            perror("player number incorrect");          
            return false;
          }
          
        
      case 'c':
         if(optarg[0] != '\0'){
            strcpy(config_file, optarg);
            break;
        } else {
          perror("empty config file name");
          return false;
        }
      break;

      default:
        break;

    }
  }

  return true;

} 
