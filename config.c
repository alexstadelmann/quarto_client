char config_file[100] = {0};
#include "config.h"
#include "header.h"

char portVal[BUFFERLENGTH_PORT];
  char *paramNameHost = "hostname";
  char *paramNamePort = "portnumber";
  char *paramNameGame = "gamekindname";
  char *string = "";

bool readConfig(char *config) {

    if (config[0] == '\0') {
      strcpy(config, "client.conf");
    }
                                                        
    char buffer[BUFFERLENGTH];  
    
    char *pointer_one;
    char *pointer_two;                                        

    FILE *file = fopen(config, "r");                                //open config

    if(file != NULL) {                                        //filter error: couldn't open file
        
      while((fgets(buffer,BUFFERLENGTH - 1, file) != NULL)) {

      //   /*
      //   each line should contain one "="-sign, therefore there
      //   should be two tokens if we separate at the "="-sign
      //   */      
      
      pointer_one = strtok(buffer,"=");
         int cursor = 0;
         while(pointer_one[cursor] != '\0' && pointer_one[cursor] != ' ' ) {
           cursor++;
         }
         pointer_one[cursor] = '\0';

        pointer_two = strtok(NULL, "=");
        cursor = 0;
        while(pointer_two[cursor] != '\0' && pointer_two[cursor] == ' ') {
          cursor++;
        }
        pointer_two = pointer_two + cursor ;

        //save data from file in struct
        if(strcmp(pointer_one, "hostname") == 0) {
          
          
        }
      

        printf("%s\n", pointer_one);
        printf("%s", pointer_two);
      }
      puts("");
    } else {                                                                        
        perror("Error: Couldn't open file!");
        exit(EXIT_FAILURE);
    }

  fclose(file);
  return true;
}